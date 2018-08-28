#include "InfoPanel.h"


InfoPanel::InfoPanel(ofJson settings, ofJson description, ofxFontStash* fontMain, ofxFontStash* fontSub)
{
	int h = description["height"] != nullptr ? description["height"] : settings["textFields"]["main"]["h"];
	mainText = createTextField(fontMain, description["main"], settings["textFields"]["main"]["y"], h, settings["width"]);
	subText = createTextField(fontSub, description["sub"], settings["textFields"]["sub"]["y"], settings["textFields"]["sub"]["h"], settings["width"]);
	duration = description["time"];

	//sound
	if (description["sound"] != nullptr && description["sound"] != "") {
		sound.load("sound/" + description["sound"].get<string>());
	}
}

void InfoPanel::start()
{
	tStart = ofGetElapsedTimeMillis();
	if (sound.isLoaded()) sound.play();
}

void InfoPanel::draw(int x)
{
	uint64_t now = ofGetElapsedTimeMillis();
	if (now - tStart < duration) {
		ofPopMatrix();
		ofTranslate(x, 0);
		//main
		//todo bouncy fade in
		float scale = 1.0;
		if (now - tStart < 1000) scale = ofxeasing::map_clamp(now, tStart, tStart + 1000, 0, 1.0, &ofxeasing::bounce::easeIn);
		else if (tStart + duration - now < 1000) scale = ofxeasing::map_clamp(now, tStart + duration - 1000, tStart + duration, 1.0, 0.0, &ofxeasing::bounce::easeOut);

		ofPushMatrix();
		ofTranslate(mainText->position);
		ofTranslate((1 - scale)* mainText->size*0.5);
		mainText->texture.draw(ofVec2f(0, 0), mainText->size.x*scale, mainText->size.y*scale);
		ofPopMatrix();

		//sub
		float alpha = 1.0;
		if (now - tStart < 500) alpha = ofxeasing::map_clamp(now, tStart, tStart + 500, 0, 1.0, &ofxeasing::quad::easeIn);
		else if (tStart + duration - now < 700) alpha = ofxeasing::map_clamp(now, tStart + duration - 700, tStart + duration, 1.0, 0.0, &ofxeasing::quad::easeOut);
		subText->texture.draw(subText->position, subText->size.x, subText->size.y);
		ofPopMatrix();
	}
}

void InfoPanel::setPanning(panning direction)
{
	playerPanning = direction;
	switch (direction) {
	case panning::center:
		sound.setPan(0);
		break;
	case panning::left:
		sound.setPan(-1.f);
		break;
	case panning::right:
		sound.setPan(1.f);
		break;
	}
	
}

void InfoPanel::setPlayer(int player_)
{
	player = player_;
	setPanning(static_cast<panning>(player));
}

TextField* InfoPanel::createTextField(ofxFontStash* font, string text, int y, int h, int wScreen)
{
	auto bb = font->getStringBoundingBox(text, 0, 0);
	ofFbo fbo;
	fbo.allocate(bb.width, bb.height);
	fbo.begin();
	ofClear(0, 0);
	ofSetColor(255);
	font->draw(text, 250, 0, fbo.getHeight()*0.9);
	fbo.end();

	ofVec2f size = ofVec2f(fbo.getWidth()*h / fbo.getHeight(), h);
	ofVec2f pos = ofVec2f(0.5*(0.5*wScreen - size.x), y);

	return new TextField(fbo, size, pos);
}

int InfoPanel::getPlayer()
{
	return player;
}

int InfoPanel::getDuration()
{
	return duration;
}

uint64_t InfoPanel::getStart()
{
	return tStart;
}
