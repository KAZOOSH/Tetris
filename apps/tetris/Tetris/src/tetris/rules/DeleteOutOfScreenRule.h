#pragma once
#include "Rule.h"


class DeleteOutOfScreenRule :
	public Rule
{
public:
	DeleteOutOfScreenRule(GameParameters* params);
	~DeleteOutOfScreenRule();

	void applyRule();
	void onGameEvent(ofJson& event);

protected:
	bool shouldRemoveOffScreen(shared_ptr<ofxBox2dBaseShape> shape);

private:

};

