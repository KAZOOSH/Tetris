#include "DeleteOutOfScreenRule.h"



DeleteOutOfScreenRule::DeleteOutOfScreenRule():Rule("DeleteOutOfScreenRule")
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
			if (ofxBox2dBaseShape::shouldRemoveOffScreen(body)){
				toDel = true;
			}
		}
		if (toDel) obj->erase();
	}
}
