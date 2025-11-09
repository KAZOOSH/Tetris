#pragma once
#include "TetrisStoneRenderer.h"
class IcyStoneRenderer :
	public TetrisStoneRenderer
{
public:
	IcyStoneRenderer(shared_ptr<TetrisStone> stone, ofColor base, ofColor highlight);
	~IcyStoneRenderer();

	virtual void updateTile();
};

