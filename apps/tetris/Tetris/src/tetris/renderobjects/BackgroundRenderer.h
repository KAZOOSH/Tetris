#pragma once
#include "RenderObject.h"
#include "GameObjectContainer.h"
#include "GameParameters.h"

class BackgroundRenderer: public RenderObject
{
public:
	BackgroundRenderer(GameParameters* params, shared_ptr<GameObjectContainer> objects);
	~BackgroundRenderer();

	virtual void render();
	void reload();

	void onGamestate(ofJson& state);

private:
	GameParameters* params;
	shared_ptr<GameObjectContainer> objects;
	ofShader shader;

	ofFbo goalTex;
	ofFbo paddleTex;

	bool isCountDown = false;
};

