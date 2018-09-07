#ifndef GAMECOMPONENTS_H
#define GAMECOMPONENTS_H

#include "GameObjectContainer.h"
#include "GameParameters.h"
#include "GameEvents.h"
#include "SoundEffectPlayer.h"

class GameComponents
{
public:
	GameComponents();
	 shared_ptr<GameObjectContainer> objects();
	 shared_ptr<GameParameters> params();
	 shared_ptr<GameEvents> events();
	 shared_ptr<SoundEffectPlayer> soundPlayer();

private:
	shared_ptr<GameObjectContainer> gameObjectContainer;
	shared_ptr<GameParameters> gameParameters;
	shared_ptr<GameEvents> gameEvents;
	shared_ptr<SoundEffectPlayer> soundEffectPlayer;
};

#endif // GAMECOMPONENTS_H