#pragma once
#include "RenderObject.h"
#include "ofxBox2dPolygon.h"

class PolygonRenderer : public RenderObject
{
public:
	PolygonRenderer(shared_ptr<ofxBox2dPolygon> renderObject);
	~PolygonRenderer();

	virtual void render();
	void reload();

protected:
	shared_ptr<ofxBox2dPolygon> renderObject;

	ofShader shader;
};

