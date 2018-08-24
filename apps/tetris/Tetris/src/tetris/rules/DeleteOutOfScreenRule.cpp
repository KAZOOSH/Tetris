#include "DeleteOutOfScreenRule.h"
#include "TetrisStone.h"


DeleteOutOfScreenRule::DeleteOutOfScreenRule(GameParameters* params):Rule("DeleteOutOfScreenRule",params)
{
	ofAddListener(params->gameEvent, this, &DeleteOutOfScreenRule::onGameEvent);
}


DeleteOutOfScreenRule::~DeleteOutOfScreenRule()
{
}

void DeleteOutOfScreenRule::applyRule()
{
	for (auto& obj:objects){
		bool toDel = false;
        
        if(obj->getName() == "TetrisStone"){
            shared_ptr<TetrisStone> stone = std::static_pointer_cast<TetrisStone>(obj);
            if(!stone->collided) {
                for (auto& body : stone->getBody()) {
                    body->setVelocity(0, 10);
                    body->enableGravity(false);
                };
            } else{
                for (auto& body : stone->getBody()) {
                    body->enableGravity(true);
                };
            }
            
        }
  
        
        
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
				//cout << "del body" << endl;
				toDel = true;
			}
		}
		if (toDel) obj->erase();
	}
}

void DeleteOutOfScreenRule::onGameEvent(ofJson & event)
{
	if (event["function"] != nullptr && event["function"] == "gamestate" && 
		event["gamestate"] == "idle") {
		
		for (auto& obj : objects) {
			bool toDel = false;

			if (obj->getName() == "TetrisStone") {
				obj->erase();
			}
		}
	}
}

bool DeleteOutOfScreenRule::shouldRemoveOffScreen(shared_ptr<ofxBox2dBaseShape> shape)
{
	return !ofRectangle(0, 0, params->params["width"], params->params["height"]).inside(shape.get()->getPosition());
}
