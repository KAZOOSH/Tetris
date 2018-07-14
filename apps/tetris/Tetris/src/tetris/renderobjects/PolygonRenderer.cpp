#include "PolygonRenderer.h"

PolygonRenderer::PolygonRenderer(shared_ptr<ofxBox2dPolygon> renderObject_):RenderObject("PolygonRenderer")
{
	renderObject = renderObject_;
}

PolygonRenderer::~PolygonRenderer()
{
}

void PolygonRenderer::render()
{
	renderObject->draw();
}
