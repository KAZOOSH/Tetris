#include "GameEvents.h"

GameEvents::GameEvents()
{
	nextCreationRule.push_back("base");
	nextCreationRule.push_back("base");
}

void GameEvents::setup(shared_ptr<GameParameters> params_)
{
	settings = params_;
}

void GameEvents::notifyGameEvent(ofJson eventText)
{
	ofNotifyEvent(gameEvent, eventText);

	if (eventText["function"] != nullptr && eventText["function"] == "gamestate") {
		gamestate = eventText["gamestate"].get<string>();
		tGamestateChange = ofGetElapsedTimeMillis();
	}
}

void GameEvents::notifyControlEvent(ofJson eventText)
{
	ofNotifyEvent(controlEvent, eventText);
}

void GameEvents::notifyEraseEvent(uint64_t & eraseId)
{
	ofNotifyEvent(objectEraseEvent, eraseId);
}

void GameEvents::setRandomNextEffect(){
	if (nextEffectList.size() == 0) {
		for (int i = 0; i < settings->effects.size(); i++) {
			nextEffectList.push_back(settings->effects[i]["state"]);
		}
		std::random_shuffle(nextEffectList.begin(), nextEffectList.end());
	}

	if (settings->getEffect(nextEffectList.back())["type"] == "world") {
		ofJson out;
		out["function"] = "createWorldEffect";
		out["params"] = settings->getEffect(nextEffectList.back());
		notifyGameEvent(out);

	} else {
		nextCreationRule[0] = nextEffectList.back();
		nextCreationRule[1] = nextEffectList.back();
	}
	nextEffectList.pop_back();
}

void GameEvents::setNextEffect(string name)
{
	if (settings->getEffect(name)["type"] == "world") {
		ofJson out;
		out["function"] = "createWorldEffect";
		out["params"] = settings->getEffect(name);
		notifyGameEvent(out);

	} else {
		nextCreationRule[0] = name;
		nextCreationRule[1] = name;
	}
}

void GameEvents::registerEraseEvent(ofEvent<uint64_t>& ev)
{
	ofAddListener(ev, this, &GameEvents::notifyEraseEvent);
}
