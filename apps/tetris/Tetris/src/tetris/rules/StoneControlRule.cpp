#include "StoneControlRule.h"



StoneControlRule::StoneControlRule(GameParameters* params) :Rule("StoneControlRule", params)
{
	//ofAddListener(params->gameEvent, this, &DeleteOutOfScreenRule::onGameEvent);
}


StoneControlRule::~StoneControlRule()
{
}

void StoneControlRule::applyRule()
{
	for (auto& obj : objects) {
		if (obj->getName() == "TetrisStone") {
			shared_ptr<TetrisStone> stone = std::static_pointer_cast<TetrisStone>(obj);
			if (!stone->collided) {
				for (auto& body : stone->getBody()) {
					int velocity = params->params["tetrisStone"]["startVelocity"].get<int>();
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
