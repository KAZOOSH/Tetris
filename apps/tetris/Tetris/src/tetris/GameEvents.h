#ifndef GAMEEVENTS_H
#define GAMEEVENTS_H

#include "ofMain.h"
#include "GameParameters.h"


class GameEvents
{
public:
	GameEvents();
	void setup(shared_ptr<GameParameters> settings);

	ofEvent<ofJson> gameEvent;
	ofEvent<ofJson> controlEvent;
	ofEvent<uint64_t> objectEraseEvent;

	void notifyGameEvent(ofJson eventText);
	void notifyControlEvent(ofJson eventText);
	void notifyEraseEvent(uint64_t& eraseId);

	void setRandomNextEffect();
	void setNextEffect(string name);

	vector<string> nextCreationRule;
	string gamestate = "idle";

	float winningHeight = 0.9;
    float velocityBeforeCollision = 10;
	float stoneCreationIntervall = 3000;
	void registerEraseEvent(ofEvent<uint64_t>& ev);

private:
	shared_ptr<GameParameters> settings;
	vector<string> nextEffectList;
};

#endif // GAMEEVENTS_H
