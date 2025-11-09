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
	uint64_t tGamestateChange = 0;

	float winningHeight = 0.9;
	
	void registerEraseEvent(ofEvent<uint64_t>& ev);

	void onBuzzer(ofJson& msg);

private:
	shared_ptr<GameParameters> settings;
	vector<string> nextEffectList;
	
 };

#endif // GAMEEVENTS_H
