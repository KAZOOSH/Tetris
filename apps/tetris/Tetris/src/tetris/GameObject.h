#pragma once
#include "RenderObject.h"
#include "ofxBox2d.h"

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
	void reloadRenderer();

	void addBody(shared_ptr<ofxBox2dBaseShape> body);
	void removeBody(shared_ptr<ofxBox2dBaseShape> body);
	void removeBody(string bodyName);

	vector<shared_ptr<ofxBox2dBaseShape>> getBody();

	void erase();

	virtual void onBodyAdded(shared_ptr<ofxBox2dBaseShape> body) {};
	ofEvent<uint64_t> eraseEvent;
protected:

	vector<shared_ptr<RenderObject>> renderer;
	vector<shared_ptr<ofxBox2dBaseShape>> body;

	string name ="";
	long id;
};

