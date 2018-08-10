#pragma once

#include "Paddle.h"
#include "GameParameters.h"

class PlayerControl
{
public:
	PlayerControl();
	~PlayerControl();

	void setup(vector<shared_ptr<Paddle>> paddles, GameParameters* params);

private:
	vector<shared_ptr<Paddle>> paddles;
	GameParameters* params;
};

