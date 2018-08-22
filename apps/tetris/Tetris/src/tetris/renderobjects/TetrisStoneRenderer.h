#pragma once
#include "RenderObject.h"
#include "TetrisStone.h"
#include "ofxEasing.h"

class TetrisStoneRenderer :
	public RenderObject
{
public:
	TetrisStoneRenderer(shared_ptr<TetrisStone> stone,ofColor base, ofColor highlight);
	~TetrisStoneRenderer();

	virtual void render();
	void reload();

protected:
	void updateTile();
	void drawTiles(string type, int scale);

private:
	shared_ptr<TetrisStone> stone;
	ofFbo tile;
	ofColor baseColor;
	ofColor highlightColor;
	uint64_t creationTime;

	bool isPartofTower = false;
	uint64_t tPartofTower = 0;
};

