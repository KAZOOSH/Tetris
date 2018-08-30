#include "Rule.h"



Rule::Rule(string name_, GameParameters* params_, int runtime_)
{
	name = name_;
	params = params_;

	creationTime = ofGetElapsedTimeMillis();
	runtime = runtime_;

	objects = make_shared<vector<shared_ptr<GameObject>>>(params->getObjects().gameObjects);
}


string Rule::getName()
{
	return name;
}

//void Rule::addObject(shared_ptr<GameObject> obj)
//{
//	objects.push_back(obj);
//}

//void Rule::removeObject(shared_ptr<GameObject> obj)
//{
//	vector<shared_ptr<GameObject>>::iterator position = find(objects.begin(), objects.end(), obj);
//	if (position != objects.end()) // == myVector.end() means the element was not found
//		objects.erase(position);
//}

//void Rule::removeObject(long id)
//{
//	auto position = find_if(objects.begin(), objects.end(),
//		[&id](const shared_ptr<GameObject> elem) { return elem->getId() == id; });
//	if (position != objects.end()) {
//		objects.erase(position);
//	}
//}

int Rule::getRuntime()
{
	return runtime;
}

uint64_t Rule::getCreationTime()
{
	return creationTime;
}
