#pragma once
#include "ofMain.h"
#include "GameObjects.h"

//renderer
#include "RenderObject.h"
#include "PolygonRenderer.h"

//game objects
#include "Paddle.h"
#include "BasicStone.h"


/// \brief creates all Game Elements
class GameFactory
{
public:
	static shared_ptr<Paddle> makePaddle(shared_ptr<GameObjects> objects, ofJson config);
	static shared_ptr<BasicStone> makeBasicStone(shared_ptr<GameObjects> objects, ofJson config, shared_ptr<PolygonRenderer> renderer);
};

