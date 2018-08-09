#pragma once
#include "ofMain.h"
#include "GameObject.h"
#include "GameParameters.h"

/// \brief abstract definition of a rule
class Rule
{
public:
	Rule(string name, GameParameters* params);
	~Rule();

	string getName();

	void addObject(shared_ptr<GameObject> obj);
	void removeObject(shared_ptr<GameObject> obj);
	void removeObject(long id);

	virtual void applyRule() = 0;

protected:
	vector<shared_ptr<GameObject>> objects;
	string name;
	GameParameters* params;
};

