#pragma once

#include <bitset>  
#include "Paddle.h"
#include "GameParameters.h"
#include "ofxSerial.h"

class PlayerControl
{
public:
	PlayerControl();
	~PlayerControl();

	void setup(vector<shared_ptr<Paddle>> paddles, GameParameters* params);

	void update();

	//callbacks
	void onPaddleMove(const ofJson& json);

protected:
	void initSerial();
	void connectDevice(ofxIO::SerialDevice& device, ofx::IO::SerialDeviceInfo info,string name);
	void sendPedalCommand(int i);
private:
	vector<shared_ptr<Paddle>> paddles;
	GameParameters* params;

	ofxIO::SerialDevice serialPlayer;
	ofxIO::SerialDevice serialBuzzer;
};

