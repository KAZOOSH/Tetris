/*
 *
 */

#include "Tetris.h"

using namespace ofxModule;

Tetris::Tetris(string moduleName):ModuleDrawable("Tetris",moduleName,false){
    setSingleThreaded();

	parameters.add(width.set("width", ofGetWidth()));
	parameters.add(height.set("height", ofGetHeight()));
	loadSettings();

	objects = shared_ptr<GameObjectContainer>(new GameObjectContainer());
	objects->initPhysics();

	//create GameControl
	gameControl = shared_ptr<GameControl>(new GameControl(objects));

	//add paddles
	objects->addPaddle( GameFactory::makePaddle(objects,"paddle1"));
	objects->addPaddle(GameFactory::makePaddle(objects, "paddle2"));
	
	//add rules
	objects->addRule(GameFactory::makeDeleteOutOfScreenRule());

	ofRegisterKeyEvents(this);
}
//------------------------------------------------------------------
void Tetris::stopModule() {


}


//------------------------------------------------------------------
void Tetris::update() {
	gameControl->update();
}


//------------------------------------------------------------------
void Tetris::draw() {
	ofSetColor(255);
	gameControl->render();

	ofDrawBitmapString("Anzahl der Objekte: " + ofToString(objects->physics.getBodyCount()), 50, 50);
	
}

void ofxModule::Tetris::keyPressed(ofKeyEventArgs & key)
{
	if (key.key == 'a') {
		auto stone = GameFactory::makeBasicStone(objects);
		objects->addGameObject(stone);
		objects->getRule("DeleteOutOfScreenRule")->addObject(stone);
	}
}

void Tetris::proceedModuleEvent(ModuleEvent &e)
{
	//set paddle position
	if(e.message["function"] != nullptr && e.message["function"] == "paddlePosition"){
		for (size_t i = 0; i < 2; ++i) {
			objects->paddles[i]->setPosition(
				ofMap( e.message["paddle"][i]["x"].get<float>(),0.0,1.0,0,width), 
				ofMap(e.message["paddle"][i]["y"].get<float>(), 0.0, 1.0, 0, height), 
				e.message["paddle"][i]["rot"]);
		}
	
	}

	
}

