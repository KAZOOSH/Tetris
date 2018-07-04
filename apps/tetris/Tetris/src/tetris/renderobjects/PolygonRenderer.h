#pragma once
#include "RenderObject.h"

class PolygonRenderer : public RenderObject 
{
public:
	PolygonRenderer();
	~PolygonRenderer();

	virtual void render();
};

