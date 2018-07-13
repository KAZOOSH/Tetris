#pragma once
#include "ofMain.h"

/// \brief abstract definition of a rule
class Rule
{
public:
	Rule(string name);
	~Rule();

	string getName();

	virtual void applyRules() = 0;

private:
	string name;
};

