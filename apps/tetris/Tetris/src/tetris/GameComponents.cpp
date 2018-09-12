#include "GameComponents.h"

GameComponents::GameComponents()
{
	gameParameters = make_shared<GameParameters>(GameParameters());
	gameEvents = make_shared<GameEvents>(GameEvents());
	gameEvents->setup(gameParameters);

	soundEffectPlayer = make_shared<SoundEffectPlayer>(SoundEffectPlayer());
	gameObjectContainer = shared_ptr<GameObjectContainer>(new GameObjectContainer());
	//gameObjectContainer = make_shared<GameObjectContainer>(g);

	/*gameParameters = shared_ptr<GameParameters>();
	gameEvents = shared_ptr<GameEvents>();
	gameEvents->setup(gameParameters);

	gameObjectContainer = shared_ptr<GameObjectContainer>();
	
	gameEvents = shared_ptr<GameEvents>();
	soundEffectPlayer = shared_ptr<SoundEffectPlayer>();*/
}

shared_ptr<GameObjectContainer> GameComponents::gameControl()
{
	return gameObjectContainer;
}

shared_ptr<GameParameters> GameComponents::params()
{
	return gameParameters;
}

shared_ptr<GameEvents> GameComponents::events()
{
	return gameEvents;
}

shared_ptr<SoundEffectPlayer> GameComponents::soundPlayer()
{
	return soundEffectPlayer;
}


