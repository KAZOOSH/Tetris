#include "BackgroundRenderer.h"



BackgroundRenderer::BackgroundRenderer(GameParameters* params_, shared_ptr<GameObjectContainer> objects_):RenderObject("BackgroundRenderer")
{
	params = params_;
	objects = objects_;
}


BackgroundRenderer::~BackgroundRenderer()
{
}

void BackgroundRenderer::render()
{
	ofSetColor(255, 0, 0);
	ofDrawRectangle(0, 0, 1000, 1000);
}

void BackgroundRenderer::reload()
{
}
