#include "ofApp.h"

using namespace ofxModule;

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	ofSetFrameRate(60);
	ofEnableAlphaBlending();

	ofSetLogLevel(OF_LOG_NOTICE);
	ofLogToConsole();

	//init app and connect modules
	if (moduleControl.getXmlLoader()->xmlHasModule("CamInput")) {
		CamInput* mod = new CamInput();
		moduleControl.getXmlLoader()->addModule(mod);
	}
        if (moduleControl.getXmlLoader()->xmlHasModule("MouseInput")) {
		MouseInput* mod = new MouseInput();
		moduleControl.getXmlLoader()->addModule(mod);
	}
	if (moduleControl.getXmlLoader()->xmlHasModule("Tetris")) {
		Tetris* mod = new Tetris();
		moduleControl.getXmlLoader()->addModule(mod);
        }

	moduleControl.getXmlLoader()->createModuleConnections();
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSoundUpdate();
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
	moduleControl.getModuleRunner()->updateModules();
}

//--------------------------------------------------------------
void ofApp::draw(){
	moduleControl.getModuleRunner()->drawModules();

	ofSetColor(255);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'f')
	{
		ofToggleFullscreen();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
