#include "RenderObject.h"



RenderObject::RenderObject(string name_)
{
	name = name_;
}

RenderObject::~RenderObject()
{
}

string RenderObject::getName()
{
	return name;
}

