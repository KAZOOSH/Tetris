#include "GameControl.h"


GameControl::GameControl(shared_ptr<GameObjectContainer> objects_)
{
	objects = objects_;
}

GameControl::~GameControl()
{
}

void GameControl::update()
{

	//apply current rules
	for (auto& obj : objects->gameObjects) {
		obj->applyRules();
	}
	//update physics
	objects->physics.update();
}

void GameControl::render()
{
	for (auto& obj : objects->gameObjects) {
		obj->render();
	}
}
