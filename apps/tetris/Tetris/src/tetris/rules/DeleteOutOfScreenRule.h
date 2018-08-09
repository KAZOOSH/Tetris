#pragma once
#include "Rule.h"
class DeleteOutOfScreenRule :
	public Rule
{
public:
	DeleteOutOfScreenRule(GameParameters* params);
	~DeleteOutOfScreenRule();

	void applyRule();

protected:
	bool shouldRemoveOffScreen(shared_ptr<ofxBox2dBaseShape> shape);

private:

};

