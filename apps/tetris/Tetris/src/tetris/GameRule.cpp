#include "GameRule.h"

GameRule::GameRule(string name, shared_ptr<GameComponents> components_, int runtime):
	Rule(name, runtime)
{
	components = components_;
}



