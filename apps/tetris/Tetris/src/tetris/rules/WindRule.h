#pragma once
#include "Rule.h"
class WindRule :
	public Rule
{
public:
	WindRule(GameParameters* params,int runtime);

	void applyRule();
};

