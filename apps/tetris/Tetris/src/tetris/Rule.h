#pragma once
#include "ofMain.h"
#include "GameObject.h"
//#include "GameObjectContainer.h"


/// \brief abstract definition of a rule
class Rule
{
public:
	Rule(string name, int runtime = 0);

	string getName();

//	void addObject(shared_ptr<GameObject> obj);
//	void removeObject(shared_ptr<GameObject> obj);
//	void removeObject(long id);

	virtual void applyRule() = 0;
	virtual void draw() {}; //used to draw rule specific information

	int getRuntime();
	uint64_t getCreationTime();

protected:
	string name;
	//shared_ptr<GameComponents> components;
	int runtime = 0;
	uint64_t creationTime;
};

