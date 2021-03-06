#pragma once
#include "GameRule.h"
#include "GameComponents.h"
#include "InfoPanel.h"


/// \brief controles game start and cleanup
class GameControlRule :
	public GameRule
{
public:
	GameControlRule(shared_ptr<GameComponents> components);
	~GameControlRule();

	void applyRule();
	void draw();


	void changeGamestate(string message);
	void onGamestateChanged(ofJson& message);
	void onPaddleMove(ofJson& message);

	int getStateTime(string stateName);

	void drawFadeOut();

private:
	ofxFontStash mainFont;
	ofxFontStash subFont;

	ofJson stateDescription;
	string gamestate = "idle";
	uint64_t startState = 0;
	map<string, InfoPanel> panels;
	map<int, InfoPanel> countdown;
	int lastCountdownSwitch=0;

	vector<bool> paddleReady;
	shared_ptr<GameObjectContainer> gameControl;

};

