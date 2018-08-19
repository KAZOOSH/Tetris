#include "PolygonRenderer.h"

PolygonRenderer::PolygonRenderer(shared_ptr<ofxBox2dPolygon> renderObject_):RenderObject("PolygonRenderer")
{
	renderObject = renderObject_;

	auto coords = renderObject->mesh.getTexCoords();

	//shader.load("shaders/tetrisStone");
}

PolygonRenderer::~PolygonRenderer()
{
}

void PolygonRenderer::render()
{
	renderObject->getVelocity();
	//renderObject->draw();

	ofPushMatrix();
	ofTranslate(renderObject->getPosition());
	ofRotateDeg(renderObject->getRotation(), 0, 0, 1);
	shader.begin();
	renderObject->mesh.draw();
	shader.end();
	ofPopMatrix();
}

void PolygonRenderer::reload()
{
	shader.load("shaders/tetrisStone");
}
