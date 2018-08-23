#include "GameEventRule.h"



GameEventRule::GameEventRule(GameParameters* params) :Rule("GameControlRule", params)
{
	mainFont.setup(params->params["fonts"]["main"], 1.0, 1024, false, 8, 1.5f);
	subFont.setup(params->params["fonts"]["sub"], 1.0, 1024, false, 8, 1.0);
	mainFont.setSize(250);
	subFont.setSize(250);
	mainFont.setCharacterSpacing(0);
	subFont.setCharacterSpacing(0);

	//create InfoPanels
	for (auto& s : params->effects) {
		vector<InfoPanel> p = { InfoPanel(params->params, s, &mainFont, &subFont),InfoPanel(params->params, s, &mainFont, &subFont) };
		p[0].setPlayer(1);
		p[0].setPlayer(2);
		panels.insert(pair<string, vector<InfoPanel>>(s["state"].get<string>(), p));
	}

	currentEvents.push_back(vector<string>());
	currentEvents.push_back(vector<string>());

	ofAddListener(params->gameEvent, this, &GameEventRule::onGameEvent);
}


GameEventRule::~GameEventRule()
{
}

void GameEventRule::applyRule()
{
	//delete old events
	uint64_t now = ofGetElapsedTimeMillis();

	for (size_t e = 0; e < currentEvents.size(); e++) {
		vector<int> toDel;
		for (size_t i = 0; i < currentEvents[e].size(); i++) {
			if (now - panels[currentEvents[e][i]][e].getDuration() > panels[currentEvents[e][i]][e].getStart()) {
				toDel.push_back(i);
			}
		}
		if (toDel.size() > 0) {
			for (int i = toDel.size() - 1; i >= 0; i--) {
				currentEvents[e].erase(currentEvents[e].begin() + i);
			}
		}
	}
}

void GameEventRule::draw()
{

	for (size_t i = 0; i < currentEvents.size(); i++){
		for (auto& ev : currentEvents[i]) {
			if (i == 0) {
				panels[ev][i].draw();
			} else {
				panels[ev][i].draw(params->params["width"].get<int>()*0.5);
			}
		}
	}
}

void GameEventRule::onGameEvent(ofJson & eventMessage)
{
	if (eventMessage["function"] != nullptr && eventMessage["function"] == "effect") {
		if (eventMessage["player"] != nullptr && eventMessage["player"] != 0) {
			currentEvents[eventMessage["player"]-1].push_back(eventMessage["effect"]);
			panels[currentEvents[eventMessage["player"] - 1].back()][eventMessage["player"] - 1].start();
		} else {
			currentEvents[0].push_back(eventMessage["effect"]);
			currentEvents[1].push_back(eventMessage["effect"]);
			panels[currentEvents[0].back()][0].start();
			panels[currentEvents[1].back()][1].start();
		}
			
		
	}
}
