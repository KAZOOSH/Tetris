#include "ofApp.h"

using namespace ofxModule;

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	ofSetFrameRate(60);
	ofEnableAlphaBlending();

	ofSetLogLevel(OF_LOG_NOTICE);
	ofLogToConsole();

	beats.load("sound/Kleiner Stein.mp3");

	if (moduleControl.getModuleLoader()->getCountModulesConfig("MouseInput")) {
		auto mod = new MouseInput();
		moduleControl.getModuleLoader()->addModule(mod);
	}
	if (moduleControl.getModuleLoader()->getCountModulesConfig("Tetris")) {
		auto mod = new Tetris();
		moduleControl.getModuleLoader()->addModule(mod);
	}
    
	// enables the communication between modules (set in modules.json)
	moduleControl.getModuleLoader()->initModuleCommunication();
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
