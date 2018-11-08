#pragma once
#include "GameRule.h"
#include "TetrisStone.h"
class StoneControlRule :
	public GameRule
{
public:
	StoneControlRule(shared_ptr<GameComponents> components);
	~StoneControlRule();
	void applyRule();

	

protected:
	void enableGravity();
	void setTetrisStoneRelativeToPaddlePosition();
	float getMinimalDistanceToOtherTowerStonesOrPaddle(shared_ptr<TetrisStone> stone, shared_ptr<Paddle> paddle);
};

