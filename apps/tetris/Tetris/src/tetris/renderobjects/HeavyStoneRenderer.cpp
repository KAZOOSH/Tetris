#include "HeavyStoneRenderer.h"



HeavyStoneRenderer::HeavyStoneRenderer(shared_ptr<TetrisStone> stone, ofColor base, ofColor highlight)
	:TetrisStoneRenderer(stone,base,highlight,"HeavyStoneRenderer")
{
}

void HeavyStoneRenderer::updateTile()
{
	int w = tile.getWidth();
	int h = tile.getHeight();

	//speed
	float dMax = 10;
	ofVec2f v = stone->getBody()[0]->getVelocity();
	ofVec2f d = -ofVec2f(ofxeasing::map_clamp(v.x, 0, 40, 0, dMax, &ofxeasing::sine::easeInOut),
		ofxeasing::map_clamp(v.y, 0, 40, 0, dMax, &ofxeasing::sine::easeInOut));

	//line
	float padding = 20;
	int wLine = 10;

	//color
	ofColor base = baseColor;
	ofColor highlight = highlightColor;
	ofColor innerRect = highlightColor;

	innerRect.a = ofxeasing::map_clamp(sin(ofGetElapsedTimef() * 2), -1, 1, 30, 200, &ofxeasing::cubic::easeInOut);

	if (isPartofTower && ofGetElapsedTimeMillis() - tPartofTower < 500) {
		innerRect.a = (innerRect.a + ofxeasing::map_clamp(ofGetElapsedTimeMillis() - tPartofTower, 0, 500, 0, 220, &ofxeasing::sine::easeInOut),0,255);
	} else if (isPartofTower && ofGetElapsedTimeMillis() - tPartofTower > 500) {
		innerRect.a = 255;
	}

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
	ofDrawRectangle(padding, padding, w - padding * 2, h - padding * 2);

	ofSetColor(innerRect);
	ofDrawRectangle(padding + wLine, padding + wLine, w - (padding + wLine) * 2, h - (padding + wLine) * 2);

	tile.end();
}


