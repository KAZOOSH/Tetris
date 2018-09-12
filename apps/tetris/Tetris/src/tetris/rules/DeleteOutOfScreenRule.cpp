#include "DeleteOutOfScreenRule.h"
#include "TetrisStone.h"


DeleteOutOfScreenRule::DeleteOutOfScreenRule(shared_ptr<GameComponents> components):GameRule("DeleteOutOfScreenRule",components)
{
	ofAddListener(components->events()->gameEvent, this, &DeleteOutOfScreenRule::onGameEvent);
}


DeleteOutOfScreenRule::~DeleteOutOfScreenRule()
{
}

void DeleteOutOfScreenRule::applyRule()
{
	auto gameControl = components->gameControl()->gameControl;
	for (auto& obj:gameControl){
		bool toDel = false;
		auto bodies = obj->getBody();

		for (auto& body : bodies) {
			if (obj->getName() == "TetrisStone" && shouldRemoveOffScreen(body)){
				toDel = true;
			}
		}
		if (toDel) obj->erase();
	}
}

void DeleteOutOfScreenRule::onGameEvent(ofJson & event)
{
	if (event["function"] != nullptr && event["function"] == "gamestate" && 
		event["gamestate"] == "afterEnd") {
		
		auto gameControl = components->gameControl()->gameControl;
		for (auto& obj : gameControl) {
			bool toDel = false;

			if (obj->getName() == "TetrisStone") {
				obj->erase();
			}
		}
	}
}

bool DeleteOutOfScreenRule::shouldRemoveOffScreen(shared_ptr<ofxBox2dBaseShape> shape)
{
	return !ofRectangle(0, 0, components->params()->settings["width"], components->params()->settings["height"]).inside(shape.get()->getPosition());
}
