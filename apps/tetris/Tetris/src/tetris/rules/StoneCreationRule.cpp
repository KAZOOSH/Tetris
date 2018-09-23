#include "StoneCreationRule.h"
#include "GameFactory.h"


StoneCreationRule::StoneCreationRule(shared_ptr<GameComponents> components) :GameRule("StoneControlRule", components)
{
	produceStoneIntervallInMillis = components->params()->settings["tetrisStone"]["produceEveryMilliseconds"].get<uint64_t>();
	ofAddListener(components->gameControl()->physics.contactStartEvents, this, &StoneCreationRule::contactStart);

	middle = components->params()->settings["width"].get<int>() / 2;

	//init stone creator

	loadKosmonaut(1,components->params()->settings["stoneCreator"]["textures"][0]);
	loadKosmonaut(2,components->params()->settings["stoneCreator"]["textures"][1]);

	
}


StoneCreationRule::~StoneCreationRule()
{
}

void StoneCreationRule::applyRule() {

	if (components->events()->gamestate == "game") {

		int tLeft = components->events()->tGamestateChange + components->params()->settings["gameplay"]["maxDuration"].get<int>() - ofGetElapsedTimeMillis();

		if (tLeft < components->params()->settings["gameplay"]["startHeightReduction"].get<int>()) {
			produceStoneIntervallInMillis = ofMap(tLeft, components->params()->settings["gameplay"]["startHeightReduction"].get<int>(), 0,
				components->params()->settings["tetrisStone"]["produceEveryMilliseconds"].get<uint64_t>(), components->params()->settings["tetrisStone"]["produceEveryMillisecondsMin"].get<uint64_t>());

		}

		updateStoneCreatorPosition(1);
		updateStoneCreatorPosition(2);
		produceStoneByIntervall();
	} else if (components->events()->gamestate == "afterEnd") {
		produceStoneIntervallInMillis = components->params()->settings["tetrisStone"]["produceEveryMilliseconds"].get<uint64_t>();
	}
}

void StoneCreationRule::draw()
{
	if (components->events()->gamestate == "game") {
	ofPushStyle();
	ofSetColor(255);

	int tLeft = components->events()->tGamestateChange + components->params()->settings["gameplay"]["maxDuration"].get<int>() - ofGetElapsedTimeMillis();

	if (tLeft < components->params()->settings["gameplay"]["startHeightReduction"].get<int>()) {
		if ((tLeft / 300) % 2) ofSetColor(255, 100, 100);
	}

	for (auto& kosmonaut : kosmonauts) {
		kosmonaut.texture.draw(kosmonaut.position.x-kosmonaut.dimension.x*0.5 + kosmonaut.dx, kosmonaut.position.y, kosmonaut.dimension.x, kosmonaut.dimension.y);
	}
	ofPopStyle();
	}
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

		stone->setPosition(ofVec2f(kosmonauts[player -1].position.x, kosmonauts[player - 1].dimension.y*0.75));

		components->gameControl()->addGameObject(stone);
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

///\brief: move stone creators laika and sigi
void StoneCreationRule::updateStoneCreatorPosition(int player){
	kosmonauts[player - 1].position.x += kosmonauts[player - 1].speed;

	int xMin = player == 1 ? minimumDistanceToBorder : middle + minimumDistanceToBorder;
	int xMax = player == 1 ? middle - minimumDistanceToBorder : 2 * middle - minimumDistanceToBorder;

	if (kosmonauts[player - 1].position.x < xMin || kosmonauts[player - 1].position.x > xMax) {
		kosmonauts[player - 1].speed *= -1;
	}

}

void StoneCreationRule::loadKosmonaut(int player, ofJson desc)
{
	kosmonauts.push_back(Kosmonaut());

	ofImage img;
	img.load(desc["pic"].get<string>());
	kosmonauts.back().texture = img.getTexture();

	kosmonauts.back().dimension.x = desc["width"];
	kosmonauts.back().dimension.y = kosmonauts.back().dimension.x *img.getHeight() / img.getWidth();

	kosmonauts.back().dx = kosmonauts.back().dimension.x * desc["dx"].get<float>();

	kosmonauts.back().speed = components->params()->settings["stoneCreator"]["speed"];

	int dx = 0;
	if (player == 2) dx = components->params()->settings["width"].get<int>()*0.5;
	kosmonauts.back().position.x = dx + ofRandom(minimumDistanceToBorder, middle - minimumDistanceToBorder);
	kosmonauts.back().position.y = 40;
}
