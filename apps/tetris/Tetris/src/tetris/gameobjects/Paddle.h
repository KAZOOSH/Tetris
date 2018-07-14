#pragma once
#include "ofMain.h"
#include "GameObject.h"
#include "ofxBox2d.h"

class PaddlePosition {
public:
	void update(ofVec2f pos, float rot) {
		position = pos;
		rotation = rot;
		hasChanged = true;
	}
	ofVec2f position;
	float rotation;
	bool hasChanged = false;
};

class Paddle : public GameObject
{
public:
	Paddle(string name);
	~Paddle();

	void render();
	void setPosition(int x, int y, float rotation);
	void updatePosition();

private:
	PaddlePosition position;
};

