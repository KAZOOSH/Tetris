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

private:
	GameParameters* params;
	shared_ptr<GameObjectContainer> objects;
	ofShader shader;
};

