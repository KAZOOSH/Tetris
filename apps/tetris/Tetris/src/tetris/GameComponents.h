#ifndef GAMECOMPONENTS_H
#define GAMECOMPONENTS_H

#include "GameObjectContainer.h"
#include "GameParameters.h"

class GameComponents
{
public:
	GameComponents();
	const GameObjectContainer &getObjects();
};

#endif // GAMECOMPONENTS_H
