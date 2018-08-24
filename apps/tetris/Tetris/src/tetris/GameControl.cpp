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

	//remove rules out of runtime
	removeDeprecatedRules();
}

void GameControl::render()
{
	for (auto& obj : objects->gameControl) {
		obj->render();
	}

	for (auto& rule : objects->rules) {
		rule->draw();
	}
}

void GameControl::onEraseEvent(long & id)
{
	toDeleteIds.push_back(id);
}

void GameControl::registerEraseEvent(ofEvent<long> ev)
{
	ofAddListener(ev, this, &GameControl::onEraseEvent);
}

void GameControl::reloadRenderer()
{
	for (auto& obj : objects->gameControl) {
		obj->reloadRenderer();
	}
}

void GameControl::removeErasedElements()
{
	for (auto& id : toDeleteIds) {
		cout << "erase remove " << id << "  " << toDeleteIds.size() << endl;
		auto position = find_if(objects->gameControl.begin(), objects->gameControl.end(),
			[&id](const shared_ptr<GameObject> elem) { return elem->getId() == id; });
		
		if (position != objects->gameControl.end()) {
			objects->gameControl.erase(position);
		}
	}
	
}

void GameControl::removeDeprecatedRules()
{
	vector<int> toDel;
	auto now = ofGetElapsedTimeMillis();
	size_t i = 0;
	for (auto& rule : objects->rules) {
		if (rule->getRuntime() != 0 && now - rule->getCreationTime() > rule->getRuntime()) {
			toDel.push_back(i);
		}
		++i;
	}

	for (std::vector<int>::size_type i = toDel.size() - 1;
		i != (std::vector<int>::size_type) - 1; i--) {
		objects->rules.erase(objects->rules.begin() + toDel[i]);
	}
}
