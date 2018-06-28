#pragma once
#include "ofMain.h"
#include "GameObjects.h"

//game objects
#include "Paddle.h"


/// \brief creates all Game Elements
class GameFactory
{
public:
	static shared_ptr<Paddle> makePaddle(shared_ptr<GameObjects> objects, ofJson config);
};

