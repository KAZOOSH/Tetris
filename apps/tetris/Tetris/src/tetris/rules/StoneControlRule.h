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
};

