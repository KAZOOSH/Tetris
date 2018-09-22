#pragma once
#include "GameRule.h"
#include "TetrisStone.h"
class NoGravityRule :
    public GameRule
{
public:
    NoGravityRule(shared_ptr<GameComponents> components,int runtime);
    bool gravityDisabled = false;
    void applyRule();
};

