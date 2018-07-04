#pragma once

#include "ofMain.h"

class RenderObject
{
public:
	RenderObject();
	RenderObject(ofJson parameters);
	~RenderObject();
	
	virtual void render() = 0;
	void setParameters(ofJson parameters);

protected:
	ofJson parameters;
};

