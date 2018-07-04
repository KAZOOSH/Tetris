#pragma once
#include "RenderObject.h"
#include "ofxBox2d.h"

class BasicStone
{
public:
	BasicStone(shared_ptr<ofxBox2dBaseShape> body, shared_ptr<RenderObject> renderer);
	~BasicStone();

	shared_ptr<RenderObject> renderer;
	shared_ptr<ofxBox2dBaseShape> body;
};

