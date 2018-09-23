#include "BackgroundRenderer.h"



BackgroundRenderer::BackgroundRenderer(shared_ptr<GameComponents> components_):RenderObject("BackgroundRenderer")
{
	components = components_;
	settings = components->params();
	gameControl = components->gameControl();
	shader.load("shaders/bg");

	goalTex.allocate(settings->settings["width"].get<int>() / 2, 10);
	goalTex.begin();
	ofClear(0, 0);
	ofSetColor(255);
	ofDrawRectangle(0, 8, goalTex.getWidth(), 2);
	
	int dx = 20;
	int x = dx;
	int ws = 2;
	while (x<goalTex.getWidth() * 2)
	{
		ofPushMatrix();
		ofTranslate(x, 0);
		ofPushMatrix();
		ofRotate(45.f);
		ofDrawRectangle(-50, 0, ws, goalTex.getHeight() +100);
		x += dx;
		ofPopMatrix();
		ofPopMatrix();
	}


	goalTex.end();
	
	paddleTex.allocate(settings->settings["paddle"]["width"], 10);
	paddleTex.begin();
	ofClear(0, 0);
	ofSetColor(255);
	ofDrawRectangle(0, 0, goalTex.getWidth(), 2);

	x = dx;

	while (x<paddleTex.getWidth() * 2)
	{
		ofPushMatrix();
		ofTranslate(x, 0);
		ofPushMatrix();
		ofRotate(45.f);
		ofDrawRectangle(-50, 0, ws, paddleTex.getHeight() + 100);
		x += dx;
		ofPopMatrix();
		ofPopMatrix();
	}
	paddleTex.end();

	loadKosmonaut(components->params()->settings["stoneCreator"]["textures"][0]);
	loadKosmonaut(components->params()->settings["stoneCreator"]["textures"][1]);

	ofAddListener(components->events()->gameEvent, this, &BackgroundRenderer::onGamestate);
}


BackgroundRenderer::~BackgroundRenderer()
{
}

void BackgroundRenderer::render()
{
	if (components->events()->gamestate == "end1" || components->events()->gamestate == "end2") {
		drawGameBackground();
		ofPushMatrix();
		ofTranslate(dxBackground, 0);
		drawWinBackground();
		ofPopMatrix();
	}else if (components->events()->gamestate == "afterEnd") {
		ofPushMatrix();
		ofTranslate(dxBackground, 0);
		drawWinBackground();
		ofPopMatrix();
		ofSetColor(0);
		ofPushMatrix();
		if (dxBackground == 0) ofTranslate(settings->settings["width"].get<int>()*0.5,0);
		ofDrawRectangle(0, 0, settings->settings["width"].get<int>()*0.5, settings->settings["height"].get<int>());
		ofPopMatrix();
	}
	else {
		drawGameBackground();
	}

	ofSetColor(255, 0, 0);
	
	//ofDrawRectangle(0, hGoal1, params->params["width"].get<int>() / 2, 5);
	//ofDrawRectangle(params->params["width"].get<int>() / 2, hGoal2, params->params["width"].get<int>() / 2, 5);
}

void BackgroundRenderer::reload()
{
	shader.load("shaders/bg");
}

void BackgroundRenderer::drawGameBackground()
{
	ofPushStyle();
	shader.begin();
	shader.setUniform1f("windowWidth", float(settings->settings["width"].get<int>()));
	shader.setUniform1f("windowHeight", float(settings->settings["height"].get<int>()));

	ofDrawRectangle(0, 0, settings->settings["width"], settings->settings["height"]);

	shader.end();

	if (isCountDown && ofGetElapsedTimeMillis() / 300 % 2) {
		ofSetColor(255, 0, 0);
		int x = 0;
		gameControl->paddles[1]->towerHeight > gameControl->paddles[0]->towerHeight ? x = 0: x = settings->settings["width"].get<int>()/2;
		ofDrawRectangle(x, 0, settings->settings["width"].get<int>() / 2, settings->settings["height"]);
	}

	ofSetColor(0);
	int h = settings->settings["height"].get<int>();
	int hBase = (1.0 - components->events()->winningHeight)*h;
	int y1 = hBase - (h - gameControl->paddles[0]->getBody()[0]->getPosition().y);
	int y2 = hBase - (h - gameControl->paddles[1]->getBody()[0]->getPosition().y);
	ofDrawRectangle(0, y1, settings->settings["width"].get<int>() / 2, h - y1);
	ofDrawRectangle(settings->settings["width"].get<int>() / 2, y2, settings->settings["width"].get<int>() / 2, h - y2);

	ofSetColor(255, 80);
	goalTex.draw(0, y1 - 10);
	goalTex.draw(settings->settings["width"].get<int>() / 2, y2 - 10);
	//ofDrawRectangle(0, y1, params->params["width"].get<int>() / 2, 5);
	//ofDrawRectangle(params->params["width"].get<int>() / 2, y2, params->params["width"].get<int>() / 2, 5);
	ofPopStyle();


	int hGoal1 = gameControl->paddles[0]->getBody()[0]->getPosition().y - gameControl->paddles[0]->towerHeight;
	int hGoal2 = gameControl->paddles[1]->getBody()[0]->getPosition().y - gameControl->paddles[1]->towerHeight;

	ofSetColor(255, 80);
	if (isCountDown) {
		gameControl->paddles[1]->towerHeight > gameControl->paddles[0]->towerHeight ? ofSetColor(255, 0, 0, 80) : ofSetColor(0, 255, 0, 80);
		paddleTex.draw(gameControl->paddles[0]->getBody()[0]->getPosition().x - settings->settings["paddle"]["width"].get<int>()*0.5, hGoal1);
		gameControl->paddles[0]->towerHeight > gameControl->paddles[1]->towerHeight ? ofSetColor(255, 0, 0, 80) : ofSetColor(0, 255, 0, 80);
		paddleTex.draw(gameControl->paddles[1]->getBody()[0]->getPosition().x - settings->settings["paddle"]["width"].get<int>()*0.5, hGoal2);

	} else {
		paddleTex.draw(gameControl->paddles[0]->getBody()[0]->getPosition().x - settings->settings["paddle"]["width"].get<int>()*0.5, hGoal1);
		paddleTex.draw(gameControl->paddles[1]->getBody()[0]->getPosition().x - settings->settings["paddle"]["width"].get<int>()*0.5, hGoal2);
	}
}

