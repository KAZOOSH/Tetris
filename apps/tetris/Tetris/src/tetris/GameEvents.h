#ifndef GAMEEVENTS_H
#define GAMEEVENTS_H

#include "ofMain.h"

class GameEvents
{
public:
	GameEvents();

	ofEvent<ofJson> gameEvent;
	ofEvent<ofJson> controlEvent;

	void notifyGameEvent(ofJson eventText);
	void notifyControlEvent(ofJson eventText);

	void setRandomNextEffect();
	void setNextEffect(string name);

	vector<string> nextCreationRule;
	string gamestate = "idle";

private:
	vector<string> nextEffectList;
};

#endif // GAMEEVENTS_H
