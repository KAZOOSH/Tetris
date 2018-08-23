#pragma once
#include "Rule.h"
#include "GameObjectContainer.h"
#include "InfoPanel.h"


/// \brief controles game start and cleanup
class GameControlRule :
	public Rule
{
public:
	GameControlRule(GameParameters* params, GameObjectContainer* gameObjects);
	~GameControlRule();

	void applyRule();
	void draw();


	void changeGamestate(string message);
	void onGamestateChanged(ofJson& message);
	void onPaddleMove(ofJson& message);

	int getStateTime(string stateName);

private:
	ofxFontStash mainFont;
	ofxFontStash subFont;

	ofJson stateDescription;
	string gamestate = "idle";
	uint64_t startState = 0;
	map<string, InfoPanel> panels;

	vector<bool> paddleReady;
	GameObjectContainer* gameObjects;

};

