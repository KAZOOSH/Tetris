#pragma once
#include "GameRule.h"
#include "TetrisStone.h"

class StoneCreationRule : public GameRule
{
	struct Kosmonaut {
		ofTexture texture;
		ofVec2f position;
		ofVec2f dimension;
		float speed;
		float dx;
	};

public:
	StoneCreationRule(shared_ptr<GameComponents> components);
	~StoneCreationRule();

	void applyRule();
	void draw();

protected:
	void produceStoneByIntervall();
	void produceStone(int player);
	shared_ptr<TetrisStone> getLastCreatedStone(int playerId);
	void collisionHandler(TetrisStone* stone);
	void contactStart(ofxBox2dContactArgs &e);

private:


	void updateStoneCreatorPosition(int player);

	uint64_t produceStoneIntervallInMillis = 3000;
	uint64_t lastStoneProductionTimePlayer1 = 0;
	uint64_t lastStoneProductionTimePlayer2 = 0;

	int minimumDistanceToBorder = 200;
	int middle;


	//rendering
	vector<Kosmonaut> kosmonauts;

	void loadKosmonaut(int player, ofJson desc);
};

