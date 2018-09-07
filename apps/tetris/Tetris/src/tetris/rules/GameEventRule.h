#pragma once
#include "GameRule.h"
#include "ofxFontStash.h"
#include "InfoPanel.h"

class GameEventRule :
	public GameRule
{
public:
	GameEventRule(shared_ptr<GameComponents> components);
	~GameEventRule();

	void applyRule();
	void draw();

	void onGameEvent(ofJson& eventMessage);

private:


	map<string, vector<InfoPanel>> panels;
	ofxFontStash mainFont;
	ofxFontStash subFont;

	vector<vector<string>> currentEvents;

};

