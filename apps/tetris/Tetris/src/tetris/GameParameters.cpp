#include "GameParameters.h"



GameParameters::GameParameters()
{
	ofFile file("_Tetris/params.json");
	if (file.exists()) {
		file >> params;
	} else {
		ofLogError(" _Tetris/params.json does not exist");
	}

	ofFile file2("_Tetris/colorSchemes.json");
	if (file2.exists()) {
		file2 >> colorSchemes;
	} else {
		ofLogError(" _Tetris/colorSchemes.json does not exist");
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

void GameParameters::getRandomColorScheme(ofColor & base, ofColor & highlight)
{
	int index = ofRandom(colorSchemes["stones"].size());
	ofJson c = colorSchemes["stones"][index]["base"];
	base = ofColor(c[0],c[1],c[2]);
	c = colorSchemes["stones"][index]["highlight"];
	highlight = ofColor(c[0], c[1], c[2]);
}
