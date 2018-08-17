/*
 *  Capture.cpp
 *  printer
 *
 *  Created by Brian Eschrich on 02.10.15
 *  Copyright 2015 reddo UG. All rights reserved.
 *
 */

#include "CamInput.h"

using namespace ofxModule;

CamInput::CamInput(string moduleName):ModuleDrawable("CamInput",moduleName,false){
	setSingleThreaded();
	parameters.add(deviceId.set("deviceId",2));
	parameters.add(width.set("width", 640));
	parameters.add(height.set("height", 480));
	parameters.add(isOsc.set("isOsc", false));
	parameters.add(nPaddle.set("nPaddle", "2"));
	loadSettings();
	
	if(isOsc) addOSCServer(new OSCServer());


	colinearPoints = shared_ptr<ColinearPoints>(new ColinearPoints());

	contourMinAreaRadius.addListener(this, &CamInput::contourMinAreaRadiusChanged);
	contourMaxAreaRadius.addListener(this, &CamInput::contourMaxAreaRadiusChanged);
	contourPersistence.addListener(this, &CamInput::contourPersistenceChanged);
	contourMaxDistance.addListener(this, &CamInput::contourMaxDistanceChanged);
	slopeError.addListener(this, &CamInput::colinearSlopeErrorChanged);
	interceptError.addListener(this, &CamInput::colinearInterceptErrorChanged);

	gui.setup("panel"); 
	gui.add(thresholdValue.set("threshold", 240, 0, 255));
	gui.add(erodeValue.set("erode", 0, 0, 10));
	gui.add(dilateValue.set("dilate", 3, 0, 10));
	gui.add(blurValue.set("blur", 2, 0, 10));
	gui.add(contourPersistence.set("contourPersistence", 30, 1, 50));
	gui.add(contourMaxDistance.set("contourMaxDistance", 200, 1, 200));
	gui.add(contourMinAreaRadius.set("contourMinAreaRadius", 8, 1, 150));
	gui.add(contourMaxAreaRadius.set("contourMaxAreaRadius", 20, 2, 300));
	gui.add(bHide.set("Hide Gui", false));
	gui.add(bShowLabels.set("Show Boxes and Positions", true));

	gui.add(interceptError.set("InterceptError", 10, 0, 300));
	gui.add(slopeError.set("SlopeError", 0.05, 0, 1));

	cam.setDeviceID(deviceId);
	cam.setup(width, height);
	thresh.allocate(width, height, OF_IMAGE_GRAYSCALE);

	contourFinder.setMinAreaRadius(contourMinAreaRadius);
	contourFinder.setMaxAreaRadius(contourMaxAreaRadius);

	// wait for half a second before forgetting something
	contourFinder.getTracker().setPersistence(contourPersistence);
	// an object can move up to 32 pixels per frame
	contourFinder.getTracker().setMaximumDistance(contourMaxDistance);

	kalman.init(1 / 10000., 1 / 10.); // inverse of (smoothness, rapidness)

	line.setMode(OF_PRIMITIVE_LINE_STRIP);
	predicted.setMode(OF_PRIMITIVE_LINE_STRIP);
	estimated.setMode(OF_PRIMITIVE_LINE_STRIP);

	speed = 0.f;

	//startThread();
}
//------------------------------------------------------------------
void CamInput::stopModule() {


}


//------------------------------------------------------------------
void CamInput::update() {
	colinearPoints->clearPointList();

	cam.update();
	if (cam.isFrameNew()) {
		convertColor(cam, thresh, CV_RGB2GRAY);
		if (blurValue.get() > 0) {
			GaussianBlur(thresh, blurValue.get());
		}

		threshold(thresh, thresholdValue);

		if (erodeValue.get() > 0) {
			erode(thresh, erodeValue.get());
		}

		if (dilateValue.get() > 0) {
			dilate(thresh, dilateValue.get());
		}

		thresh.update();
		contourFinder.findContours(thresh);

		RectTracker& tracker = contourFinder.getTracker();


		//no colinear point check
		if (contourFinder.size() == 3) {
			foundPoints.clear();
			for (size_t i = 0; i < contourFinder.size(); i++)
			{
				foundPoints.push_back(contourFinder.getCenter(i));
			}
			sendPositions();
		}

		//colinear point check
		/*double d = 0.04;
        vector<cv::Point> approx;
		for (int i = 0; i < contourFinder.size(); i++) {
			vector<cv::Point> contour = contourFinder.getContour(i);
			double peri = arcLength(contour, true);
			approxPolyDP(contour, approx, d * peri, true);
			if (approx.size() > 3 && approx.size() < 6) {
				colinearPoints->addPoint(contourFinder.getCenter(i));
			}
		}

		//cout << colinearPoints->getPointListSize();
		if (colinearPoints->getPointListSize() >= 3) {
			vector<vector<cv::Point>> computedPointLists = colinearPoints->computeColinearPoints();
			if (computedPointLists.size() > 0) {
				// take first List of 3 Items
				foundPoints = computedPointLists[0];
				sendPositions();
				//cout << "# ColinearPoints: " << foundPoints.size() << endl;
			} else {
				//cout << "No Group found" << endl;
			}
		}*/

	}
}


