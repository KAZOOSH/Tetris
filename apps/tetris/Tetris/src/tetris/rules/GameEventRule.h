#pragma once
#include "Rule.h"
#include "ofxFontStash.h"
#include "InfoPanel.h"

class GameEventRule :
	public Rule
{
public:
	GameEventRule(GameParameters* params);
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

