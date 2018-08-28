/*
 */

#pragma once

#include "ofMain.h"
#include "ModuleDrawable.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ColinearPoints.h"

using namespace ofxModule;
    
	/// \brief control for a webcam 
	/// \ outputes the current Picture as ofTexture via ModuleEvent 
	/// \ outputes can be controlled using ModuleEvents
    class CamInput : public ModuleDrawable{
        
    public:
        
		CamInput(string moduleName = "CamInput");
        
        void update();
        void stopModule();
        void draw();
		void sendPositions();

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
		ofParameter<string> hostIp;

		shared_ptr<ColinearPoints> colinearPoints;
        vector<cv::Point> foundPoints;
		ofParameter<double> slopeError;
		ofParameter<double> interceptError;

    protected:
        
    private:

		ofParameter<int> deviceId;
		ofParameter<int> width;
		ofParameter<int> height;
		ofParameter<bool> isOsc;
		ofParameter<string> nPaddle;
		
		ofVideoGrabber vidGrabber;
    };
    

