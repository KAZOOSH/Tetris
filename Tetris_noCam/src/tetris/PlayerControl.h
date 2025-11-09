#pragma once

#include <bitset>  
#include "Paddle.h"
#include "GameComponents.h"
#include "ofxSerial.h"

class PlayerControl
{
public:
	PlayerControl();
	~PlayerControl();

	void setup(shared_ptr<GameComponents> components);

	void update();

	//callbacks
	void onPaddleMove(const ofJson& json);

protected:
	void initSerial();
	void connectDevice(ofxIO::SerialDevice& device, ofx::IO::SerialDeviceInfo info,string name);
	void sendPedalCommand(int i);
private:
	vector<shared_ptr<Paddle>> paddles;
	shared_ptr<GameComponents> components;

	ofxIO::SerialDevice serialPlayer;
	ofxIO::SerialDevice serialBuzzer;
};

