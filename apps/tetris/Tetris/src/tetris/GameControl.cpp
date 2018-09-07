#include "GameControl.h"


GameControl::GameControl(shared_ptr<GameObjectContainer> objects)
{
	objectContainer = objects;
}

GameControl::~GameControl()
{
}

void GameControl::update()
{	
	//update paddles
	for (auto& obj : objectContainer->paddles) {
		obj->updatePosition();
	}

	//apply current rules
	for (auto& rule : objectContainer->rules) {
		rule->applyRule();
	}
	//update physics
	objectContainer->physics.update();

	//remove Elements erased elements
	removeErasedElements();

	//remove rules out of runtime
	removeDeprecatedRules();
}

void GameControl::render()
{
	for (auto& obj : objectContainer->objects) {
		obj->render();
	}

	for (auto& rule : objectContainer->rules) {
		rule->draw();
	}
}

void GameControl::onEraseEvent(long & id)
{
	toDeleteIds.push_back(id);
}

void GameControl::registerEraseEvent(ofEvent<long>& ev)
{
	ofAddListener(ev, this, &GameControl::onEraseEvent);
}

void GameControl::reloadRenderer()
{
	for (auto& obj : objectContainer->objects) {
		obj->reloadRenderer();
	}
}

void GameControl::removeErasedElements()
{
	for (auto& id : toDeleteIds) {
		
		auto position = find_if(objectContainer->objects.begin(), objectContainer->objects.end(),
			[&id](const shared_ptr<GameObject> elem) { return elem->getId() == id; });
		
		if (position != objectContainer->objects.end()) {
			/*for (auto& r : objectContainer->rules) {
				r->removeObject(id);
			}*/
			
			//cout << "erase remove " << id << "  " << toDeleteIds.size() << endl;
			objectContainer->objects.erase(position);
		}
	}
	toDeleteIds.clear();
	
}

void GameControl::removeDeprecatedRules()
{
	vector<int> toDel;
	auto now = ofGetElapsedTimeMillis();
	size_t i = 0;
	for (auto& rule : objectContainer->rules) {
		if (rule->getRuntime() != 0 && now - rule->getCreationTime() > rule->getRuntime()) {
			toDel.push_back(i);
		}
		++i;
	}

	for (std::vector<int>::size_type i = toDel.size() - 1;
		i != (std::vector<int>::size_type) - 1; i--) {
		objectContainer->rules.erase(objectContainer->rules.begin() + toDel[i]);
	}
}
