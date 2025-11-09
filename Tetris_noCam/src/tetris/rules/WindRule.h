#pragma once
#include "GameRule.h"
#include "TetrisStone.h"
class WindRule :
	public GameRule
{
public:
	WindRule(shared_ptr<GameComponents> components,int runtime);

	void applyRule();
};

