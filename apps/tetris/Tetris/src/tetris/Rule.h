#pragma once
#include "ofMain.h"
#include "GameObject.h"
#include "GameParameters.h"

/// \brief abstract definition of a rule
class Rule
{
public:
	Rule(string name, GameParameters* params, int runtime = 0);
	~Rule();

	string getName();

	void addObject(shared_ptr<GameObject> obj);
	void removeObject(shared_ptr<GameObject> obj);
	void removeObject(long id);

	virtual void applyRule() = 0;
	virtual void draw() {}; //used to draw rule specific information

	int getRuntime();
	uint64_t getCreationTime();

protected:
	vector<shared_ptr<GameObject>> objects;
	string name;
	GameParameters* params;
	int runtime = 0;
	uint64_t creationTime;
};

