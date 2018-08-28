#pragma once
#include "Rule.h"
#include "TetrisStone.h"
class WindRule :
	public Rule
{
public:
	WindRule(GameParameters* params,int runtime);

	void applyRule();
};

