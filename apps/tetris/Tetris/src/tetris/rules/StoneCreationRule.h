#pragma once
#include "GameRule.h"
#include "TetrisStone.h"

class StoneCreationRule : public GameRule
{
public:
	StoneCreationRule(shared_ptr<GameComponents> components);
	~StoneCreationRule();

	void applyRule();

protected:
	void produceStoneByIntervall();
	void produceStone(int player);
	shared_ptr<TetrisStone> getLastCreatedStone(int playerId);
	void collisionHandler(TetrisStone* stone);
	void contactStart(ofxBox2dContactArgs &e);

private:
	uint64_t produceStoneIntervallInMillis = 3000;
	uint64_t lastStoneProductionTimePlayer1 = 0;
	uint64_t lastStoneProductionTimePlayer2 = 0;
};

