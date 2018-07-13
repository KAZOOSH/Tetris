#include "Paddle.h"



Paddle::Paddle(string name):GameObject(name)
{
	shared_ptr<ofxBox2dRect> body = shared_ptr<ofxBox2dRect>(new ofxBox2dRect);
	body->enableGravity(false);
	addBody(body);
}

Paddle::~Paddle()
{
}

void Paddle::render()
{
	//static_pointer_cast<ofxBox2dRect>(body.begin())->draw();

}

void Paddle::setPosition(int x, int y, float rotation)
{
	//body->setPosition(x, y);
	//body->setRotation(rotation);
}
