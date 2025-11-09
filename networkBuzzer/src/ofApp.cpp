#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("oscSenderExample");
	ofSetFrameRate(60); // run at 60 fps
	ofSetVerticalSync(true);

	// open an outgoing connection to HOST:PORT

	auto json = ofLoadJson("settings.json");
	sender.setup(json["ip"].get<string>(), json["port"].get<int>());

	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();

	// this should be set to whatever com port your serial device is connected to.
	// (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
	// arduino users check in arduino app....
	int baud = 9600;
	serial.setup(0, baud); //open the first device
}

//--------------------------------------------------------------
void ofApp::update(){
	
	
	int nRead = 0;  // a temp variable to keep count per read
	unsigned char bytesReturned[3];

	while ((nRead = serial.readBytes(bytesReturned, 3)) > 0) {
		nTimesRead++;
		nBytesRead = nRead;

		ofxOscMessage m;
		m.setAddress("buzzer");
		m.addBoolArg(true);
		sender.sendMessage(m, false);
	};


	memcpy(bytesReadString, bytesReturned, 3);
}

//--------------------------------------------------------------
void ofApp::draw(){


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'b') {
		ofxOscMessage m;
		m.setAddress("buzzer");
		m.addBoolArg(true);
		sender.sendMessage(m, false);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
