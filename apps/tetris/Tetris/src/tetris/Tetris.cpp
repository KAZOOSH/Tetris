/*
 *
 */

#include "Tetris.h"

using namespace ofxModule;

Tetris::Tetris(string moduleName):ModuleDrawable("Tetris",moduleName,false){
    setSingleThreaded();
	loadSettings();

	//create osc
	if (params.params["isOsc"]) {
		addOSCServer(new OSCServer(12346));
		ofAddListener(oscServer->oscEvent, this, &Tetris::onOscMessage);
	}

    produceStoneIntervallInMillis = params.params["tetrisStone"]["produceEveryMilliseconds"].get<uint64_t>();


	//create Warper
	gameFbo.allocate(params.params["width"], params.params["height"]);
	warperLeft.setSourceRect(ofRectangle(0, 0, gameFbo.getWidth()/2, gameFbo.getHeight()));              // this is the source rectangle which is the size of the image and located at ( 0, 0 )
	warperLeft.setTargetRect(ofRectangle(0, 0, gameFbo.getWidth() / 2, gameFbo.getHeight()));
	warperLeft.setup();
	warperLeft.load("_Tetris/warper_left.json");

	warperRight.setSourceRect(ofRectangle(0, 0, gameFbo.getWidth() / 2, gameFbo.getHeight()));              // this is the source rectangle which is the size of the image and located at ( 0, 0 )
	warperRight.setTargetRect(ofRectangle(gameFbo.getWidth()/2+10, 0, gameFbo.getWidth() / 2, gameFbo.getHeight()));
	warperRight.setup();
	warperRight.load("_Tetris/warper_right.json");

	//create objects
	objects = shared_ptr<GameObjectContainer>(new GameObjectContainer());
	objects->initPhysics();

	//create GameControl
	gameControl = shared_ptr<GameControl>(new GameControl(objects));

    // add contact listener
    objects->physics.enableEvents();
    ofAddListener(objects->physics.contactStartEvents, this, &Tetris::contactStart);
    
	//add paddles
    shared_ptr<Paddle> p1 =  GameFactory::makePaddle(objects,Paddle::paddleNameLeft,&params);
	objects->addPaddle(p1);
    
    shared_ptr<Paddle> p2 =  GameFactory::makePaddle(objects,Paddle::paddleNameRight,&params);
	objects->addPaddle(p2);

	playerControl.setup(objects->paddles, &params);
	
	//add rules
	objects->addRule(GameFactory::makeDeleteOutOfScreenRule(&params));
	objects->addRule(GameFactory::makeGameControlRule(&params));

	ofRegisterKeyEvents(this);
}

void Tetris::contactStart(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) {
        TetrisStone * stoneA = (TetrisStone*)e.a->GetBody()->GetUserData();
        TetrisStone * stoneB = (TetrisStone*)e.b->GetBody()->GetUserData();
        
        //check colliding objects produce new stone immediately on first collision of last created stone
        if(stoneA) {
            if(!stoneA->collided){
                if(stoneA->getPlayerId()==1){
                    lastStoneProductionTimePlayer1 =0;
                } else if(stoneA->getPlayerId()==2){
                    lastStoneProductionTimePlayer2 =0;
                }
                stoneA->collide();
            }
        }
        if(stoneB) {
            if(!stoneB->collided){
                if(stoneB->getPlayerId()==1){
                    lastStoneProductionTimePlayer1 =0;
                } else if(stoneB->getPlayerId()==2){
                    lastStoneProductionTimePlayer2 =0;
                }
                stoneB->collide();
            }
        }
    }
}

//------------------------------------------------------------------
void Tetris::stopModule() {

}

//------------------------------------------------------------------
void Tetris::produceStoneByIntervall() {
    if(lastStoneProductionTimePlayer1 + produceStoneIntervallInMillis < ofGetElapsedTimeMillis()){
            produceStone(1);
        }
    if(lastStoneProductionTimePlayer2 + produceStoneIntervallInMillis < ofGetElapsedTimeMillis()){
        produceStone(2);
    }
}

