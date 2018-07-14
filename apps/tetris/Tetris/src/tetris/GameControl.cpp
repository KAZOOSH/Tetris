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
	//update paddles
	for (auto& obj : objects->paddles) {
		obj->updatePosition();
	}

	//apply current rules
	for (auto& rule : objects->rules) {
		rule->applyRule();
	}
	//update physics
	objects->physics.update();

	//remove Elements erased elements
	removeErasedElements();
}

void GameControl::render()
{
	for (auto& obj : objects->gameObjects) {
		obj->render();
	}
}

void GameControl::onEraseEvent(long & id)
{
	toDeleteIds.push_back(id);
}

void GameControl::removeErasedElements()
{
	for (auto& id : toDeleteIds) {
		auto position = find_if(objects->gameObjects.begin(), objects->gameObjects.end(),
			[&id](const shared_ptr<GameObject> elem) { return elem->getId() == id; });
		if (position != objects->gameObjects.end()) {
			objects->gameObjects.erase(position);
		}
	}
	
}
