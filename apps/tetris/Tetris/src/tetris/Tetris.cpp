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
    shared_ptr<Paddle> p1 =  GameFactory::makePaddle(objects,"paddle1");
    p1->setPosition(200,600);
	objects->addPaddle(p1);
    
    shared_ptr<Paddle> p2 =  GameFactory::makePaddle(objects,"paddle1");
    p2->setPosition(600,600);
	objects->addPaddle(p2);
	
	//add rules
	objects->addRule(GameFactory::makeDeleteOutOfScreenRule());
	ofRegisterKeyEvents(this);
}
//------------------------------------------------------------------
void Tetris::stopModule() {

}

//------------------------------------------------------------------
void Tetris::produceStoneByIntervall(UInt64 intervall) {

    if(lastStoneProductionTime + intervall < ofGetElapsedTimeMillis()){
        lastStoneProductionTime = ofGetElapsedTimeMillis();
        
        // left Player
        auto stone = GameFactory::makeTetrisStone(objects);
        stone->setPlayer(1);
        objects->addGameObject(stone);
        objects->getRule("DeleteOutOfScreenRule")->addObject(stone);
        
        // right Player
        auto stone2 = GameFactory::makeTetrisStone(objects);
        stone2->setPosition(ofVec2f(600,0));
        stone2->setPlayer(2);
        objects->addGameObject(stone2);
        objects->getRule("DeleteOutOfScreenRule")->addObject(stone2);
        
        
    }
}

shared_ptr<GameObject> Tetris::getLastCreatedStone(int playerId){
    for (size_t i = objects->gameObjects.size()-1; i > 0; --i) {
        if(objects->gameObjects[i]->getName() == "TetrisStone"){
            int pId = objects->gameObjects[i]->getPlayerId();
            if(pId == playerId) {
                return objects->gameObjects[i];
            }
        };
    }
}


//------------------------------------------------------------------
void Tetris::update() {
	gameControl->update();
    produceStoneByIntervall(produceStoneIntervallInMillis);
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
    if (key.key == 'b') {
        auto stone = GameFactory::makeTetrisStone(objects);
        objects->addGameObject(stone);
        objects->getRule("DeleteOutOfScreenRule")->addObject(stone);
    }
    
    if (key.key == '1') {
        getLastCreatedStone(1)->makeHeavy();
    }
    if (key.key == '2') {
        getLastCreatedStone(1)->makeBouncy();
    }
    
    
    // rotate last stone for player 1
    if (key.key == 'r') {
        getLastCreatedStone(1)->rotateRight();
    }
    
    if (key.key == 'e') {
        getLastCreatedStone(1)->rotateLeft();
    }
    
    // for testing
    if (key.key == 'q') {
        for (size_t i = 0; i < 2; ++i) {
            objects->paddles[i]->setRotationDiff(-6);
        }
    }
    if (key.key == 'w') {
        for (size_t i = 0; i < 2; ++i) {
            objects->paddles[i]->setRotationDiff(6);
        }
    }
    if (key.key == 'i') {
        for (size_t i = 0; i < 2; ++i) {
            objects->paddles[i]->setDampingDiff(0.1f);
        }
    }
    if (key.key == 'k') {
        for (size_t i = 0; i < 2; ++i) {
            objects->paddles[i]->setDampingDiff(-0.1f);
        }
    }
    if (key.key == 'o') {
        for (size_t i = 0; i < 2; ++i) {
            objects->paddles[i]->setFrequencyDiff(0.1f);
        }
    }
    if (key.key == 'l') {
        for (size_t i = 0; i < 2; ++i) {
            objects->paddles[i]->setFrequencyDiff(-0.1f);
        }
    }
}

void Tetris::proceedModuleEvent(ModuleEvent &e)
{
	//set paddle position
	if(e.message["function"] != nullptr && e.message["function"] == "paddlePosition"){
		for (size_t i = 0; i < 2; ++i) {
			objects->paddles[i]->setPosition(
				ofMap( e.message["paddle"][i]["x"].get<float>(),0.0,1.0,0,width), 
				ofMap(e.message["paddle"][i]["y"].get<float>(), 0.0, 1.0, 0, height));
		}
	
	}

	
}

