#pragma once
#include "Rule.h"
#include "RenderObject.h"
#include <vector>

class CreationRules {
	void clear() {
		rules.clear();
		renderObjects.clear();
	};

	vector<shared_ptr<Rule>> rules;
	vector<shared_ptr<RenderObject>> renderObjects;
};

