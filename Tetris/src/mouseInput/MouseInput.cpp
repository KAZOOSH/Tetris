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

MouseInput::MouseInput(string moduleName):ModuleDrawable("MouseInput",moduleName){

	loadSettings();

	ofRegisterKeyEvents(this);
}
//------------------------------------------------------------------
void MouseInput::stopModule() {


}


//------------------------------------------------------------------
void MouseInput::update() {
	

	ofJson send;
	send["function"] = "paddle1Position";
	send["paddle"] = 
	{{
			{"x", ofMap(ofGetMouseX(),0,ofGetWidth(),0.0,1.0)},
			{"y", ofMap(ofGetMouseY()+y0,0,ofGetHeight(),0.0,1.0)}
		},{
			{ "x", ofMap(ofGetMouseX() + 500,0,ofGetWidth(),0.0,1.0) },
			{ "y", ofMap(ofGetMouseY()+y1,0,ofGetHeight(),0.0,1.0) }
		}
	};

	notifyEvent(send);

	send["function"] = "paddle2Position";
	send["paddle"] =
	{ {
		{ "x", ofMap(ofGetMouseX(),0,ofGetWidth(),0.0,1.0) },
	{ "y", ofMap(ofGetMouseY() + y0,0,ofGetHeight(),0.0,1.0) }
		},{
			{ "x", ofMap(ofGetMouseX() + 400,0,ofGetWidth(),0.0,1.0) },
	{ "y", ofMap(ofGetMouseY() + y1,0,ofGetHeight(),0.0,1.0) }
		}
	};

	notifyEvent(send);
}


//------------------------------------------------------------------
void MouseInput::draw() {

}

void ofxModule::MouseInput::keyPressed(ofKeyEventArgs & key)
{
	if (key.key == 'q') {
		y0 += 20;
		y1 -= 20;
	}

	if (key.key == 'w') {
		y0 -= 20;
		y1 += 20;
	}
}

