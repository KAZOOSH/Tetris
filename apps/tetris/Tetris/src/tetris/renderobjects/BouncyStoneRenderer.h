#pragma once
#include "TetrisStoneRenderer.h"

class BouncyStoneRenderer : public TetrisStoneRenderer
{
public:
	BouncyStoneRenderer(shared_ptr<TetrisStone> stone, ofColor base, ofColor highlight);
protected:
	virtual void updateTile();

	float rotation;
};

