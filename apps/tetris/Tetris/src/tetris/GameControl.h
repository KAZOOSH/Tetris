#pragma once
#include "GameObjects.h"

/// \brief controls game flow, object creation and winning conditions
class GameControl
{
public:
	GameControl(shared_ptr<GameObjects> objects);
	~GameControl();

	void update();

private:
	long tGameStarted;
	shared_ptr<GameObjects> objects;
};