//------------------------------------------------------------------
void CamInput::draw() {
	ofBackground(0);

	if (!bHide) {
		gui.draw();
	}

	line.draw();

	predicted.draw();
	ofPushStyle();
	ofSetColor(ofColor::red, 128);
	ofFill();
	ofDrawCircle(point, speed * 2);
	ofPopStyle();

	estimated.draw();

	cam.draw(0, 480);
	thresh.draw(640, 480);

	RectTracker& tracker = contourFinder.getTracker();

	// draw red rectangles at position
	for (int i = 0; i < foundPoints.size(); i++) {
		ofPushMatrix();
		ofTranslate(0, 480);
		ofSetColor(255, 0, 0);
		ofNoFill();
		ofDrawRectangle(foundPoints[i].x - 10, foundPoints[i].y - 10, 20, 20);
		ofSetColor(255, 255, 255);
		ofPopMatrix();
	}

	if (bShowLabels) {
		ofSetColor(255);
		ofPushMatrix();
		ofTranslate(0, 480);
		contourFinder.draw();
		ofPopMatrix();
		for (int i = 0; i < contourFinder.size(); i++) {
			ofPoint center = toOf(contourFinder.getCenter(i));
			ofPushMatrix();
			ofTranslate(center.x, 480 + center.y);

			int label = contourFinder.getLabel(i);
			string msg = ofToString(label) + ":" + ofToString(tracker.getAge(label));
			ofDrawBitmapString(msg, 0, 0);
			ofVec2f velocity = toOf(contourFinder.getVelocity(i));
			ofScale(5, 5);
			ofDrawLine(0, 0, velocity.x, velocity.y);
			ofPopMatrix();
		}
	} else {
		for (int i = 0; i < contourFinder.size(); i++) {
			unsigned int label = contourFinder.getLabel(i);
			// only draw a line if this is not a new label
			if (tracker.existsPrevious(label)) {
				// use the label to pick a random color
				ofSeedRandom(label << 24);
				ofSetColor(ofColor::fromHsb(ofRandom(255), 255, 255));
				// get the tracked object (cv::Rect) at current and previous position
				const cv::Rect& previous = tracker.getPrevious(label);
				const cv::Rect& current = tracker.getCurrent(label);
				// get the centers of the rectangles
				ofVec2f previousPosition(previous.x + previous.width / 2, previous.y + previous.height / 2 + 480);
				ofVec2f currentPosition(current.x + current.width / 2, current.y + current.height / 2 + 480);
				ofDrawLine(previousPosition, currentPosition);
				ofSetColor(255);
			}
		}
	}

	ofDrawBitmapString("found points : " + ofToString(foundPoints.size()), 30, 500);
}

/// \brief sends message to connected modules
void CamInput::sendPositions()
{
	if (foundPoints[0].x > foundPoints[1].x)
		swap(foundPoints[0], foundPoints[1]);
	if (foundPoints[0].x > foundPoints[2].x)
		swap(foundPoints[0], foundPoints[2]);
	if (foundPoints[1].x > foundPoints[2].x)
		swap(foundPoints[1], foundPoints[2]);
	
	ofJson send;
	send["function"] = "paddle" + nPaddle + "Position";
	send["paddle"] =
	{ {
			{ "x", ofMap(foundPoints[0].x,0,width,0.0,1.0) },
			{ "y", ofMap(foundPoints[0].y,0,height,0.0,1.0) }
		},{
			{ "x", ofMap(foundPoints[1].x,0,width,0.0,1.0) },
		{ "y", ofMap(foundPoints[1].y,0,height,0.0,1.0) }
		}
	};
	if (!isOsc) {
		
		notifyEvent(send);
	} else {
		ofxOscMessage message;
		message.setAddress("paddlePosition");
		message.addStringArg(send.dump());

		sendOSCMessage(message);
	}
	

	

}

void CamInput::contourMinAreaRadiusChanged(int & minRadius)
{
	contourFinder.setMinAreaRadius(minRadius);
}

void CamInput::contourMaxAreaRadiusChanged(int & maxRadius)
{
	contourFinder.setMaxAreaRadius(maxRadius);
}

void CamInput::contourPersistenceChanged(int & persistence)
{
	contourFinder.getTracker().setPersistence(persistence);
}

void CamInput::contourMaxDistanceChanged(int & maxDistance)
{
	contourFinder.getTracker().setMaximumDistance(maxDistance);
}

void CamInput::colinearSlopeErrorChanged(double & slopeError)
{
	colinearPoints->setSlopePrecision(slopeError);
}

void CamInput::colinearInterceptErrorChanged(double & interceptError)
{
	colinearPoints->setInterceptPrecision(interceptError);
}

