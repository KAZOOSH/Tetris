#pragma once
#include "ofMain.h"
#include "GameObjectContainer.h"
#include "GameParameters.h"

//renderer
#include "RenderObject.h"
#include "PolygonRenderer.h"
#include "TetrisStoneRenderer.h"
#include "BackgroundRenderer.h"
#include "HeavyStoneRenderer.h"
#include "BouncyStoneRenderer.h"

//game objects
#include "Paddle.h"
#include "TetrisStone.h"

//rules
#include "DeleteOutOfScreenRule.h"
#include "GameControlRule.h"
#include "GameEventRule.h"
#include "WindRule.h"

/// \brief creates all Game Elements
class GameFactory
{
public:
    //Gameobjects
    static shared_ptr<Paddle> makePaddle(shared_ptr<GameObjectContainer> objects, string name, GameParameters* params);
    static shared_ptr<GameObject> makeBasicStone(shared_ptr<GameObjectContainer> objects);
    static shared_ptr<TetrisStone> makeTetrisStone(shared_ptr<GameObjectContainer> objects, GameParameters* params, string activeEffect);
    static shared_ptr<GameObject> makeBackgroundObject(shared_ptr<GameObjectContainer> objects, GameParameters* params);
    
    
    //rules
    static shared_ptr<DeleteOutOfScreenRule> makeDeleteOutOfScreenRule(GameParameters* params);
    static shared_ptr<GameControlRule> makeGameControlRule(GameParameters* params, GameObjectContainer* gameControl);
	static shared_ptr<GameEventRule> makeGameEventRule(GameParameters* params);
	static shared_ptr<Rule> makeWorldEffect(GameParameters* params, ofJson config);
};

