#include "PlayerControl.h"



PlayerControl::PlayerControl()
{
}


PlayerControl::~PlayerControl()
{
}

void PlayerControl::setup(shared_ptr<GameComponents> components_)
{
	components = components_;
	paddles = components->gameControl()->paddles;

	initSerial();
}

void PlayerControl::update()
{
	// pedal
	try
	{
		// Read all bytes from the device;
		uint8_t buffer[16];
		while (serialPlayer.available() > 0){
			std::size_t sz = serialPlayer.readBytes(buffer, 16);
			if (sz >= 1 && buffer[0] != '0') {
				std::bitset<8> bits(buffer[0]);
				for (size_t i = 0; i < 4; i++){
					if (bits.test(i)) {
						sendPedalCommand(i);
					}
				}
			}
		}
	}
	catch (const std::exception& exc){
		ofLogError("ofApp::update") << exc.what();
	}

	// buzzer
	try
	{
		// Read all bytes from the device;
		uint8_t buffer[16];
		while (serialBuzzer.available() > 0) {
			std::size_t sz = serialBuzzer.readBytes(buffer, 16);
			if (sz >= 1 && buffer[0] == 'p') {
				ofJson out;
				out["control"] = "buzzer";
				components->events()->notifyControlEvent(out);
			}
		}
	}
	catch (const std::exception& exc){
		ofLogError("ofApp::update") << exc.what();
	}
}

//TODO : add martin control
void PlayerControl::onPaddleMove(const ofJson & json)
{
	auto settings = components->params();

	ofJson out;
	out["control"] = "paddle";

	int nPaddle = json["function"] == "paddle1Position" ? 0 : 1;

		//calculate movement area
		float w = 0.5*settings->settings["width"].get<float>();
		float offset = (w - settings->settings["paddleArea"][0].get<float>()) / 2;
		float x_min = offset + nPaddle * w;
		float x_max = w - offset + nPaddle * w;
		float h = settings->settings["height"].get<float>();
		float y_min = h - settings->settings["paddleArea"][1].get<float>()- settings->settings["paddleArea"][2].get<float>();
		float y_max = h - settings->settings["paddleArea"][2].get<float>();


		//map input to movement area
		ofVec2f pos1 = ofVec2f(ofMap(json["paddle"][0]["x"].get<float>(), 0.2,0.8,x_min,x_max,true),
			ofMap(json["paddle"][0]["y"].get<float>(), 0.0, 1.0, y_min, y_max,true));
		
		ofVec2f pos2 = ofVec2f(ofMap(json["paddle"][1]["x"].get<float>(), 0.2, 0.8, x_min, x_max,true),
			ofMap(json["paddle"][1]["y"].get<float>(), 0.0, 1.0, y_min, y_max));

		paddles[nPaddle]->setAnchorPosition(pos1, pos2);
			
		out["id"] = nPaddle + 1; 
		out["p1"]=
			{
				{ "x" , pos1.x },
				{ "y", pos1.y }
		};
		out["p2"] =
		{
			{ "x" , pos2.x },
			{ "y", pos2.y }
		};
	
	components->events()->notifyControlEvent(out);
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
			cout << deviceDescriptor.getHardwareId() << "   " << components->params()->settings["serial"]["pedalId"].get<string>() << endl;
			//connect matching devices
			if (deviceDescriptor.getHardwareId() == components->params()->settings["serial"]["buzzerId"]) {
				connectDevice(serialBuzzer, deviceDescriptor,"buzzer");
			}else if (deviceDescriptor.getHardwareId() == components->params()->settings["serial"]["pedalId"]) {
				connectDevice(serialPlayer, deviceDescriptor, "pedal");
			}
		}
	} else
	{
		ofLogNotice("ofApp::setup") << "No devices connected.";
	}
}

void PlayerControl::connectDevice(ofxIO::SerialDevice & device, ofx::IO::SerialDeviceInfo info, string name)
{
	if (device.setup(info, 9600)) {
		ofLogNotice("ofApp::setup") << "Successfully setup " << name << "   -> "<< info;
	} else {
		ofLogError("ofApp::setup") << "Unable to setup " << name << "   -> " << info;
	}

}

void PlayerControl::sendPedalCommand(int i)
{
		ofJson out;
		out["control"] = "pedal";
		out["direction"] = i % 2 == 0 ? "left" : "right";
		out["player"] = i < 2 ? 1 : 2;
		components->events()->notifyControlEvent(out);

}
