#include "TetrisStoneRenderer.h"



TetrisStoneRenderer::TetrisStoneRenderer(shared_ptr<TetrisStone> stone_, ofColor base, ofColor highlight):RenderObject("TetrisStoneRenderer")
{
	stone = stone_;

	tile.allocate(128, 128);
	updateTile();

	baseColor = base;
	highlightColor = highlight;

	creationTime = ofGetElapsedTimeMillis();
}

void TetrisStoneRenderer::render()
{
	updateTile();

	int scale = stone->getScale();
	auto body = stone->getBody()[0];
	ofPushStyle();
	ofPushMatrix();
	ofTranslate(body->getPosition());
	ofRotateDeg(body->getRotation(), 0, 0, 1);
	ofSetColor(255);
	drawTiles(stone->getType(),scale);
	ofPopMatrix();
	ofPopStyle();
}

void TetrisStoneRenderer::reload()
{
}

void TetrisStoneRenderer::updateTile()
{
	int w = tile.getWidth();
	int h = tile.getHeight();

	float t = ((ofGetElapsedTimeMillis()+ creationTime) / 3) % 500 * 2*PI /500;
	float padding = sin(t) * 5 + 15;
	int wLine = 10;

	tile.begin();
	ofSetColor(baseColor);
	ofDrawRectangle(0, 0, w, h);
	ofSetColor(highlightColor);
	ofDrawRectangle(padding, padding, w- padding*2, h- padding*2);
	ofSetColor(baseColor);
	ofDrawRectangle(padding+wLine, padding+ wLine, w - (padding+ wLine) *2 , h - (padding + wLine)*2);
	tile.end();
}

void TetrisStoneRenderer::drawTiles(string type,int scale)
{
	if (type == "stone_L") {
		ofPushMatrix();
		ofTranslate(-scale * 0.75, -scale * 0.75);
		tile.draw(0, -scale, scale, scale);
		tile.draw(0, 0, scale, scale);
		tile.draw(0, scale, scale, scale);
		tile.draw(scale, scale, scale, scale);
		ofPopMatrix();
	}else if (type == "stone_Z") {
		ofPushMatrix();
		ofTranslate(-scale * 0.5, 0);
		tile.draw(-scale, -scale, scale, scale);
		tile.draw(0, -scale, scale, scale);
		tile.draw(0, 0, scale, scale);
		tile.draw(scale, 0, scale, scale);
		ofPopMatrix();
	} else if (type == "stone_I") {
		ofPushMatrix();
		ofTranslate(-scale * 0.5, -scale * 0.5);
		tile.draw(0, -scale, scale, scale);
		tile.draw(0, 0, scale, scale);
		tile.draw(0, scale, scale, scale);
		ofPopMatrix();
	} else if (type == "stone_O") {
		tile.draw(0, 0, scale, scale);
		tile.draw(-scale, 0, scale, scale);
		tile.draw(-scale, -scale, scale, scale);
		tile.draw(0, -scale, scale, scale);
	} else if (type == "stone_T") {
		ofPushMatrix();
		ofTranslate(-scale * 0.5, -scale * 0.25);
		tile.draw(0, -scale, scale, scale);
		tile.draw(0, 0, scale, scale);
		tile.draw(-scale, 0, scale, scale);
		tile.draw(scale, 0, scale, scale);
		ofPopMatrix();
	}
}


TetrisStoneRenderer::~TetrisStoneRenderer()
{
}
