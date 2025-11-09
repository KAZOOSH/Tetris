#include "BouncyStoneRenderer.h"



BouncyStoneRenderer::BouncyStoneRenderer(shared_ptr<TetrisStone> stone, ofColor base, ofColor highlight)
	:TetrisStoneRenderer(stone, base, highlight, "BouncyStoneRenderer")
{
}

void BouncyStoneRenderer::updateTile()
{
	int w = tile.getWidth();
	int h = tile.getHeight();

	//speed
	ofVec2f v = stone->getBody()[0]->getVelocity();
	ofVec2f d = ofVec2f(64 + ofxeasing::map_clamp(v.x, 0, 40, -0, 0, &ofxeasing::sine::easeInOut),64+
		ofxeasing::map_clamp(v.y, 0, 40, -20, 20, &ofxeasing::sine::easeInOut));
	

	float dRotation = 20;
	if (!isPartofTower) {
		rotation = ofGetElapsedTimef()*10;
	}

	tile.begin();
	ofSetColor(baseColor);
	ofDrawRectangle(0, 0, w, h);
	ofTranslate(d);
	
	ofTranslate(ofVec2f(sin(rotation)*dRotation, cos(rotation)*dRotation));

	ofSetColor(highlightColor);
	ofDrawCircle(0, 0 , 30);
	
	tile.end();
}

void BouncyStoneRenderer::drawTiles(string type, int scale)
{
	if (type == "stone_L") {
		ofPushMatrix();
		ofTranslate(-scale * 0.75, -scale * 0.75);
		tile.draw(0, -scale, scale, scale);
		tile.draw(0, 0, scale, scale);
		tile.draw(0, scale, scale, scale);
		tile.draw(scale, scale, scale, scale);
		ofPopMatrix();
	} else if (type == "stone_Z") {
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

