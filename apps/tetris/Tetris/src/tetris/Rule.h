#pragma once
#include "ofMain.h"

/// \brief abstract definition of a rule
class Rule
{
public:
	Rule();
	Rule(ofJson parameters);
	~Rule();


	virtual void applyRule() = 0;
	void setParameters(ofJson parameters);

private:
	ofJson parameters;
};

