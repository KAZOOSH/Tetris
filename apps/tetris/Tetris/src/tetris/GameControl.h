#pragma once
#include "GameObjectContainer.h"
#include "GameEvents.h"

/// \brief controls game flow, object creation and winning conditions
class GameControl
{
public:
	GameControl(shared_ptr<GameObjectContainer> gameControl, shared_ptr<GameEvents> events);
	~GameControl();

	void update();
	void render();

	void onEraseEvent(uint64_t& id);

	void reloadRenderer();

protected:
	void removeErasedElements();
	void removeDeprecatedRules();

private:
	uint64_t tGameStarted;
	shared_ptr<GameObjectContainer> objectContainer;

	vector<uint64_t> toDeleteIds;
};

