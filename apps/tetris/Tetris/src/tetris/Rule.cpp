#include "Rule.h"



Rule::Rule(string name_, int runtime_)
{
	name = name_;
	//components = components_;

	creationTime = ofGetElapsedTimeMillis();
	runtime = runtime_;

}


string Rule::getName()
{
	return name;
}

int Rule::getRuntime()
{
	return runtime;
}

uint64_t Rule::getCreationTime()
{
	return creationTime;
}
