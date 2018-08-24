#include "DeleteOutOfScreenRule.h"
#include "TetrisStone.h"


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
		if (obj->getName() == "TetrisStone") {
			auto tet = std::static_pointer_cast<TetrisStone>(obj);
			if (!tet->collided)
			{
				for (auto& body : bodies) {
					body->addForce(ofVec2f(0, -1), 500);
				}
			}
			
		}
		for (auto& body : bodies) {
			if (shouldRemoveOffScreen(body)){
				cout << "del body" << endl;
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
