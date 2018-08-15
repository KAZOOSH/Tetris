/*
 *
 */

#include "Tetris.h"

using namespace ofxModule;

Tetris::Tetris(string moduleName):ModuleDrawable("Tetris",moduleName,false){
    setSingleThreaded();
	loadSettings();

	//create Warper
	gameFbo.allocate(params.params["width"], params.params["height"]);
	warperLeft.setSourceRect(ofRectangle(0, 0, gameFbo.getWidth()/2, gameFbo.getHeight()));              // this is the source rectangle which is the size of the image and located at ( 0, 0 )
	warperLeft.setTargetRect(ofRectangle(0, 0, gameFbo.getWidth() / 2, gameFbo.getHeight()));
	warperLeft.setup();
	//warper.load(); // reload last saved changes.

	warperRight.setSourceRect(ofRectangle(0, 0, gameFbo.getWidth() / 2, gameFbo.getHeight()));              // this is the source rectangle which is the size of the image and located at ( 0, 0 )
	warperRight.setTargetRect(ofRectangle(gameFbo.getWidth()/2+10, 0, gameFbo.getWidth() / 2, gameFbo.getHeight()));
	warperRight.setup();

	//create objects
	objects = shared_ptr<GameObjectContainer>(new GameObjectContainer());
	objects->initPhysics();

	//create GameControl
	gameControl = shared_ptr<GameControl>(new GameControl(objects));

	//add paddles
    shared_ptr<Paddle> p1 =  GameFactory::makePaddle(objects,"paddle1");
    //p1->setPosition(200,600);
	objects->addPaddle(p1);
    
    shared_ptr<Paddle> p2 =  GameFactory::makePaddle(objects,"paddle1");
   // p2->setPosition(600,600);
	objects->addPaddle(p2);

	playerControl.setup(objects->paddles, &params);
	
	//add rules
	objects->addRule(GameFactory::makeDeleteOutOfScreenRule(&params));
	objects->addRule(GameFactory::makeGameControlRule(&params));

	ofRegisterKeyEvents(this);
}
//------------------------------------------------------------------
void Tetris::stopModule() {

}

//------------------------------------------------------------------
void Tetris::produceStoneByIntervall(uint64 intervall) {

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
	//draw game
	gameFbo.begin();
	ofClear(0, 0);
	gameControl->render();
	gameFbo.end();

	//do warping
	drawWarpedFbo(warperLeft,false);
	drawWarpedFbo(warperRight, true);

	ofDrawBitmapString("Anzahl der Objekte: " + ofToString(objects->physics.getBodyCount()), 50, 50);
	
}

void ofxModule::Tetris::keyPressed(ofKeyEventArgs & key)
{
	if (key.key == 'a') {
		auto stone = GameFactory::makeBasicStone(objects);
		objects->addGameObject(stone);
		objects->getRule("DeleteOutOfScreenRule")->addObject(stone);
	}

	if (key.key == 't' ) {
		warperLeft.toggleShow();
		warperRight.toggleShow();
	}

	if (key.key == 'l') {
		warperLeft.load("_Tetris/warper_left.json");
		warperRight.load("_Tetris/warper_right.json");
	}

	if (key.key == 's') {
		warperLeft.save("_Tetris/warper_left.json");
		warperRight.save("_Tetris/warper_right.json");
	}

	if (key.key == '#') {
		gameControl->reloadRenderer();
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
    if (key.key == '3') {
        getLastCreatedStone(1)->makeLarge();
    }
    
    // rotate last stone for player 1
    if (key.key == 'r') {
        getLastCreatedStone(1)->rotateRight();
    }
    
    if (key.key == 'e') {
        getLastCreatedStone(1)->rotateLeft();
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
		playerControl.onPaddleMove(e.message);
	}

}

void ofxModule::Tetris::drawWarpedFbo(ofxQuadWarp warper, bool isRight)
{
	//======================== get our quad warp matrix.

	ofMatrix4x4 mat = warper.getMatrix();

	//======================== use the matrix to transform our fbo.

	ofPushMatrix();
	ofMultMatrix(mat);
	ofSetColor(255);
	if(!isRight) gameFbo.getTexture().drawSubsection(ofRectangle(0, 0, gameFbo.getWidth() / 2, gameFbo.getHeight()), ofRectangle(0, 0, gameFbo.getWidth() / 2, gameFbo.getHeight()));
	else gameFbo.getTexture().drawSubsection(ofRectangle(0, 0, gameFbo.getWidth() / 2, gameFbo.getHeight()), ofRectangle(gameFbo.getWidth() / 2, 0, gameFbo.getWidth() / 2, gameFbo.getHeight()));
	ofPopMatrix();

	//======================== draw quad warp ui.

	ofSetColor(ofColor::magenta);
	warper.drawQuadOutline();

	ofSetColor(ofColor::yellow);
	warper.drawCorners();

	ofSetColor(ofColor::magenta);
	warper.drawHighlightedCorner();

	ofSetColor(ofColor::red);
	warper.drawSelectedCorner();
}

