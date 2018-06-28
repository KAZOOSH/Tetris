#include "Paddle.h"



Paddle::Paddle(ofJson params):RenderObject()
{
	body = shared_ptr<ofxBox2dRect>(new ofxBox2dRect);
	body->enableGravity(false);
}

Paddle::~Paddle()
{
}

void Paddle::render()
{
	body->draw();
}

void Paddle::setPosition(int x, int y, float rotation)
{
	body->setPosition(x, y);
	body->setRotation(rotation);
}