void Tetris::produceStone(int player) {
    
    auto stone = GameFactory::makeTetrisStone(objects,&params);
    stone->setPlayer(player);
    
    if(player == 1) {
        lastStoneProductionTimePlayer1 = ofGetElapsedTimeMillis();
    }
    if(player == 2){
      lastStoneProductionTimePlayer2 = ofGetElapsedTimeMillis();
      stone->setPosition(ofVec2f(1500,0));
    }
    objects->addGameObject(stone);
    objects->getRule("DeleteOutOfScreenRule")->addObject(stone);
}

void Tetris::setTetrisStoneRelativeToPaddlePosition() {
    
    int towerHeightPaddleLeft = 0;
    int towerHeightPaddleRight = 0;

    shared_ptr<Paddle> paddleLeft = objects->getPaddle(Paddle::paddleNameLeft);
    shared_ptr<Paddle> paddleRight = objects->getPaddle(Paddle::paddleNameRight);
    
    for (size_t i = objects->gameObjects.size()-1; i > 0; --i) {
        if(objects->gameObjects[i]->getName() == "TetrisStone"){
            int pId = objects->gameObjects[i]->getPlayerId();
            int y = 10000;
            if(objects->gameObjects[i]->getIsPartOfTower()){
                
                if(objects->gameObjects[i]){
                    if(objects->gameObjects[i]->getBody().size()>0){
                         y = objects->gameObjects[i]->getBody()[0]->getPosition().y;
                    }
                  
                }
                
            }

            if(pId == 1) {
                ofVec2f plp =paddleLeft->getPaddleBodyPosition();
                objects->gameObjects[i]->updateRelativeToPaddlePosition(plp);
                towerHeightPaddleLeft = max(towerHeightPaddleLeft,max(0, (int)plp.y-y));
                paddleLeft->towerHeight = towerHeightPaddleLeft;
            }else if(pId == 2) {
                ofVec2f prp =paddleRight->getPaddleBodyPosition();
                objects->gameObjects[i]->updateRelativeToPaddlePosition(paddleRight->getPaddleBodyPosition());
                towerHeightPaddleRight = max(towerHeightPaddleRight,max(0, (int)prp.y-y));
                 paddleRight->towerHeight = towerHeightPaddleRight;
            }
            
            
        };
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

void Tetris::onOscMessage(ofxOscMessage & message)
{
	if (message.getAddress() == "paddlePosition") {
		playerControl.onPaddleMove(ofJson::parse(message.getArgAsString(0)));
	}
}


//------------------------------------------------------------------
void Tetris::update() {
	gameControl->update();
    produceStoneByIntervall();
    setTetrisStoneRelativeToPaddlePosition();
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

void Tetris::keyPressed(ofKeyEventArgs & key)
{
	if (key.key == 'y') {
		ofJson state = ofJson{
			{ "function","gamestate" },
			{ "gamestate" , "end1" }
		};
		params.notifyGameEvent(state);
	}

	if (key.key == 'a') {
		// left Player
		auto stone = GameFactory::makeTetrisStone(objects, &params);
		stone->setPlayer(1);
		objects->addGameObject(stone);
		objects->getRule("DeleteOutOfScreenRule")->addObject(stone);

		// right Player
		auto stone2 = GameFactory::makeTetrisStone(objects, &params);
		stone2->setPosition(ofVec2f(600, 0));
		stone2->setPlayer(2);
		objects->addGameObject(stone2);
		objects->getRule("DeleteOutOfScreenRule")->addObject(stone2);
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
        auto stone = GameFactory::makeTetrisStone(objects, &params);
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
	//cout << e.message.dump(4) << endl;
	//set paddle position
	if(e.message["function"] != nullptr && (e.message["function"] == "paddle1Position" || e.message["function"] == "paddle2Position")){
		playerControl.onPaddleMove(e.message);
	}

}

void Tetris::drawWarpedFbo(ofxQuadWarp warper, bool isRight)
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

