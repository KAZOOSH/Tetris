#include "GameObjectContainer.h"



GameObjectContainer::GameObjectContainer()
{
}


GameObjectContainer::~GameObjectContainer()
{
}

void GameObjectContainer::initPhysics()
{
	physics.init();
	physics.setGravity(0, 10);
	physics.createGround();
	physics.setFPS(60.0);
}

void GameObjectContainer::addGameObject(shared_ptr<GameObject> object)
{
	gameObjects.push_back(object);
}