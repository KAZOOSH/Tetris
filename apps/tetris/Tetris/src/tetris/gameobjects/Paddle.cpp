#include "Paddle.h"



Paddle::Paddle(string name):GameObject(name)
{
}

Paddle::~Paddle()
{
}

///\brief for testing perpuses, we should finally use a renderer for this
void Paddle::render()
{
	static_pointer_cast<ofxBox2dRect>(body[0])->draw();

}

void Paddle::setPosition(int x, int y, float rotation)
{
	position.position = ofVec2f(x, y);
	position.rotation = rotation;
	position.hasChanged = true;
}

void Paddle::updatePosition()
{
	if (position.hasChanged) {
		static_pointer_cast<ofxBox2dRect>(body[0])->setPosition(position.position.x, position.position.y);
		static_pointer_cast<ofxBox2dRect>(body[0])->setRotation(position.rotation);
		position.hasChanged = false;
	}
}
