#include "BackgroundRenderer.h"



BackgroundRenderer::BackgroundRenderer(GameParameters* params_, shared_ptr<GameObjectContainer> objects_):RenderObject("BackgroundRenderer")
{
	params = params_;
	objects = objects_;
	shader.load("shaders/bg");
}


BackgroundRenderer::~BackgroundRenderer()
{
}

void BackgroundRenderer::render()
{
	ofPushStyle();
	shader.begin();
	shader.setUniform1f("windowWidth", float(params->params["width"].get<int>()));
	shader.setUniform1f("windowHeight", float(params->params["height"].get<int>()));

	ofDrawRectangle(0, 0, params->params["width"], params->params["height"]);

	shader.end();


	ofSetColor(0);
	int h = params->params["height"].get<int>();
	int hBase = (1.0 - params->winningHeight)*h;
	int y1 = hBase - (h - objects->paddles[0]->getBody()[0]->getPosition().y);
	int y2 = hBase - (h - objects->paddles[1]->getBody()[0]->getPosition().y);
	ofDrawRectangle(0, y1, params->params["width"].get<int>() / 2, h-y1);
	ofDrawRectangle(params->params["width"].get<int>() / 2, y2, params->params["width"].get<int>() / 2, h-y2);
	
	ofSetColor(60);
	ofDrawRectangle(0, y1, params->params["width"].get<int>() / 2, 5);
	ofDrawRectangle(params->params["width"].get<int>() / 2, y2, params->params["width"].get<int>() / 2, 5);
	ofPopStyle();
}

void BackgroundRenderer::reload()
{
	shader.load("shaders/bg");
}
