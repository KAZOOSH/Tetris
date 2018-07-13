#pragma once

#include "ofMain.h"

class RenderObject
{
public:
	RenderObject(string name);
	~RenderObject();
	
	virtual void render() = 0;
	string getName();

protected:

private:
	string name;
};

