#pragma once
#include "ofMain.h"
#include "GameObjectContainer.h"
#include "GameParameters.h"

//renderer
#include "RenderObject.h"
#include "PolygonRenderer.h"
#include "TetrisStoneRenderer.h"
#include "BackgroundRenderer.h"

//game objects
#include "Paddle.h"
#include "TetrisStone.h"
#include "BackgroundObject.h"

//rules
#include "DeleteOutOfScreenRule.h"
#include "GameControlRule.h"

/// \brief creates all Game Elements
class GameFactory
{
public:
    //Gameobjects
    static shared_ptr<Paddle> makePaddle(shared_ptr<GameObjectContainer> objects, string name, GameParameters* params);
    static shared_ptr<GameObject> makeBasicStone(shared_ptr<GameObjectContainer> objects);
    static shared_ptr<TetrisStone> makeTetrisStone(shared_ptr<GameObjectContainer> objects, GameParameters* params, GameParameters::effects activeEffect);
    static shared_ptr<BackgroundObject> makeBackgroundObject(shared_ptr<GameObjectContainer> objects, GameParameters* params);
    
    
    //rules
    static shared_ptr<DeleteOutOfScreenRule> makeDeleteOutOfScreenRule(GameParameters* params);
    static shared_ptr<GameControlRule> makeGameControlRule(GameParameters* params, GameObjectContainer* gameObjects);
};

