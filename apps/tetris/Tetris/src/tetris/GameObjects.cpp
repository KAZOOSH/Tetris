#include "GameObjects.h"



GameObjects::GameObjects()
{
}


GameObjects::~GameObjects()
{
}

void GameObjects::initPhysics()
{
	physics.init();
	physics.setGravity(0, 10);
	physics.createGround();
	physics.setFPS(60.0);
}

void GameObjects::addRule(shared_ptr<Rule> rule)
{
	rules.push_back(rule);
}

void GameObjects::addRenderObject(shared_ptr<RenderObject> object)
{
	renderObjects.push_back(object);
}
