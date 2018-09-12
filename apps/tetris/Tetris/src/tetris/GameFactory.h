#pragma once
#include "ofMain.h"
#include "GameObjectContainer.h"
#include "GameParameters.h"
#include "GameComponents.h"

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
#include "StoneControlRule.h"
#include "StoneCreationRule.h"

/// \brief creates all Game Elements
class GameFactory
{
public:
    //Gameobjects
    static shared_ptr<Paddle> makePaddle(shared_ptr<GameComponents> components, string name);
    static shared_ptr<GameObject> makeBasicStone(shared_ptr<GameComponents> components);
    static shared_ptr<TetrisStone> makeTetrisStone(shared_ptr<GameComponents> components, string activeEffect);
    static shared_ptr<GameObject> makeBackgroundObject(shared_ptr<GameComponents> components);
    
    
    //rules
    static shared_ptr<DeleteOutOfScreenRule> makeDeleteOutOfScreenRule(shared_ptr<GameComponents> components);
    static shared_ptr<GameControlRule> makeGameControlRule(shared_ptr<GameComponents> components);
	static shared_ptr<GameEventRule> makeGameEventRule(shared_ptr<GameComponents> components);
	static shared_ptr<StoneControlRule> makeStoneControlRule(shared_ptr<GameComponents> components);
	static shared_ptr<StoneCreationRule> makeStoneCreationRule(shared_ptr<GameComponents> components);
	static shared_ptr<Rule> makeWorldEffect(shared_ptr<GameComponents> components, ofJson config);
};

