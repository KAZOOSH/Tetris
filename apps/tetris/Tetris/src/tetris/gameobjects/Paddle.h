#pragma once
#include "ofMain.h"
#include "GameObject.h"
#include "ofxBox2d.h"

class Paddle : public GameObject
{
public:
	Paddle(string name);
	~Paddle();

	void render();
	void setPosition(int x, int y, float rotation);

private:
	
};

