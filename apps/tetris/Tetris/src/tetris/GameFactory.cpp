#include "GameFactory.h"

shared_ptr<Paddle> GameFactory::makePaddle(shared_ptr<GameObjectContainer> objects, ofJson config)
{
	shared_ptr<Paddle> ret = shared_ptr<Paddle>(new Paddle(ofJson()));
	ret->body->setup(objects->physics.getWorld(), 10, 10, 150, 10);
	objects->addRenderObject(ret);
	objects->paddles.push_back(ret);
	return ret;
}

shared_ptr<BasicStone> GameFactory::makeBasicStone(shared_ptr<GameObjectContainer> objects, ofJson config, shared_ptr<PolygonRenderer> renderer)
{
	shared_ptr<ofxBox2dRect> body = shared_ptr<ofxBox2dRect>(new ofxBox2dRect);
	body->setup(objects->physics.getWorld(), 10, 10, 150, 10);

	shared_ptr<BasicStone> ret = shared_ptr<BasicStone>(new BasicStone(body, renderer));

	objects->addRenderObject(renderer);
	//  add to game objects objects->paddles.push_back(ret);
	return ret;
}
