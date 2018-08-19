#include "GameControlRule.h"



GameControlRule::GameControlRule(GameParameters* params):Rule("GameControlRule",params)
{
	mainFont.setup(params->params["fonts"]["main"], 1.0, 1024, false, 8, 1.5f);
	subFont.setup(params->params["fonts"]["sub"], 1.0, 1024, false, 8, 1.0);
	mainFont.setSize(250);
	subFont.setSize(250);
	mainFont.setCharacterSpacing(0);
	subFont.setCharacterSpacing(0);

	paddleReady = { false,false };

	ofFile file("_Tetris/textfields.json");
	if (file.exists()) {
		file >> stateDescription;
	}

	//create InfoPanels
	for (auto& s : stateDescription) {
		panels.insert(pair<string, InfoPanel>(s["state"], InfoPanel(params->params, s, &mainFont, &subFont)));
	}

	ofAddListener(params->gameEvent, this, &GameControlRule::onGamestateChanged);
	ofAddListener(params->controlEvent, this, &GameControlRule::onPaddleMove);
}


GameControlRule::~GameControlRule()
{
}

void GameControlRule::applyRule()
{
	bool isTSwitch = ofGetElapsedTimeMillis() - startState > getStateTime(gamestate);

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
		changeGamestate("countdown2");
	} else if (gamestate == "countdown2" && isTSwitch) {
		changeGamestate("countdown1");
	} else if (gamestate == "countdown1" && isTSwitch) {
		changeGamestate("game");
	} else if (gamestate == "game") {

	} else if (gamestate == "end1" && isTSwitch) {
		changeGamestate("idle");
	} else if (gamestate == "end2" && isTSwitch) {
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
	ofNotifyEvent(params->gameEvent, state);
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
	if (message["control"] == "paddle") {
		float p = 0.5*(message["p1"]["y"].get<float>() + message["p2"]["y"].get<float>());

		float y_min = params->params["height"].get<float>()- params->params["paddleArea"][1].get<float>();
		float y_max = params->params["height"].get<float>();
		if (ofMap(p, y_max, y_min, 0.0, 1.0) > 0.7) paddleReady[message["id"] - 1] = true;
		else paddleReady[message["id"] - 1] = false;
	}
}

int GameControlRule::getStateTime(string stateName)
{
	for (auto& s : stateDescription) {
		if (s["state"] == stateName) return s["time"];
	}
}

InfoPanel::InfoPanel(ofJson settings, ofJson description, ofxFontStash* fontMain, ofxFontStash* fontSub)
{
	int h = description["height"] != nullptr ? description["height"] : settings["textFields"]["main"]["h"];
	mainText = createTextField(fontMain, description["main"], settings["textFields"]["main"]["y"], h,settings["width"]);	
	subText = createTextField(fontSub, description["sub"], settings["textFields"]["sub"]["y"], settings["textFields"]["sub"]["h"], settings["width"]);
	duration = description["time"];
}

void InfoPanel::start()
{
	tStart = ofGetElapsedTimeMillis();
}

void InfoPanel::draw(int x)
{
	uint64_t now = ofGetElapsedTimeMillis();
	if (now - tStart < duration) {
		ofPopMatrix();
		ofTranslate(x, 0);
		//main
		//todo bouncy fade in
		float scale = 1.0;
		if (now - tStart < 1000) scale = ofxeasing::map_clamp(now, tStart, tStart + 1000, 0, 1.0, &ofxeasing::bounce::easeIn);
		else if (tStart + duration - now < 1000) scale = ofxeasing::map_clamp(now, tStart + duration - 1000, tStart + duration, 1.0, 0.0, &ofxeasing::bounce::easeOut);

		ofPushMatrix();
			ofTranslate(mainText->position);
			ofTranslate((1-scale)* mainText->size*0.5);
			mainText->texture.draw(ofVec2f(0,0), mainText->size.x*scale, mainText->size.y*scale);
		ofPopMatrix();

		//sub
		float alpha = 1.0;
		if(now - tStart < 500) alpha = ofxeasing::map_clamp(now, tStart, tStart+500, 0, 1.0, &ofxeasing::quad::easeIn);
		else if (tStart + duration -now < 700) alpha = ofxeasing::map_clamp(now, tStart + duration - 700, tStart + duration, 1.0, 0.0, &ofxeasing::quad::easeOut);
		subText->texture.draw(subText->position, subText->size.x, subText->size.y);
		ofPopMatrix();
	}
}

TextField* InfoPanel::createTextField(ofxFontStash* font, string text, int y, int h, int wScreen)
{
	auto bb = font->getStringBoundingBox(text, 0, 0);
	ofFbo fbo;
	fbo.allocate(bb.width, bb.height);
	fbo.begin();
	ofClear(0, 0);
	ofSetColor(255);
	font->draw(text, 250, 0, fbo.getHeight()*0.9);
	fbo.end();

	ofVec2f size = ofVec2f( fbo.getWidth()*h / fbo.getHeight(),h);
	ofVec2f pos = ofVec2f(0.5*(0.5*wScreen - size.x), y);

	return new TextField(fbo, size, pos);
}
