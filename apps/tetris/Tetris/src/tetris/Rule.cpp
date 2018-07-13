#include "Rule.h"



Rule::Rule(string name_)
{
	name = name_;
}



Rule::~Rule()
{
}

string Rule::getName()
{
	return name;
}

