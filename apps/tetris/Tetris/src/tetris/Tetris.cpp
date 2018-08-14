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
	objects->addPaddle(GameFactory::makePaddle(objects,"paddle1"));
	objects->addPaddle(GameFactory::makePaddle(objects, "paddle2"));
	playerControl.setup(objects->paddles, &params);
	
	//add rules
	objects->addRule(GameFactory::makeDeleteOutOfScreenRule(&params));

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
    if (key.key == 'b') {
        auto stone = GameFactory::makeTetrisStone(objects);
        objects->addGameObject(stone);
        objects->getRule("DeleteOutOfScreenRule")->addObject(stone);
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

