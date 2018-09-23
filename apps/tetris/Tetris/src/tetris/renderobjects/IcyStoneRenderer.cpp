#include "IcyStoneRenderer.h"



IcyStoneRenderer::IcyStoneRenderer(shared_ptr<TetrisStone> stone, ofColor base, ofColor highlight):TetrisStoneRenderer( stone, base, highlight,"IcyStoneRenderer")
{
}


IcyStoneRenderer::~IcyStoneRenderer()
{
}

void IcyStoneRenderer::updateTile()
{
	int w = tile.getWidth();
	int h = tile.getHeight();

	//speed
	ofVec2f v = stone->getBody()[0]->getVelocity();
	ofVec2f dv = -ofVec2f(ofxeasing::map_clamp(v.x, 0, 40, 0, dMax, &ofxeasing::sine::easeInOut),
		ofxeasing::map_clamp(v.y, 0, 40, 0, dMax, &ofxeasing::sine::easeInOut));

	//line
	ofColor base = baseColor;
	int wLinet = wLine;
	if (isPartofTower && ofGetElapsedTimeMillis() - tPartofTower < 500) {
		wLinet += ofxeasing::map_clamp(ofGetElapsedTimeMillis() - tPartofTower, 0, 500, 10, 0, &ofxeasing::sine::easeInOut);

		base.lerp(ofColor(204, 251, 255),
			ofxeasing::map_clamp(ofGetElapsedTimeMillis() - tPartofTower, 0, 500, 0.0, 1.0, &ofxeasing::sine::easeInOut));
	} else if (isPartofTower) {
		base = ofColor(204, 251, 255);
	}

	ofColor iceColor = ofColor(255, 255, 255);

	tile.begin();
	ofClear(0, 0);
	/*if (isPartofTower) {
		ofSetColor(204, 251, 255);
	} else {
		ofSetColor(baseColor);
	}*/
	ofSetColor(base);
	
	ofDrawRectangle(0, 0, w, h);
	ofTranslate(dv);
	ofSetColor(highlightColor);
	ofDrawRectangle(padding, padding, w - padding * 2, h - padding * 2);
	
	ofSetColor(iceColor);
	ofSetLineWidth(10);
	ofDrawLine(padding, padding, w - padding, padding);
	ofDrawLine(padding, padding, padding, h - padding - h / 2);

	if (isPartofTower) {// && ofGetElapsedTimeMillis() - tPartofTower > 500) {
		ofSetColor(baseColor);
		ofDrawRectangle(padding + wLinet, padding + wLinet, w - (padding + wLinet) * 2, h - (padding + wLinet) * 2);
	}
	tile.end();
}
