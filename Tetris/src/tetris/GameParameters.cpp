#include "GameParameters.h"



GameParameters::GameParameters()
{
	ofFile fileParams("_Tetris/params.json");
	if (fileParams.exists()) {
		fileParams >> settings;
	} else {
		ofLogError(" _Tetris/params.json does not exist");
	}

	ofFile fileSchemes("_Tetris/colorSchemes.json");
	if (fileSchemes.exists()) {
		fileSchemes >> colorSchemes;
	} else {
		ofLogError(" _Tetris/colorSchemes.json does not exist");
	}

	ofFile fileEffects("_Tetris/effects.json");
	if (fileEffects.exists()) {
		fileEffects >> effects;
	} else {
		ofLogError(" _Tetris/effects.json does not exist");
	}
}


GameParameters::~GameParameters()
{
}



void GameParameters::getRandomColorScheme(ofColor & base, ofColor & highlight)
{
	int index = ofRandom(colorSchemes["stones"].size());
	ofJson c = colorSchemes["stones"][index]["base"];
	base = ofColor(c[0],c[1],c[2]);
	c = colorSchemes["stones"][index]["highlight"];
	highlight = ofColor(c[0], c[1], c[2]);
}



ofJson GameParameters::getEffect(string effect)
{
	for (auto& e : effects) {
		if (e["state"] == effect) return e;
	}
	return ofJson();
}
