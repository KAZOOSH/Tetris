#pragma once
#include "Rule.h"

/// \brief controles game start and cleanup
class GameControlRule :
	public Rule
{
public:
	GameControlRule(GameParameters* params);
	~GameControlRule();

	void applyRule();
	void draw();

private:
	string gamestate = "idle";
};

