#pragma once
#include "ofMain.h"
//#include "CreationRules.h"

class CreationRules;

class GameParameters
{
public:
	GameParameters();
	~GameParameters();

	ofEvent<ofJson> gameEvent;
	ofEvent<ofJson> controlEvent;

	void notifyGameEvent(ofJson eventText);
	void notifyControlEvent(ofJson eventText);

	void getRandomColorScheme(ofColor& base, ofColor& highlight);

	

	//settings
	ofJson params;
	ofJson colorSchemes;

	//game params
	float winningHeight = 0.9;
	vector<CreationRules*> nextCreationRules;

};

