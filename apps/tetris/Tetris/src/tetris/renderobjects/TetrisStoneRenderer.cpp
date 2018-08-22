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
	if (stone->getIsPartOfTower() != isPartofTower) {
		isPartofTower = !isPartofTower;
		tPartofTower = ofGetElapsedTimeMillis();
	}

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

	//speed
	float dMax = 25;
	ofVec2f v = stone->getBody()[0]->getVelocity();
	ofVec2f d = -ofVec2f(ofxeasing::map_clamp(v.x, 0, 40, 0, dMax,&ofxeasing::sine::easeInOut), 
		ofxeasing::map_clamp(v.y, 0, 40, 0, dMax, &ofxeasing::sine::easeInOut));

	//line
	float padding = 20;
	int wLine = 10;

	if (isPartofTower && ofGetElapsedTimeMillis() - tPartofTower < 500) {
		wLine += ofxeasing::map_clamp(ofGetElapsedTimeMillis() - tPartofTower, 0, 500, 10, 0, &ofxeasing::sine::easeInOut);
	}

	//color
	ofColor base = baseColor;
	ofColor highlight = highlightColor;
	/*float damping = 1.0;

	if (isPartofTower) {
		base.setHsb(baseColor.getHue(), baseColor.getSaturation()*damping, baseColor.getBrightness()*damping);
		highlight.setHsb(highlightColor.getHue(), highlightColor.getSaturation()*damping, highlightColor.getBrightness()*damping);
	}*/

	tile.begin();
	ofSetColor(base);
	ofDrawRectangle(0, 0, w, h);
	ofTranslate(d);
	ofSetColor(highlight);
	ofDrawRectangle(padding, padding, w- padding*2, h- padding*2);

	if (isPartofTower){// && ofGetElapsedTimeMillis() - tPartofTower > 500) {
		ofSetColor(base);
		ofDrawRectangle(padding + wLine, padding + wLine, w - (padding + wLine) * 2, h - (padding + wLine) * 2);
	}
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
