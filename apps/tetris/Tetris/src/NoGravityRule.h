#pragma once
#include "Rule.h"
#include "TetrisStone.h"
class NoGravityRule :
    public Rule
{
public:
    NoGravityRule(GameParameters* params,int runtime);
    bool gravityDisabled = false;
    void applyRule();
};

