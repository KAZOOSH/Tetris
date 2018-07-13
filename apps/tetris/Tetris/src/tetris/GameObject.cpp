#include "GameObject.h"



GameObject::GameObject(string name_)
{
	name = name_;
}


GameObject::~GameObject()
{
}

void GameObject::applyRules()
{
	for (auto& rule : rules) {
		rule->applyRules();
	}
}

void GameObject::render()
{
	for (auto& r : renderer) {
		r->render();
	}
}

void GameObject::addRenderer(shared_ptr<RenderObject> renderer_)
{
	renderer.push_back(renderer_);
}

void GameObject::removeRenderer(shared_ptr<RenderObject> renderer_)
{
	vector<shared_ptr<RenderObject>>::iterator position = find(renderer.begin(), renderer.end(), renderer_);
	if (position != renderer.end()) // == myVector.end() means the element was not found
		renderer.erase(position);
}

void GameObject::removeRenderer(string rendererName)
{
	auto position = find_if(renderer.begin(), renderer.end(),
		[&rendererName](const shared_ptr<RenderObject> elem){ return elem->getName() == rendererName; });
	if (position != renderer.end()) {
		renderer.erase(position);
	}

	/*int toDel = -1;
	for (size_t i = 0; i < renderer.size(); i++){
		if (renderer[i]->getName() == rendererName) toDel = i;
		break;
	}*/
}

void GameObject::addBody(shared_ptr<ofxBox2dBaseShape> body_)
{
	body.push_back(body_);
}

void GameObject::removeBody(shared_ptr<ofxBox2dBaseShape> body_)
{
	vector<shared_ptr<ofxBox2dBaseShape>>::iterator position = find(body.begin(), body.end(), body_);
	if (position != body.end()) // == myVector.end() means the element was not found
		body.erase(position);
}

void GameObject::removeBody(string bodyName)
{
	auto position = find_if(body.begin(), body.end(),
		[&bodyName](const shared_ptr<ofxBox2dBaseShape> elem) {return *(string*)elem->getData() == bodyName; });
	if (position != body.end()) {
		body.erase(position);
	}
}

void GameObject::addRule(shared_ptr<Rule> rule_)
{
	rules.push_back(rule_);
}

void GameObject::removeRule(shared_ptr<Rule> rule_)
{
	vector<shared_ptr<Rule>>::iterator position = find(rules.begin(), rules.end(), rule_);
	if (position != rules.end()) // == myVector.end() means the element was not found
		rules.erase(position);
}

void GameObject::removeRule(string ruleName)
{
	auto position = find_if(rules.begin(), rules.end(),
		[&ruleName](const shared_ptr<Rule> elem) { return elem->getName() == ruleName; });
	if (position != rules.end()) {
		rules.erase(position);
	}
}
