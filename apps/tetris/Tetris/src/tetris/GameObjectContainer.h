#pragma once

#include "RenderObject.h"
#include "Rule.h"
#include "GameObject.h"
#include "ofxBox2d.h"
#include "Paddle.h"
#include "Rule.h"
#include "GameParameters.h"


class GameObjectContainer
{
public:
	GameObjectContainer(GameParameters* params);
	~GameObjectContainer();

	void initPhysics();

	void addGameObject(shared_ptr<GameObject> object);
	void addPaddle(shared_ptr<Paddle> object);
	void addRule(shared_ptr<Rule> rule);

	shared_ptr<Rule> getRule(string name);
    shared_ptr<Paddle> getPaddle(string name);
	vector<shared_ptr<Paddle>> paddles;

	//all objects
	vector<shared_ptr<GameObject>> gameControl;
	vector<shared_ptr<Rule>> rules;
	ofxBox2d physics;

protected:
	GameParameters* params;
};

