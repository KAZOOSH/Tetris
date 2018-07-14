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

	parameters.add(deviceId.set("deviceId",2));
	parameters.add(width.set("width",320));
	parameters.add(height.set("height",240));
	loadSettings();
	
	vidGrabber.setVerbose(true);
	vidGrabber.setDeviceID(2);
	vidGrabber.setup(width,height);

	startThread();
}
//------------------------------------------------------------------
void CamInput::stopModule() {


}


//------------------------------------------------------------------
void CamInput::update() {

}


//------------------------------------------------------------------
void CamInput::draw() {

}

/// \brief sends message to connected modules
void CamInput::sendPositions()
{
	ofJson out;
	out["key"] = "value";
	notifyEvent(out);
}

