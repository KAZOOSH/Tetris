#include "StoneControlRule.h"



StoneControlRule::StoneControlRule(shared_ptr<GameComponents> components) :GameRule("StoneControlRule", components)
{
	//ofAddListener(params->gameEvent, this, &DeleteOutOfScreenRule::onGameEvent);
}


StoneControlRule::~StoneControlRule()
{
}

void StoneControlRule::applyRule()
{
	auto objects = components->objects()->objects;
	for (auto& obj : objects) {
		if (obj->getName() == "TetrisStone") {
			shared_ptr<TetrisStone> stone = std::static_pointer_cast<TetrisStone>(obj);
			if (!stone->collided) {
				for (auto& body : stone->getBody()) {
					int velocity = components->params()->settings["tetrisStone"]["startVelocity"].get<int>();
					body->setVelocity(0, velocity);
					body->enableGravity(false);
				};
			} else {
				for (auto& body : stone->getBody()) {
					body->enableGravity(true);
				};
			}
		}
	}
}
