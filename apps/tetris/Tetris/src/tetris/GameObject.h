#pragma once
#include "RenderObject.h"
#include "ofxBox2d.h"
//#include "Rule.h"

/// \brief game object class, basically a container which controlls the renderer, rules, and physics objects
class GameObject
{
public:
	GameObject(string name);
	~GameObject();

	string getName();
	long getId();

	//virtual void applyRules();
	virtual void render();

	void addRenderer(shared_ptr<RenderObject> renderer);
	void removeRenderer(shared_ptr<RenderObject> renderer);
	void removeRenderer(string rendererName);

	void addBody(shared_ptr<ofxBox2dBaseShape> body);
	void removeBody(shared_ptr<ofxBox2dBaseShape> body);
	void removeBody(string bodyName);

	vector<shared_ptr<ofxBox2dBaseShape>> getBody();

	/*void addRule(shared_ptr<Rule> rule);
	void removeRule(shared_ptr<Rule> rule);
	void removeRule(string ruleName);
	*/
	void erase();

	virtual void onBodyAdded(shared_ptr<ofxBox2dBaseShape> body) {};

	ofEvent<long> eraseEvent;
protected:

	vector<shared_ptr<RenderObject>> renderer;
	vector<shared_ptr<ofxBox2dBaseShape>> body;
	//vector<shared_ptr<Rule>> rules;

	string name;
	long id;
};

