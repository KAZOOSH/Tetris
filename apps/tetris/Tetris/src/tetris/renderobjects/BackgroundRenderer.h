#pragma once
#include "RenderObject.h"
#include "GameObjectContainer.h"
#include "GameParameters.h"
#include "GameComponents.h"
#include "ofxEasing.h"

class BackgroundRenderer: public RenderObject
{
public:
	BackgroundRenderer(shared_ptr<GameComponents> components);
	~BackgroundRenderer();

	virtual void render();
	void reload();

	void onGamestate(ofJson& state);

protected:
	void drawGameBackground();
	void drawWinBackground();

	void drawArc(float x, float y, float width, float height, float start, float stop);

	void loadKosmonaut(ofJson desc);
private:
	shared_ptr<GameComponents> components;
	shared_ptr<GameParameters> settings;
	shared_ptr<GameObjectContainer> gameControl;
	ofShader shader;

	ofFbo goalTex;
	ofFbo paddleTex;

	bool isCountDown = false;
	uint64_t endStart = 0;

	string lastState = "endEven";
	int dxBackground = 0;

	vector<ofTexture> avatars;
};

