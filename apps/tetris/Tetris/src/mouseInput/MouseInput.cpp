/*
 *  Capture.cpp
 *  printer
 *
 *  Created by Brian Eschrich on 02.10.15
 *  Copyright 2015 reddo UG. All rights reserved.
 *
 */

#include "MouseInput.h"

using namespace ofxModule;

MouseInput::MouseInput(string moduleName):ModuleDrawable("MouseInput",moduleName,false){

	loadSettings();

	startThread();
}
//------------------------------------------------------------------
void MouseInput::stopModule() {


}


//------------------------------------------------------------------
void MouseInput::update() {
	

	ofJson send;
	send["function"] = "paddlePosition";
	send["paddle"] = 
	{{
			{"x", ofMap(ofGetMouseX(),0,ofGetWidth(),0.0,1.0)},
			{"y", ofMap(ofGetMouseY(),0,ofGetHeight(),0.0,1.0)},
			{ "rot", 0.0f }
		},{
			{ "x", ofMap(ofGetMouseX()+300,0,ofGetWidth(),0.0,1.0) },
			{ "y", ofMap(ofGetMouseY(),0,ofGetHeight(),0.0,1.0) },
			{ "rot", 0.2f }
		}
		
	};
	notifyEvent(send);
}


//------------------------------------------------------------------
void MouseInput::draw() {

}

