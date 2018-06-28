#include "GameControl.h"


GameControl::GameControl(shared_ptr<GameObjects> objects_)
{
	objects = objects_;
}

GameControl::~GameControl()
{
}

void GameControl::update()
{

	//apply current rules
	for (auto& rule : objects->rules) {
		rule->applyRule();
	}
	objects->physics.update();
}
