#include "StoneControlRule.h"



StoneControlRule::StoneControlRule(shared_ptr<GameComponents> components) :GameRule("StoneControlRule", components)
{
	//ofAddListener(params->gameEvent, this, &DeleteOutOfScreenRule::onGameEvent);
}


StoneControlRule::~StoneControlRule()
{
}

void StoneControlRule::enableGravity()
{
	auto gameControl = components->gameControl()->gameControl;
	for (auto& obj : gameControl) {
		if (obj->getName() == "TetrisStone") {
			shared_ptr<TetrisStone> stone = std::static_pointer_cast<TetrisStone>(obj);
			if (!stone->collided) {
				for (auto& body : stone->getBody()) {
					int velocity = components->params()->settings["tetrisStone"]["startVelocity"].get<int>();

					int tLeft = components->events()->tGamestateChange + components->params()->settings["gameplay"]["maxDuration"].get<int>() - ofGetElapsedTimeMillis();

					if (tLeft < components->params()->settings["gameplay"]["startHeightReduction"].get<int>()) {
						velocity = ofMap(tLeft, components->params()->settings["gameplay"]["startHeightReduction"].get<int>(), 0,
							components->params()->settings["tetrisStone"]["startVelocity"].get<int>(), components->params()->settings["tetrisStone"]["endVelocity"].get<int>());
					}

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


/**
* setTetrisStoneRelativeToPaddlePosition
* set Stone Position and get towerheight
*/
void StoneControlRule::setTetrisStoneRelativeToPaddlePosition()
{
	int towerHeightPaddleLeft = 0;
	int towerHeightPaddleRight = 0;

	// get Paddles
	shared_ptr<Paddle> paddleLeft = components->gameControl()->getPaddle(Paddle::paddleNameLeft);
	shared_ptr<Paddle> paddleRight = components->gameControl()->getPaddle(Paddle::paddleNameRight);

	// iterate over tetrisstones
	for (size_t i = components->gameControl()->gameControl.size() - 1; i > 0; --i) {
		if (components->gameControl()->gameControl[i]->getName() == "TetrisStone") {
			if (components->gameControl()->gameControl[i]) {
				shared_ptr<TetrisStone> stone = std::static_pointer_cast<TetrisStone>(components->gameControl()->gameControl[i]);

				int pId = stone->getPlayerId();
				int y = 10000;


				if (stone->getBody().size()>0 && stone->collided) {
					// get Height if its part of the tower
					if (stone->getIsPartOfTower()) {
						y = stone->getBody()[0]->getPosition().y;
					}

					if (pId == 1) {
						ofVec2f plp = paddleLeft->getPaddleBodyPosition();
						float distanceToPaddleOrOtherTetrisStone = getMinimalDistanceToOtherTowerStonesOrPaddle(stone, paddleLeft);
						stone->updateRelativeToPaddlePosition(plp, distanceToPaddleOrOtherTetrisStone);
						towerHeightPaddleLeft = max(towerHeightPaddleLeft, max(0, (int)plp.y - y));
						paddleLeft->towerHeight = towerHeightPaddleLeft;

					} else if (pId == 2) {
						ofVec2f prp = paddleRight->getPaddleBodyPosition();
						float distanceToPaddleOrOtherTetrisStone = getMinimalDistanceToOtherTowerStonesOrPaddle(stone, paddleRight);
						stone->updateRelativeToPaddlePosition(prp, distanceToPaddleOrOtherTetrisStone);
						towerHeightPaddleRight = max(towerHeightPaddleRight, max(0, (int)prp.y - y));
						paddleRight->towerHeight = towerHeightPaddleRight;
					}
				}
			}
		};
	}
}

float StoneControlRule::getMinimalDistanceToOtherTowerStonesOrPaddle(shared_ptr<TetrisStone> stone, shared_ptr<Paddle> paddle)
{
	float minimumDistance = 100000;
	float distance = 0;
	// check all stones and set sistance if its
	for (size_t i = components->gameControl()->gameControl.size() - 1; i > 0; --i) {
		if (components->gameControl()->gameControl[i]->getName() == "TetrisStone" && components->gameControl()->gameControl[i]->getId() != stone->getId()) {
			shared_ptr<TetrisStone> otherStone = std::static_pointer_cast<TetrisStone>(components->gameControl()->gameControl[i]);
			if (otherStone->getBody().size()>0 && otherStone->getIsPartOfTower()) {
				distance = (stone->getBody()[0]->getPosition() - otherStone->getBody()[0]->getPosition()).length();
				if (distance < minimumDistance) {
					minimumDistance = distance;
				}
			}
		}
	}
	distance = (paddle->getPaddleBodyPosition() - stone->getBody()[0]->getPosition()).length();
	if (distance < minimumDistance) {
		minimumDistance = distance;
	}
	return minimumDistance;
}

void StoneControlRule::applyRule()
{
	enableGravity();
	setTetrisStoneRelativeToPaddlePosition();
	
}