#pragma once
#include "ofMain.h"
#include "GameObjectContainer.h"

//renderer
#include "RenderObject.h"
#include "PolygonRenderer.h"

//game objects
#include "Paddle.h"
#include "TetrisStone.h"

//rules
#include "DeleteOutOfScreenRule.h"

/// \brief creates all Game Elements
class GameFactory
{
public:
	//Gameobjects
	static shared_ptr<Paddle> makePaddle(shared_ptr<GameObjectContainer> objects, string name);
	static shared_ptr<GameObject> makeBasicStone(shared_ptr<GameObjectContainer> objects);
    static shared_ptr<TetrisStone> makeTetrisStone(shared_ptr<GameObjectContainer> objects);
    
    
	//rules
	static shared_ptr<DeleteOutOfScreenRule> makeDeleteOutOfScreenRule();
};

