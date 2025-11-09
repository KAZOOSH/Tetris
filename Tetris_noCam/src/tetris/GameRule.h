#pragma once
#include "Rule.h"
#include "GameComponents.h"

class GameRule :
	public Rule
{
public:
	GameRule(string name, shared_ptr<GameComponents> components_, int runtime = 0);

protected:
	shared_ptr<GameComponents> components;
};

