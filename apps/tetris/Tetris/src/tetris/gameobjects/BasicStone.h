#pragma once
#include "PolygonRenderer.h"
#include "ofxBox2d.h"

class BasicStone
{
public:
	BasicStone(shared_ptr<ofxBox2dBaseShape> body, shared_ptr<PolygonRenderer> renderer);
	~BasicStone();

};

