#include "DeleteOutOfScreenRule.h"



DeleteOutOfScreenRule::DeleteOutOfScreenRule(GameParameters* params):Rule("DeleteOutOfScreenRule",params)
{
}


DeleteOutOfScreenRule::~DeleteOutOfScreenRule()
{
}

void DeleteOutOfScreenRule::applyRule()
{
	for (auto& obj:objects){
		bool toDel = false;
		auto bodies = obj->getBody();
		for (auto& body : bodies) {
			if (shouldRemoveOffScreen(body)){
				toDel = true;
			}
		}
		if (toDel) obj->erase();
	}
}

bool DeleteOutOfScreenRule::shouldRemoveOffScreen(shared_ptr<ofxBox2dBaseShape> shape)
{
	return !ofRectangle(0, 0, params->params["width"], params->params["height"]).inside(shape.get()->getPosition());
}
