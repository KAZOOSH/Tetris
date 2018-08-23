#include "BouncyStoneRenderer.h"



BouncyStoneRenderer::BouncyStoneRenderer(shared_ptr<TetrisStone> stone, ofColor base, ofColor highlight)
	:TetrisStoneRenderer(stone, base, highlight, "HeavyStoneRenderer")
{
}

void BouncyStoneRenderer::updateTile()
{
	int w = tile.getWidth();
	int h = tile.getHeight();

	//speed
	float dMax = 25;
	ofVec2f v = stone->getBody()[0]->getVelocity();
	ofVec2f d = -ofVec2f(ofxeasing::map_clamp(v.x, 0, 40, 0, dMax, &ofxeasing::sine::easeInOut),
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
	

	float dRotation = 10;
	if (!isPartofTower) {
		rotation = ofGetElapsedTimef();
	}

	tile.begin();
	ofSetColor(base);
	ofDrawRectangle(0, 0, w, h);
	ofTranslate(d);
	
	ofTranslate(ofVec2f(sin(rotation)*dRotation, cos(rotation)*dRotation));

	ofSetColor(highlight);
	ofDrawCircle(padding + wLine, padding + wLine, w - (padding + wLine) * 2, h - (padding + wLine) * 2);
	
	tile.end();
}

