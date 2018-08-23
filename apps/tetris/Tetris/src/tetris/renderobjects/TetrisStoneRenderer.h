#pragma once
#include "RenderObject.h"
#include "TetrisStone.h"
#include "ofxEasing.h"

class TetrisStoneRenderer :
	public RenderObject
{
public:
	TetrisStoneRenderer(shared_ptr<TetrisStone> stone, ofColor base, ofColor highlight, string name = "TetrisStoneRenderer",
		int dmax = 25, int padding = 20, int wLine = 10);
	~TetrisStoneRenderer();

	virtual void render();
	void reload();

protected:
	virtual void updateTile();
	virtual void drawTiles(string type, int scale);

	shared_ptr<TetrisStone> stone;
	ofFbo tile;
	ofColor baseColor;
	ofColor highlightColor;
	uint64_t creationTime;

	bool isPartofTower = false;
	uint64_t tPartofTower = 0;


	//drawing params
	float dMax = 25;
	float padding = 20;
	int wLine = 10;
};

