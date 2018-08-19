#pragma once
#include "Rule.h"
#include "ofxFontStash.h"
#include "ofxEasing.h"

class TextField {
public:
	TextField(ofFbo texture_, ofVec2f size_, ofVec2f position_) {
		texture = texture_;
		size = size_;
		position = position_;
	}
	ofFbo texture;
	ofVec2f size;
	ofVec2f position;
};

class InfoPanel {
public:
	InfoPanel() {};
	InfoPanel(ofJson settings, ofJson description, ofxFontStash* fontMain, ofxFontStash* fontSub);

	void start();
	void draw(int x = 0);
	
	TextField* mainText;
	TextField* subText;

	TextField* createTextField(ofxFontStash* font, string text, int y, int h, int wScreen);

private:
	uint64_t tStart = 0;
	int duration;
};

/// \brief controles game start and cleanup
class GameControlRule :
	public Rule
{
public:
	GameControlRule(GameParameters* params);
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
};

