#include "BackgroundRenderer.h"



BackgroundRenderer::BackgroundRenderer(shared_ptr<GameComponents> components_):RenderObject("BackgroundRenderer")
{
	components = components_;
	settings = components->params();
	objects = components->objects();
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

	ofAddListener(components->events()->gameEvent, this, &BackgroundRenderer::onGamestate);
}


BackgroundRenderer::~BackgroundRenderer()
{
}

void BackgroundRenderer::render()
{
	ofPushStyle();
	shader.begin();
	shader.setUniform1f("windowWidth", float(settings->settings["width"].get<int>()));
	shader.setUniform1f("windowHeight", float(settings->settings["height"].get<int>()));

	ofDrawRectangle(0, 0, settings->settings["width"], settings->settings["height"]);

	shader.end();


	ofSetColor(0);
	int h = settings->settings["height"].get<int>();
	int hBase = (1.0 - components->events()->winningHeight)*h;
	int y1 = hBase - (h - objects->paddles[0]->getBody()[0]->getPosition().y);
	int y2 = hBase - (h - objects->paddles[1]->getBody()[0]->getPosition().y);
	ofDrawRectangle(0, y1, settings->settings["width"].get<int>() / 2, h-y1);
	ofDrawRectangle(settings->settings["width"].get<int>() / 2, y2, settings->settings["width"].get<int>() / 2, h-y2);
	
	ofSetColor(255,80);
	goalTex.draw(0, y1-10);
	goalTex.draw(settings->settings["width"].get<int>() / 2, y2-10);
	//ofDrawRectangle(0, y1, params->params["width"].get<int>() / 2, 5);
	//ofDrawRectangle(params->params["width"].get<int>() / 2, y2, params->params["width"].get<int>() / 2, 5);
	ofPopStyle();


	int hGoal1 = objects->paddles[0]->getBody()[0]->getPosition().y- objects->paddles[0]->towerHeight;
	int hGoal2 = objects->paddles[1]->getBody()[0]->getPosition().y - objects->paddles[1]->towerHeight;
	
	ofSetColor(255, 80);
	if (isCountDown) {
		objects->paddles[1]->towerHeight > objects->paddles[0]->towerHeight ? ofSetColor(255,0,0, 80) : ofSetColor(0, 255, 0, 80);
		paddleTex.draw(objects->paddles[0]->getBody()[0]->getPosition().x - settings->settings["paddle"]["width"].get<int>()*0.5, hGoal1);
		objects->paddles[0]->towerHeight > objects->paddles[1]->towerHeight ? ofSetColor(255, 0, 0, 80) : ofSetColor(0, 255, 0, 80);
		paddleTex.draw(objects->paddles[1]->getBody()[0]->getPosition().x - settings->settings["paddle"]["width"].get<int>()*0.5, hGoal2);

	} else {
		paddleTex.draw(objects->paddles[0]->getBody()[0]->getPosition().x - settings->settings["paddle"]["width"].get<int>()*0.5, hGoal1);
		paddleTex.draw(objects->paddles[1]->getBody()[0]->getPosition().x - settings->settings["paddle"]["width"].get<int>()*0.5, hGoal2);
	}
	
	//ofDrawRectangle(0, hGoal1, params->params["width"].get<int>() / 2, 5);
	//ofDrawRectangle(params->params["width"].get<int>() / 2, hGoal2, params->params["width"].get<int>() / 2, 5);
}

void BackgroundRenderer::reload()
{
	shader.load("shaders/bg");
}

void BackgroundRenderer::onGamestate(ofJson & state)
{
	if (state["function"] != nullptr && state["function"] == "countdown") {
		isCountDown = true;
	} else if (state["function"] != nullptr && state["function"] == "gamestate") {
		isCountDown = false;
	}
}
