#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
	ofSetVerticalSync(true);

	colinearPoints = shared_ptr<ColinearPoints>(new ColinearPoints());

	contourMinAreaRadius.addListener(this, &ofApp::contourMinAreaRadiusChanged);
	contourMaxAreaRadius.addListener(this, &ofApp::contourMaxAreaRadiusChanged);
	contourPersistence.addListener(this, &ofApp::contourPersistenceChanged);
	contourMaxDistance.addListener(this, &ofApp::contourMaxDistanceChanged);
	slopeError.addListener(this, &ofApp::colinearSlopeErrorChanged);
	interceptError.addListener(this, &ofApp::colinearInterceptErrorChanged);

	gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
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

	cam.setDeviceID(1);
	cam.setup(640, 480);
	thresh.allocate(640, 480, OF_IMAGE_GRAYSCALE);

	contourFinder.setMinAreaRadius(contourMinAreaRadius);
	contourFinder.setMaxAreaRadius(contourMaxAreaRadius);

	// wait for half a second before forgetting something
	contourFinder.getTracker().setPersistence(contourPersistence);
	// an object can move up to 32 pixels per frame
	contourFinder.getTracker().setMaximumDistance(contourMaxDistance);
	
	kalman.init(1/10000., 1/10.); // inverse of (smoothness, rapidness)
	
	line.setMode(OF_PRIMITIVE_LINE_STRIP);
	predicted.setMode(OF_PRIMITIVE_LINE_STRIP);
	estimated.setMode(OF_PRIMITIVE_LINE_STRIP);
	
	speed = 0.f;
}

void ofApp::update() {
	colinearPoints->clearPointList();
	ofVec2f curPoint(mouseX, mouseY);
	line.addVertex(ofDefaultVertexType(curPoint.x, curPoint.y, 0));
	
	kalman.update(ofDefaultVertexType(curPoint.x, curPoint.y, 0)); // feed measurement
	
	point = kalman.getPrediction(); // prediction before measurement
	predicted.addVertex(ofDefaultVertexType(point.x, point.y, 0));
	estimated.addVertex(kalman.getEstimation()); // corrected estimation after measurement
	
	speed = kalman.getVelocity().length();
	int alpha = ofMap(speed, 0, 20, 50, 255, true);
	line.addColor(ofColor(255, 255, 255, alpha));
	predicted.addColor(ofColor(255, 0, 0, alpha));
	estimated.addColor(ofColor(0, 255, 0, alpha));

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
		double d = 0.04;
		vector<Point> approx;
		for (int i = 0; i < contourFinder.size(); i++) {
			vector<Point> contour = contourFinder.getContour(i);
			double peri = arcLength(contour, true);
			approxPolyDP(contour, approx, d * peri, true);
			if (approx.size() > 3 && approx.size() < 6) {
				colinearPoints->addPoint(contourFinder.getCenter(i));
			}
		}
		
		cout << colinearPoints->getPointListSize();
		if (colinearPoints->getPointListSize() >= 3) {
			vector<vector<Point>> computedPointLists = colinearPoints->computeColinearPoints();
			if (computedPointLists.size() > 0) {
				// take first List of 3 Items
				foundPoints = computedPointLists[0];
				cout << "# ColinearPoints: " << foundPoints.size() << endl;
			}
			else {
				cout << "No Group found" << endl;
			}
		}

	}

}

void ofApp::draw() {
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
	}
	else {
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

}

void ofApp::keyPressed(int key) {
	if (key == 'h') {
		bHide = !bHide;
	}
	if (key == ' ') {
		bShowLabels = !bShowLabels;
	}
}

//--------------------------------------------------------------
void ofApp::contourMinAreaRadiusChanged(int &minRadius) {
	contourFinder.setMinAreaRadius(minRadius);
}

void ofApp::contourMaxAreaRadiusChanged(int &maxRadius) {
	contourFinder.setMaxAreaRadius(maxRadius);
}

void ofApp::contourPersistenceChanged(int & persistence)
{
	contourFinder.getTracker().setPersistence(persistence);
}

void ofApp::contourMaxDistanceChanged(int & maxDistance)
{
	contourFinder.getTracker().setMaximumDistance(maxDistance);
}

void ofApp::colinearSlopeErrorChanged(double & slopeError)
{
	colinearPoints->setSlopePrecision(slopeError);
}

void ofApp::colinearInterceptErrorChanged(double & interceptError)
{
	colinearPoints->setInterceptPrecision(interceptError);
}
