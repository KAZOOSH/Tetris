#include "StoneCreationRule.h"
#include "GameFactory.h"


StoneCreationRule::StoneCreationRule(shared_ptr<GameComponents> components) :GameRule("StoneControlRule", components)
{
	produceStoneIntervallInMillis = components->params()->settings["tetrisStone"]["produceEveryMilliseconds"].get<uint64_t>();
	ofAddListener(components->gameControl()->physics.contactStartEvents, this, &StoneCreationRule::contactStart);
}


StoneCreationRule::~StoneCreationRule()
{
}

void StoneCreationRule::applyRule() {
	if (components->events()->gamestate == "game") produceStoneByIntervall();
}

void StoneCreationRule::produceStoneByIntervall() {
	if (lastStoneProductionTimePlayer1 + produceStoneIntervallInMillis < ofGetElapsedTimeMillis()) {
		produceStone(1);
	}
	if (lastStoneProductionTimePlayer2 + produceStoneIntervallInMillis < ofGetElapsedTimeMillis()) {
		produceStone(2);
	}
}

void StoneCreationRule::produceStone(int player) {

	if (getLastCreatedStone(player) == nullptr || getLastCreatedStone(player)->getBody()[0]->getPosition().y >500) {
		//create stone
		auto stone = GameFactory::makeTetrisStone(components, components->events()->nextCreationRule[player - 1]);
		stone->setPlayer(player);

		components->soundPlayer()->play("newBlock", player);

		//notify effect if present
		if (components->events()->nextCreationRule[player - 1] != "base") {
			ofJson out;
			out["function"] = "effect";
			out["effect"] = components->events()->nextCreationRule[player - 1];
			out["player"] = player;
			components->events()->notifyGameEvent(out);
		}

		if (components->events()->nextCreationRule[player - 1] == "quicky") {
			// collided stones get gravity effects
			stone->collide();
			stone->getBody()[0]->addForce(ofVec2f(0, 1), 10000);
		}
		if (components->events()->nextCreationRule[player - 1] == "rotary") {
			// collided stones get gravity effects
			stone->collide();
			stone->getBody()[0]->addImpulseForce(stone->getBody()[0]->getB2DPosition() + ofVec2f(10, 0), ofVec2f(0, 5000));
		}

		// set stone effect for active player back to base
		components->events()->nextCreationRule[player - 1] = "base";

		int minimumDistanceToBorder = 200;
		int middle = components->params()->settings["width"].get<int>() / 2;
		if (player == 1) {
			lastStoneProductionTimePlayer1 = ofGetElapsedTimeMillis();
			stone->setPosition(ofVec2f(ofRandom(minimumDistanceToBorder, middle - minimumDistanceToBorder), 0));
		}
		if (player == 2) {
			lastStoneProductionTimePlayer2 = ofGetElapsedTimeMillis();
			stone->setPosition(ofVec2f(ofRandom(middle + minimumDistanceToBorder, 2 * middle - minimumDistanceToBorder), 0));
		}
		components->gameControl()->addGameObject(stone);
		//components->objects()->getRule("DeleteOutOfScreenRule")->addObject(stone);
		//components->objects()->getRule("StoneControlRule")->addObject(stone);
		components->events()->registerEraseEvent(stone->eraseEvent);
	} else {
		if (player == 1) {
			lastStoneProductionTimePlayer1 = ofGetElapsedTimeMillis() + produceStoneIntervallInMillis / 2;
		}
		if (player == 2) {
			lastStoneProductionTimePlayer2 = ofGetElapsedTimeMillis()
				+ produceStoneIntervallInMillis / 2;
		}
	}
}

shared_ptr<TetrisStone> StoneCreationRule::getLastCreatedStone(int playerId) {
	for (size_t i = components->gameControl()->gameControl.size() - 1; i > 0; --i) {
		shared_ptr<TetrisStone> stone = std::static_pointer_cast<TetrisStone>(components->gameControl()->gameControl[i]);

		if (stone->getName() == "TetrisStone") {
			int pId = stone->getPlayerId();
			if (pId == playerId) {
				return stone;
			}
		};
	}
	return nullptr;
}


void StoneCreationRule::collisionHandler(TetrisStone* stone) {
	int minimumYPosToCreateStoneOnCollide = 1000;
	//check colliding objects produce new stone immediately on first collision of last created stone
	if (stone->getBody().size()>0) {

		if (!stone->collided) {
			if (stone->getBody()[0]->getPosition().y > minimumYPosToCreateStoneOnCollide) {
				if (stone->getPlayerId() == 1) {
					lastStoneProductionTimePlayer1 = 0;
				} else if (stone->getPlayerId() == 2) {
					lastStoneProductionTimePlayer2 = 0;
				}
			}
			stone->collide();
		}
	}
}

void StoneCreationRule::contactStart(ofxBox2dContactArgs &e) {
	if (e.a != nullptr && e.b != nullptr) {
		TetrisStone * stone;

		if ((TetrisStone*)e.a->GetBody()->GetUserData()) {
			stone = (TetrisStone*)e.a->GetBody()->GetUserData();
			collisionHandler(stone);
		}

		if ((TetrisStone*)e.b->GetBody()->GetUserData()) {
			stone = (TetrisStone*)e.b->GetBody()->GetUserData();
			collisionHandler(stone);
		}
	}
}