#pragma once
#include "GameObjectContainer.h"

/// \brief controls game flow, object creation and winning conditions
class GameControl
{
public:
	GameControl(shared_ptr<GameObjectContainer> objects);
	~GameControl();

	void update();
	void render();

private:
	long tGameStarted;
	shared_ptr<GameObjectContainer> objects;
};

