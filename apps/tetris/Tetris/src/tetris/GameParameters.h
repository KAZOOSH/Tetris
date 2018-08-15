#pragma once

#include "ofMain.h"
class GameParameters
{
public:
	GameParameters();
	~GameParameters();

	ofEvent<ofJson> gameEvent;
	ofEvent<ofJson> controlEvent;

	void notifyGameEvent(ofJson eventText);
	void notifyControlEvent(ofJson eventText);

	//settings
	ofJson params;

	//params relevant for current game
	//ofParameter<string> gamestate = "idle";
};

