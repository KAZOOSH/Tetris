#include "PlayerControl.h"



PlayerControl::PlayerControl()
{
}


PlayerControl::~PlayerControl()
{
	ofRemoveListener(serialBuzzer.events.onSerialBuffer, this, &PlayerControl::onBuzzer);
	ofRemoveListener(serialPlayer[0].events.onSerialBuffer, this, &PlayerControl::onPlayer1);
	ofRemoveListener(serialPlayer[1].events.onSerialBuffer, this, &PlayerControl::onPlayer2);
}

void PlayerControl::setup(vector<shared_ptr<Paddle>> paddles_, GameParameters * params_)
{
	paddles = paddles_;
	params = params_;

	serialPlayer.push_back(ofxIO::BufferedSerialDevice());
	serialPlayer.push_back(ofxIO::BufferedSerialDevice());
	initSerial();
}

//TODO : add martin control
void PlayerControl::onPaddleMove(ofJson & json)
{
	ofJson out;
	out["control"] = "paddle";
	for (size_t i = 0; i < 2; ++i) {
		//calculate movement area
		float w = 0.5*params->params["width"].get<float>();
		float offset = (w - params->params["paddleArea"][0].get<float>()) / 2;
		float x_min = offset + i * w;
		float x_max = w - offset + i * w;
		float h = params->params["height"].get<float>();
		float y_min = h - params->params["paddleArea"][1].get<float>();
		float y_max = h;

		//map input to movement area
		ofVec2f pos = ofVec2f(ofMap(json["paddle"][i]["x"].get<float>(), 0.0,1.0,x_min,x_max),
			ofMap(json["paddle"][i]["y"].get<float>(), 0.0, 1.0, y_min, y_max));
		float rot = json["paddle"][i]["rot"];
		
		paddles[i]->setPosition(
			ofMap(json["paddle"][i]["x"].get<float>(), 0.0, 1.0, x_min, x_max),
			ofMap(json["paddle"][i]["y"].get<float>(), 0.0, 1.0, y_min, y_max),
			json["paddle"][i]["rot"]);

		out["paddle" + ofToString(i)] = {
			{"x" , pos.x},
			{"y", pos.y},
			{"rot" , rot}
		};
	}
	params->notifyControlEvent(out);
}

void PlayerControl::onBuzzer(const ofxIO::SerialBufferEventArgs & args)
{
	string message = args.buffer().toString();
	if (message[0] == 'p') {
		//event
		cout << "buzzer input" << endl;
		
		ofJson out;
		out["control"] = "buzzer";
		params->notifyControlEvent(out);
	}
}

void PlayerControl::onPlayer1(const ofxIO::SerialBufferEventArgs & args)
{
	string message = args.buffer().toString();
	if (message[0] == 'p') {
		//event
		cout << "player1 input" << endl;

		ofJson out;
		out["control"] = "player1Button";
		params->notifyControlEvent(out);
	}
}

void PlayerControl::onPlayer2(const ofxIO::SerialBufferEventArgs & args)
{
	string message = args.buffer().toString();
	if (message[0] == 'p') {
		//event
		cout << "player2 input" << endl;

		ofJson out;
		out["control"] = "player2Button";
		params->notifyControlEvent(out);
	}
}

void PlayerControl::initSerial()
{
	auto deviceDescriptors = ofx::IO::SerialDeviceUtils::listDevices();

	if (!deviceDescriptors.empty())
	{
		ofLogNotice("ofApp::setup") << "Connected Devices: ";
		for (auto deviceDescriptor : deviceDescriptors)
		{
			ofLogNotice("ofApp::setup") << "\t" << deviceDescriptor;

			//connect matching devices
			if (deviceDescriptor.getHardwareId() == params->params["serial"]["buzzerId"]) {
				connectDevice(serialBuzzer, deviceDescriptor,"buzzer");
			}else if (deviceDescriptor.getHardwareId() == params->params["serial"]["player1Button"]) {
				connectDevice(serialPlayer[0], deviceDescriptor, "player1");
			} else if (deviceDescriptor.getHardwareId() == params->params["serial"]["player2Button"]) {
				connectDevice(serialPlayer[1], deviceDescriptor, "player2");
			}
		}
	} else
	{
		ofLogNotice("ofApp::setup") << "No devices connected.";
	}
}

void PlayerControl::connectDevice(ofxIO::BufferedSerialDevice & device, ofx::IO::SerialDeviceInfo info, string callback)
{
	if (device.setup(info, 115200)) {
		//register callback
		if(callback == "buzzer") ofAddListener(device.events.onSerialBuffer, this, &PlayerControl::onBuzzer);
		else if (callback == "player1") ofAddListener(device.events.onSerialBuffer, this, &PlayerControl::onPlayer1);
		else if (callback == "player2") ofAddListener(device.events.onSerialBuffer, this, &PlayerControl::onPlayer2);
		ofLogNotice("ofApp::setup") << "Successfully setup " << callback << "   -> "<< info;
	} else {
		ofLogError("ofApp::setup") << "Unable to setup " << callback << "   -> " << info;
	}

}