void BackgroundRenderer::drawWinBackground()
{
	ofSetCircleResolution(400);
	int dt = ofGetElapsedTimeMillis() - endStart;
	int height = components->params()->settings["height"];
	int width = components->params()->settings["width"];
	int maxR = components->params()->settings["background"]["maxHeight"].get<float>()*height;

	//circles
	ofSetColor(255, 0, 0);
	float lStripe = ofxeasing::map_clamp(dt, 0, components->params()->settings["background"]["fadeStripes"], 0, height*1.3,&ofxeasing::cubic::easeIn);
	float rCircle = ofClamp(lStripe, 0, maxR);

	ofDrawCircle(width * 0.25, height, rCircle);
	//stripes
	ofSetColor(255);
	int nStripes = components->params()->settings["background"]["nStripes"];
	float dAngle = 180.0 / float(nStripes);
	ofPushMatrix();
	ofTranslate(width * 0.25, height);
	for (size_t i = 0; i < nStripes; ++i) {
		ofPushMatrix();
		ofRotate(i*dAngle+180);
		drawArc(0, 0, lStripe, lStripe, 0, 0.3*dAngle * PI / 180.0);
		ofPopMatrix();
	}
	ofPopMatrix();

	ofDrawCircle(width * 0.25, height, rCircle*0.15);
	//fade kosmonaut
	ofSetColor(255);
	

	int dAvatar = dt - components->params()->settings["background"]["fadeStripes"] - components->params()->settings["background"]["break"] - components->params()->settings["background"]["fadePilot"];
	if (dAvatar > 0) {
		float sizeAvatar = ofxeasing::map_clamp(dt, 0, components->params()->settings["background"]["fadePilot"], 0, components->params()->settings["background"]["sizeAvatar"], &ofxeasing::bounce::easeIn);
		
		int index = dxBackground == 0 ? 0 : 1;
		int h = sizeAvatar * avatars[index].getHeight() / avatars[index].getWidth();
		int x = ((width / 2) - sizeAvatar)*0.5;
		int y = 300;
		avatars[index].draw(x, y, sizeAvatar, h);
	}

	ofSetColor(0);
	ofDrawRectangle(0, height - 100, width, 100);
}

void BackgroundRenderer::drawArc(float x, float y, float width, float height, float start, float stop)
{
	ofPushMatrix();

	ofTranslate(x, y);
	ofScale(width, height, 1);
	float resolution = .02;
	ofBeginShape();
	ofVertex(0, 0);
	for (float theta = start; theta <= stop; theta += resolution) {
		ofVertex(cos(theta), sin(theta));
	}
	ofEndShape(true);

	ofPopMatrix();
}

void BackgroundRenderer::loadKosmonaut(ofJson desc) {
	ofImage img;
	img.load(desc["pic"].get<string>());

	avatars.push_back(ofTexture());
	avatars.back()= img.getTexture();
}

void BackgroundRenderer::onGamestate(ofJson & state)
{
	if (state["function"] != nullptr && state["function"] == "countdown") {
		isCountDown = true;
	} else if (state["function"] != nullptr && state["function"] == "gamestate") {
		isCountDown = false;

		lastState = state["gamestate"].get<string>();
		if (state["gamestate"] == "end1") {
			dxBackground = 0;
			
			endStart = ofGetElapsedTimeMillis();
		}else if (state["gamestate"] == "end2") {
			dxBackground = components->params()->settings["width"].get<int>() * 0.5;
			endStart = ofGetElapsedTimeMillis();
		} else if (state["gamestate"] == "endEven") {
			endStart = ofGetElapsedTimeMillis();
		}
	}
}
