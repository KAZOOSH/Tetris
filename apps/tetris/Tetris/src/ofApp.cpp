#include "ofApp.h"

using namespace ofxModule;

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	ofSetFrameRate(60);


	ofSetLogLevel(OF_LOG_NOTICE);
	ofLogToConsole();

	//init app
	if (moduleControl.getXmlLoader()->xmlHasModule("CamInput")) {
		CamInput* mod = new CamInput();
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
	moduleControl.getModuleRunner()->updateModules();
}

//--------------------------------------------------------------
void ofApp::draw(){
	moduleControl.getModuleRunner()->drawModules();
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
