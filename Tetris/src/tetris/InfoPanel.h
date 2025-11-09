#pragma once
#include "ofMain.h"
#include "ofxEasing.h"
#include "ofxFontStash.h"

enum panning {
	center,
	left,
	right
};

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

	void setPanning(panning direction);
	void setPlayer(int player); //0 is both

	TextField* mainText;
	TextField* subText;

	TextField* createTextField(ofxFontStash* font, string text, int y, int h, int wScreen);

	int getPlayer();
	int getDuration();
	uint64_t getStart();

private:
	uint64_t tStart = 0;
	int duration;
	ofSoundPlayer sound;
	panning playerPanning = center;
	int player = 0;
};