#include "GameControlRule.h"



GameControlRule::GameControlRule(shared_ptr<GameComponents> components):GameRule("GameControlRule",components)
{
	gameControl = components->gameControl();
	mainFont.setup(components->params()->settings["fonts"]["main"], 1.0, 1024, false, 8, 1.5f);
	subFont.setup(components->params()->settings["fonts"]["sub"], 1.0, 1024, false, 8, 1.0);
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
		panels.insert(pair<string, InfoPanel>(s["state"].get<string>(), InfoPanel(components->params()->settings, s, &mainFont, &subFont)));
	}

	//create countdown panels
	for (size_t i = 0; i < 15; i++)
	{
		ofJson s;
		s["state"] = ofToString(i+1);
		s["main"] = ofToString(i+1);
		s["sub"] = "(" + ofToString(i+1) + ")";
		s["time"] = 1000;
		s["sound"] = "";
		
		countdown.insert(pair<int, InfoPanel>(i, InfoPanel(components->params()->settings, s, &mainFont, &subFont)));
	}

	ofAddListener(components->events()->gameEvent, this, &GameControlRule::onGamestateChanged);
	ofAddListener(components->events()->controlEvent, this, &GameControlRule::onPaddleMove);
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
		components->events()->winningHeight = components->params()->settings["gameplay"]["winningHeightMax"].get<float>();
		changeGamestate("countdown2");
	} else if (gamestate == "countdown2" && isTSwitch) {
		changeGamestate("countdown1");
	} else if (gamestate == "countdown1" && isTSwitch) {
		changeGamestate("game");
	} else if (gamestate == "game") {
		int winningHeight = components->events()->winningHeight*components->params()->settings["height"].get<float>();
		//cout << winningHeight << " -> " << gameObjects->paddles[0]->towerHeight << "   |    " << gameObjects->paddles[1]->towerHeight << endl;
		if (gameControl->paddles[0]->towerHeight > winningHeight) {
			changeGamestate("end1");
		}
		else if (gameControl->paddles[1]->towerHeight > winningHeight) {
			changeGamestate("end2");
		}

		//reduce winning height
		if (now - startState > components->params()->settings["gameplay"]["startHeightReduction"].get<int>()){
			components->events()->winningHeight = 
				ofMap(now - startState, components->params()->settings["gameplay"]["startHeightReduction"].get<int>(),
				components->params()->settings["gameplay"]["maxDuration"].get<int>(),
				components->params()->settings["gameplay"]["winningHeightMax"].get<float>(),
				components->params()->settings["gameplay"]["winningHeightMin"].get<float>(),true);
		}
		if (now - startState > components->params()->settings["gameplay"]["maxDuration"].get<int>()) {
			if (gameControl->paddles[0]->towerHeight > gameControl->paddles[1]->towerHeight) {
				changeGamestate("end1");
			} else if (gameControl->paddles[1]->towerHeight > gameControl->paddles[0]->towerHeight) {
				changeGamestate("end2");
			}else changeGamestate("endEven");
		}
	} else if (gamestate == "end1" && isTSwitch) {
		changeGamestate("afterEnd");
	} else if (gamestate == "end2" && isTSwitch) {
		changeGamestate("afterEnd");
	} else if (gamestate == "endEven" && isTSwitch) {
		changeGamestate("afterEnd");
	} else if (gamestate == "afterEnd" && isTSwitch) {
		changeGamestate("idle");
	}
}

void GameControlRule::draw()
{
	ofSetColor(255);
	//ofDrawBitmapString(gamestate, 200, 200);
	
	//if (gamestate != "game") {
		panels[gamestate].draw();
		panels[gamestate].draw(components->params()->settings["width"].get<int>()*0.5);
	//}

	if (gamestate == "idle") {

	}else if (gamestate == "waiting_for_players") {

	}else if (gamestate == "countdown") {

	}else if (gamestate == "game") {
		int tLeft = startState + components->params()->settings["gameplay"]["maxDuration"].get<int>() - ofGetElapsedTimeMillis();
		if (tLeft < 15000  && tLeft >0) {
			int t = tLeft / 1000;
			if (t != lastCountdownSwitch) {
				lastCountdownSwitch = t;
				countdown[t].start();
				ofJson s;
				s["function"] = "countdown";
				components->events()->notifyGameEvent(s);
			}
			countdown[t].draw();
			countdown[t].draw(components->params()->settings["width"].get<int>()*0.5);
		}

		
	}else if (gamestate == "end2") {
		ofPushMatrix();
		ofTranslate(components->params()->settings["width"].get<int>() * 0.5, 0);
		drawFadeOut();
		ofPopMatrix();
		
	} else if (gamestate == "end1") {
		drawFadeOut();
	}

	
}

void GameControlRule::changeGamestate(string message)
{
	gamestate = message;
	startState = ofGetElapsedTimeMillis();

	panels[gamestate].start();

	if (gamestate == "game") components->soundPlayer()->play("start", 1);
	if (gamestate == "game") components->soundPlayer()->play("start", 2);

	ofJson state = ofJson{
		{"function","gamestate"},
		{ "gamestate" , gamestate}
	};
	ofRemoveListener(components->events()->gameEvent, this, &GameControlRule::onGamestateChanged);
	components->events()->notifyGameEvent(state);
	ofAddListener(components->events()->gameEvent, this, &GameControlRule::onGamestateChanged);
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

		float y_min = components->params()->settings["height"].get<float>()- components->params()->settings["paddleArea"][1].get<float>();
		float y_max = components->params()->settings["height"].get<float>();
		if (ofMap(p, y_max, y_min, 0.0, 1.0) > 0.7) paddleReady[message["id"].get<int>() - 1] = true;
		else paddleReady[message["id"].get<int>() - 1] = false;
	}
}

int GameControlRule::getStateTime(string stateName)
{
	for (auto& s : stateDescription) {
		if (s["state"] == stateName) return s["time"];
	}
	return 0;
}

void GameControlRule::drawFadeOut()
{
	ofSetColor(0);//, ofClamp((ofGetElapsedTimeMillis() - startState) * 255 / 2000,0,255));
	ofDrawRectangle(0, 0, components->params()->settings["width"].get<int>() * 0.5, components->params()->settings["height"].get<int>());
}


