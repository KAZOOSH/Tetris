#pragma once
#include "GameObjectContainer.h"

/// \brief controls game flow, object creation and winning conditions
class GameControl
{
public:
	GameControl(GameObjectContainer objectContainer);
	~GameControl();

	void update();
	void render();

	void onEraseEvent(long& id);

	void registerEraseEvent(ofEvent<long>& ev);

	void reloadRenderer();

protected:
	void removeErasedElements();
	void removeDeprecatedRules();

private:
	long tGameStarted;
	unique_ptr<GameObjectContainer> objectContainer;

	vector<long> toDeleteIds;
};

