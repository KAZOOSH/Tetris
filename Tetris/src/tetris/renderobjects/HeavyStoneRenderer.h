#pragma once

#include "TetrisStoneRenderer.h"

class HeavyStoneRenderer : public TetrisStoneRenderer
{
public:
	HeavyStoneRenderer(shared_ptr<TetrisStone> stone, ofColor base, ofColor highlight);

protected:
	virtual void updateTile();
};

