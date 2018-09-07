#pragma once
#include "GameRule.h"


class DeleteOutOfScreenRule :
	public GameRule
{
public:
	DeleteOutOfScreenRule(shared_ptr<GameComponents> components);
	~DeleteOutOfScreenRule();

	void applyRule();
	void onGameEvent(ofJson& event);

protected:
	bool shouldRemoveOffScreen(shared_ptr<ofxBox2dBaseShape> shape);

private:

};

