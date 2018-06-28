#include "RenderObject.h"



RenderObject::RenderObject()
{
}

RenderObject::RenderObject(ofJson parameters_)
{
	parameters = parameters_;
}


RenderObject::~RenderObject()
{
}

void RenderObject::setParameters(ofJson parameters_)
{
	parameters = parameters_;
}
