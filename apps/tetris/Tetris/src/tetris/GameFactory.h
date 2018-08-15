#pragma once
#include "ofMain.h"
#include "GameObjectContainer.h"
#include "GameParameters.h"

//renderer
#include "RenderObject.h"
#include "PolygonRenderer.h"

//game objects
#include "Paddle.h"
#include "BasicStone.h"

//rules
#include "DeleteOutOfScreenRule.h"
#include "GameControlRule.h"

/// \brief creates all Game Elements
class GameFactory
{
public:
	//Gameobjects
	static shared_ptr<Paddle> makePaddle(shared_ptr<GameObjectContainer> objects, string name);
	static shared_ptr<GameObject> makeBasicStone(shared_ptr<GameObjectContainer> objects);

	//rules
	static shared_ptr<DeleteOutOfScreenRule> makeDeleteOutOfScreenRule(GameParameters* params);
	static shared_ptr<GameControlRule> makeGameControlRule(GameParameters* params);
};

