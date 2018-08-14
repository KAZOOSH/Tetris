#pragma once

#include "Paddle.h"
#include "GameParameters.h"
#include "ofxSerial.h"

class PlayerControl
{
public:
	PlayerControl();
	~PlayerControl();

	void setup(vector<shared_ptr<Paddle>> paddles, GameParameters* params);

	//callbacks
	void onPaddleMove(ofJson& json);
	void onBuzzer(const ofxIO::SerialBufferEventArgs& args);
	void onPlayer1(const ofxIO::SerialBufferEventArgs& args);
	void onPlayer2(const ofxIO::SerialBufferEventArgs& args);

protected:
	void initSerial();
	void connectDevice(ofxIO::BufferedSerialDevice& device, ofx::IO::SerialDeviceInfo info, string callback);
private:
	vector<shared_ptr<Paddle>> paddles;
	GameParameters* params;

	vector<ofxIO::BufferedSerialDevice> serialPlayer;
	ofxIO::BufferedSerialDevice serialBuzzer;
};

