#pragma once

#include "RenderObject.h"
#include "Rule.h"
#include "ofxBox2d.h"
#include "Paddle.h"

class GameObjects
{
public:
	GameObjects();
	~GameObjects();

	void initPhysics();

	void addRule(shared_ptr<Rule> rule);
	void addRenderObject(shared_ptr<RenderObject> object);

	vector<shared_ptr<Paddle>> paddles;

	//all objects
	vector<shared_ptr<RenderObject>> renderObjects;
	vector<shared_ptr<Rule>> rules;
	ofxBox2d physics;
};

