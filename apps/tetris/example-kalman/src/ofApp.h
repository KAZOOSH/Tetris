#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ColinearPoints.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	void contourMinAreaRadiusChanged(int & minRadius);
	void contourMaxAreaRadiusChanged(int & maxRadius);
	void contourPersistenceChanged(int & persistence);
	void contourMaxDistanceChanged(int & maxDistance);
	
	void colinearSlopeErrorChanged(double & slopeError);
	void colinearInterceptErrorChanged(double & interceptError);

	ofxCv::ContourFinder contourFinder;
	ofParameter<int> contourMinAreaRadius;
	ofParameter<int> contourMaxAreaRadius;
	ofParameter<int> contourThreshold;
	ofParameter<int> contourPersistence;
	ofParameter<int> contourMaxDistance;
	ofParameter<int> countOfRectanglesInCamera;
	ofParameter<bool> bShowLabels;
	
	ofxCv::KalmanPosition kalman;
	ofMesh predicted, line, estimated;
	ofVec2f point;
	float speed;

	ofVideoGrabber cam;
	ofImage thresh;
	int camWidth;
	int camHeight;

	ofxPanel gui;
	ofParameter<bool> bHide;
	ofParameter<int> thresholdValue;
	
	ofParameter<int> erodeValue;
	ofParameter<int> dilateValue;
	ofParameter<int> blurValue;

	shared_ptr<ColinearPoints> colinearPoints;
	vector<Point> foundPoints;
	ofParameter<double> slopeError;
	ofParameter<double> interceptError;

};
