#include "GameEvents.h"

GameEvents::GameEvents()
{

}

void GameEvents::notifyGameEvent(ofJson eventText)
{
	ofNotifyEvent(gameEvent, eventText);

	if (eventText["function"] != nullptr && eventText["function"] == "gamestate") {
		gamestate = eventText["gamestate"].get<string>();
	}
}

void GameEvents::notifyControlEvent(ofJson eventText)
{
	ofNotifyEvent(controlEvent, eventText);
}

void GameEvents::setRandomNextEffect(){
	if (nextEffectList.size() == 0) {
		for (int i = 0; i < effects.size(); i++) {
			nextEffectList.push_back(effects[i]["state"]);
		}
		std::random_shuffle(nextEffectList.begin(), nextEffectList.end());
	}

	if (getEffect(nextEffectList.back())["type"] == "world") {
		ofJson out;
		out["function"] = "createWorldEffect";
		out["params"] = getEffect(nextEffectList.back());
		notifyGameEvent(out);

	} else {
		nextCreationRule[0] = nextEffectList.back();
		nextCreationRule[1] = nextEffectList.back();
	}
	nextEffectList.pop_back();
}

void GameEvents::setNextEffect(string name)
{
	if (getEffect(name)["type"] == "world") {
		ofJson out;
		out["function"] = "createWorldEffect";
		out["params"] = getEffect(name);
		notifyGameEvent(out);

	} else {
		nextCreationRule[0] = name;
		nextCreationRule[1] = name;
	}
}
