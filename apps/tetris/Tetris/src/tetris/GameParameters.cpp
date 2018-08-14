#include "GameParameters.h"



GameParameters::GameParameters()
{
	ofFile file("_Tetris/params.json");
	if (file.exists()) {
		file >> params;
	} else {
		ofLogError(" _Tetris/params.json does not exist");
	}
}


GameParameters::~GameParameters()
{
}

void GameParameters::notifyGameEvent(ofJson eventText)
{
	ofNotifyEvent(gameEvent, eventText);
}

void GameParameters::notifyControlEvent(ofJson eventText)
{
	ofNotifyEvent(controlEvent, eventText);
}
