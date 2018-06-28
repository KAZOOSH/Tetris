#pragma once
#include "ofMain.h"
#include "RenderObject.h"
#include "ofxBox2d.h"

class Paddle : public RenderObject 
{
public:
	Paddle(ofJson params);
	~Paddle();

	void render();
	void setPosition(int x, int y, float rotation);

	shared_ptr<ofxBox2dRect> body;
private:
	
};

