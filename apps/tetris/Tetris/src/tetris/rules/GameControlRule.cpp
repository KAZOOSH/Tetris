#include "GameControlRule.h"



GameControlRule::GameControlRule(GameParameters* params, GameObjectContainer* gameControl_):Rule("GameControlRule",params)
{
	gameObjects = gameControl_;
	mainFont.setup(params->params["fonts"]["main"], 1.0, 1024, false, 8, 1.5f);
	subFont.setup(params->params["fonts"]["sub"], 1.0, 1024, false, 8, 1.0);
	mainFont.setSize(250);
	subFont.setSize(250);
	mainFont.setCharacterSpacing(0);
	subFont.setCharacterSpacing(0);

	paddleReady = { false,false };

	ofFile file("_Tetris/gamestates.json");
	if (file.exists()) {
		file >> stateDescription;
	}

	//create InfoPanels
	for (auto& s : stateDescription) {
		panels.insert(pair<string, InfoPanel>(s["state"].get<string>(), InfoPanel(params->params, s, &mainFont, &subFont)));
	}

	ofAddListener(params->gameEvent, this, &GameControlRule::onGamestateChanged);
	ofAddListener(params->controlEvent, this, &GameControlRule::onPaddleMove);
}


GameControlRule::~GameControlRule()
{
}

void GameControlRule::applyRule()
{
	uint64_t now = ofGetElapsedTimeMillis();
	bool isTSwitch = now - startState > getStateTime(gamestate);

	if (gamestate == "idle") {
		if (paddleReady[0] && paddleReady[1]) {
			changeGamestate( "countdown3");
		} else if (isTSwitch) {
			changeGamestate("waiting_for_players");
		}
	} else if (gamestate == "waiting_for_players") {
		if (paddleReady[0] && paddleReady[1]) {
			changeGamestate("countdown3");
		} else if (isTSwitch) {
			changeGamestate("idle");
		}
	} else if (gamestate == "countdown3" && isTSwitch) {
		params->winningHeight = params->params["gameplay"]["winningHeightMax"].get<float>();
		changeGamestate("countdown2");
	} else if (gamestate == "countdown2" && isTSwitch) {
		changeGamestate("countdown1");
	} else if (gamestate == "countdown1" && isTSwitch) {
		changeGamestate("game");
	} else if (gamestate == "game") {
		int winningHeight = params->winningHeight*params->params["height"].get<float>();
		//cout << winningHeight << " -> " << gameObjects->paddles[0]->towerHeight << "   |    " << gameObjects->paddles[1]->towerHeight << endl;
		if (gameObjects->paddles[0]->towerHeight > winningHeight) {
			changeGamestate("end1");
		}
		else if (gameObjects->paddles[1]->towerHeight > winningHeight) {
			changeGamestate("end2");
		}

		//reduce winning height
		cout << now << " - " << startState << "    > " << params->params["gameplay"]["maxDuration"].get<int>() << endl;
		if (now - startState > params->params["gameplay"]["startHeightReduction"].get<int>()){
			params->winningHeight = 
				ofMap(now - startState, params->params["gameplay"]["startHeightReduction"].get<int>(),
				params->params["gameplay"]["maxDuration"].get<int>(),
				params->params["gameplay"]["winningHeightMax"].get<float>(),
				params->params["gameplay"]["winningHeightMin"].get<float>(),true);
		} else if (now - startState > params->params["gameplay"]["maxDuration"].get<int>()) {
			cout << "even" << endl;
			changeGamestate("endEven");
		}
	} else if (gamestate == "end1" && isTSwitch) {
		changeGamestate("idle");
	} else if (gamestate == "end2" && isTSwitch) {
		changeGamestate("idle");
	} else if (gamestate == "endEven" && isTSwitch) {
		changeGamestate("idle");
	}
}

void GameControlRule::draw()
{
	ofSetColor(255);
	ofDrawBitmapString(gamestate, 200, 200);
	
	if (gamestate != "game") {
		panels[gamestate].draw();
		panels[gamestate].draw(params->params["width"].get<int>()*0.5);
	}

	if (gamestate == "idle") {

	}else if (gamestate == "waiting_for_players") {

	}else if (gamestate == "countdown") {

	}else if (gamestate == "game") {
		ofSetColor(255);
		int h = params->params["height"].get<int>();
		int hBase = (1.0 - params->winningHeight)*h;
		int y1 = hBase -(h - gameObjects->paddles[0]->getBody()[0]->getPosition().y);
		int y2 = hBase - (h - gameObjects->paddles[1]->getBody()[0]->getPosition().y);
		ofDrawRectangle(0, y1, params->params["width"].get<int>()/2, 10);
		ofDrawRectangle(params->params["width"].get<int>() / 2, y2, params->params["width"].get<int>() / 2, 10);
	}else if (gamestate == "end1") {

	} else if (gamestate == "end2") {

	}

	
}

void GameControlRule::changeGamestate(string message)
{
	gamestate = message;
	startState = ofGetElapsedTimeMillis();

	panels[gamestate].start();

	ofJson state = ofJson{
		{"function","gamestate"},
		{ "gamestate" , gamestate}
	};
	ofRemoveListener(params->gameEvent, this, &GameControlRule::onGamestateChanged);
	params->notifyGameEvent(state);
	ofAddListener(params->gameEvent, this, &GameControlRule::onGamestateChanged);
}

void GameControlRule::onGamestateChanged(ofJson & message)
{
	if (message["function"] != nullptr && message["function"] == "gamestate") {
		gamestate = message["gamestate"].get<string>();
		panels[gamestate].start();
		startState = ofGetElapsedTimeMillis();
	}
}

void GameControlRule::onPaddleMove(ofJson & message)
{
	if (message["control"] != nullptr && message["control"] == "paddle") {
		float p = 0.5*(message["p1"]["y"].get<float>() + message["p2"]["y"].get<float>());

		float y_min = params->params["height"].get<float>()- params->params["paddleArea"][1].get<float>();
		float y_max = params->params["height"].get<float>();
		if (ofMap(p, y_max, y_min, 0.0, 1.0) > 0.7) paddleReady[message["id"].get<int>() - 1] = true;
		else paddleReady[message["id"].get<int>() - 1] = false;
	}
}

int GameControlRule::getStateTime(string stateName)
{
	for (auto& s : stateDescription) {
		if (s["state"] == stateName) return s["time"];
	}
}


