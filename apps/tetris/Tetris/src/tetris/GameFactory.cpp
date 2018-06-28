#include "GameFactory.h"

shared_ptr<Paddle> GameFactory::makePaddle(shared_ptr<GameObjects> objects, ofJson config)
{
	shared_ptr<Paddle> ret = shared_ptr<Paddle>(new Paddle(ofJson()));
	ret->body->setup(objects->physics.getWorld(), 10, 10, 150, 10);
	objects->addRenderObject(ret);
	objects->paddles.push_back(ret);
	return ret;
}
