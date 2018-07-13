#pragma once

#include "RenderObject.h"
#include "Rule.h"
#include "GameObject.h"
#include "ofxBox2d.h"
#include "Paddle.h"

class GameObjectContainer
{
public:
	GameObjectContainer();
	~GameObjectContainer();

	void initPhysics();

	void addGameObject(shared_ptr<GameObject> object);

	vector<shared_ptr<Paddle>> paddles;

	//all objects
	vector<shared_ptr<GameObject>> gameObjects;
	ofxBox2d physics;

protected:

};

