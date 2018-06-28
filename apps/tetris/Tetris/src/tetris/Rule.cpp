#include "Rule.h"



Rule::Rule()
{
}

Rule::Rule(ofJson parameters_)
{
	parameters = parameters_;
}


Rule::~Rule()
{
}

void Rule::setParameters(ofJson parameters_)
{
	parameters = parameters_;
}
