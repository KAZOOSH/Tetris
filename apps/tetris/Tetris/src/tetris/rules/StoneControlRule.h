#pragma once
#include "Rule.h"
#include "TetrisStone.h"
class StoneControlRule :
	public Rule
{
public:
	StoneControlRule(GameParameters* params);
	~StoneControlRule();

	void applyRule();
};

