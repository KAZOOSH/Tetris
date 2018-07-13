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
	GameFactory::makePaddle(objects,ofJson());
	GameFactory::makePaddle(objects, ofJson());

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
}

void Tetris::proceedModuleEvent(ModuleEvent &e)
{
	//set paddle position
	if(e.message["function"] != nullptr && e.message["function"] == "paddlePosition"){
		for (size_t i = 0; i < 2; ++i) {
			objects->paddles[i]->setPosition(
				ofMap( e.message["paddle"][i]["x"].get<float>(),0.0,1.0,0,width), 
				ofMap(e.message["paddle"][i]["y"].get<float>(), 0.0, 1.0, 0, height), e.message["paddle"][i]["rot"]);
		}
	
	}

	
}

