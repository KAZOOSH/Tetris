#include "GameControlRule.h"



GameControlRule::GameControlRule(GameParameters* params):Rule("GameControlRule",params)
{
}


GameControlRule::~GameControlRule()
{
}

void GameControlRule::applyRule()
{
}

void GameControlRule::draw()
{
	ofSetColor(255);
	ofDrawBitmapString(gamestate, 200, 200);

	if (gamestate == "idle") {
		
	}else if (gamestate == "waiting_for_players") {

	}else if (gamestate == "countdown") {

	}else if (gamestate == "game") {

	}else if (gamestate == "end") {

	}
}

void GameControlRule::onGamestateChange(ofJson & message)
{
	if (message["function"] != nullptr && message["function"] == "gamestate") {
		gamestate = message["gamestate"].get<string>();
	}
}
