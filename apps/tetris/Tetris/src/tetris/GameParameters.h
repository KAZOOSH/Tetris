#pragma once

#include "ofMain.h"
class GameParameters
{
public:
	GameParameters();
	~GameParameters();

	ofEvent<ofJson> gameEvent;
	void notifyGameEvent(ofJson eventText);

	//settings
	ofJson params;

	//params relevant for current game
	//string gamestate = "idle";
};

