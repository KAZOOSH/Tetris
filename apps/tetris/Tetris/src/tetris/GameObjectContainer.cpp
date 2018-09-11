#include "GameObjectContainer.h"



GameObjectContainer::GameObjectContainer()
{
}


GameObjectContainer::~GameObjectContainer()
{
}

void GameObjectContainer::initPhysics(float gravity)
{
    physics.init();
	physics.setGravity(0, gravity);
    //physics.createGround();
    physics.setFPS(60.0);
}

void GameObjectContainer::addGameObject(shared_ptr<GameObject> object)
{
    gameControl.push_back(object);
	
}

void GameObjectContainer::addPaddle(shared_ptr<Paddle> object)
{
    paddles.push_back(object);
    gameControl.push_back(object);
    
}
shared_ptr<Paddle> GameObjectContainer::getPaddle(string name)
{
    for (auto& p : paddles) {
        if(name == Paddle::paddleNameLeft && p->isPaddleLeft){
            return p;
        }else if(name == Paddle::paddleNameRight && p->isPaddleRight){
            return p;
        }
    }
	return nullptr;
}

void GameObjectContainer::addRule(shared_ptr<Rule> rule)
{
    rules.push_back(rule);
}

shared_ptr<Rule> GameObjectContainer::getRule(string name)
{
    for (auto& r : rules) {
        if (r->getName() == name) return r;
    }
    return shared_ptr<Rule>();
}
