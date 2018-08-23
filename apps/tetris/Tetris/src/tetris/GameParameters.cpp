#include "GameParameters.h"



GameParameters::GameParameters()
{
	ofFile fileParams("_Tetris/params.json");
	if (fileParams.exists()) {
		fileParams >> params;
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

void GameParameters::notifyGameEvent(ofJson eventText)
{
	ofNotifyEvent(gameEvent, eventText);

	if (eventText["function"] != nullptr && eventText["function"] == "gamestate") {
		gamestate = eventText["gamestate"].get<string>();
	}
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

void GameParameters::setRandomNextEffect(){
	if (nextEffectList.size() == 0) {
		for (int i = 0; i < effects.size(); i++) {
			nextEffectList.push_back(effects[i]["state"]);
		}
		std::random_shuffle(nextEffectList.begin(), nextEffectList.end());
	}

	if (getEffect(nextEffectList.back())["type"] == "world") {
		ofJson out;
		out["function"] = "createWorldEffect";
		out["params"] = getEffect(nextEffectList.back());
		notifyGameEvent(out);

	} else {
		nextCreationRule[0] = nextEffectList.back();
		nextCreationRule[1] = nextEffectList.back();
	}
	nextEffectList.pop_back();
}

void GameParameters::setNextEffect(string name)
{
	if (getEffect(name)["type"] == "world") {
		ofJson out;
		out["function"] = "createWorldEffect";
		out["params"] = getEffect(name);
		notifyGameEvent(out);

	} else {
		nextCreationRule[0] = name;
		nextCreationRule[1] = name;
	}
}

ofJson GameParameters::getEffect(string effect)
{
	for (auto& e : effects) {
		if (e["state"] == effect) return e;
	}
	return ofJson();
}
