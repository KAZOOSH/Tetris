#pragma once
#include "RenderObject.h"
#include "GameObjectContainer.h"
#include "GameParameters.h"
#include "GameComponents.h"

class BackgroundRenderer: public RenderObject
{
public:
	BackgroundRenderer(shared_ptr<GameComponents> components);
	~BackgroundRenderer();

	virtual void render();
	void reload();

	void onGamestate(ofJson& state);

private:
	shared_ptr<GameComponents> components;
	shared_ptr<GameParameters> settings;
	shared_ptr<GameObjectContainer> gameControl;
	ofShader shader;

	ofFbo goalTex;
	ofFbo paddleTex;

	bool isCountDown = false;
};

