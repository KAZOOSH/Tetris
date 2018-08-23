#include "TetrisStoneRenderer.h"



TetrisStoneRenderer::TetrisStoneRenderer(shared_ptr<TetrisStone> stone_, ofColor base, ofColor highlight,
	string name, int dmax_, int padding_ , int wLine_ ):RenderObject(name)
{
	stone = stone_;
	dMax = dmax_;
	padding = padding_;
	wLine = wLine_;

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

	int scale = stone->getScale()*2;
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
	ofVec2f v = stone->getBody()[0]->getVelocity();
	ofVec2f d = -ofVec2f(ofxeasing::map_clamp(v.x, 0, 40, 0, dMax,&ofxeasing::sine::easeInOut), 
		ofxeasing::map_clamp(v.y, 0, 40, 0, dMax, &ofxeasing::sine::easeInOut));

	//line
	int wLinet = wLine;
	if (isPartofTower && ofGetElapsedTimeMillis() - tPartofTower < 500) {
		wLinet += ofxeasing::map_clamp(ofGetElapsedTimeMillis() - tPartofTower, 0, 500, 10, 0, &ofxeasing::sine::easeInOut);
	}


	tile.begin();
	ofSetColor(baseColor);
	ofDrawRectangle(0, 0, w, h);
	ofTranslate(d);
	ofSetColor(highlightColor);
	ofDrawRectangle(padding, padding, w- padding*2, h- padding*2);

	if (isPartofTower){// && ofGetElapsedTimeMillis() - tPartofTower > 500) {
		ofSetColor(baseColor);
		ofDrawRectangle(padding + wLinet, padding + wLinet, w - (padding + wLinet) * 2, h - (padding + wLinet) * 2);
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
