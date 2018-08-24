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
    
	ofSetWindowPosition(0, 0);
	ofSetWindowShape(params.params["width"], params.params["height"]);

    produceStoneIntervallInMillis = params.params["tetrisStone"]["produceEveryMilliseconds"].get<uint64_t>();
    
    //add creation rules
    params.nextCreationRule.push_back("base");
    params.nextCreationRule.push_back("base");
    
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
    objects = shared_ptr<GameObjectContainer>(new GameObjectContainer(&params));
    objects->initPhysics();
    ofAddListener(params.gameEvent, this, &Tetris::onGameEvent);
    
    //create GameControl
    gameObjects = shared_ptr<GameControl>(new GameControl(objects));
    ofAddListener(params.controlEvent, this, &Tetris::onControlEvent);
    
    // add contact listener
    objects->physics.enableEvents();
    ofAddListener(objects->physics.contactStartEvents, this, &Tetris::contactStart);
    
    //add Background
    objects->addGameObject(GameFactory::makeBackgroundObject(objects, &params));
    
    
    //add paddles
    shared_ptr<Paddle> p1 =  GameFactory::makePaddle(objects,Paddle::paddleNameLeft,&params);
    objects->addPaddle(p1);
    
    shared_ptr<Paddle> p2 =  GameFactory::makePaddle(objects,Paddle::paddleNameRight,&params);
    objects->addPaddle(p2);
    
    playerControl.setup(objects->paddles, &params);
    
    //add rules
    objects->addRule(GameFactory::makeDeleteOutOfScreenRule(&params));
    objects->addRule(GameFactory::makeGameControlRule(&params,objects.get()));
    objects->addRule(GameFactory::makeGameEventRule(&params));
    
    
    ofRegisterKeyEvents(this);
}

void Tetris::contactStart(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) {
        TetrisStone * stone;
        
        if((TetrisStone*)e.a->GetBody()->GetUserData()){
            stone = (TetrisStone*)e.a->GetBody()->GetUserData();
            collisionHandler(stone);
        }
        
        if((TetrisStone*)e.b->GetBody()->GetUserData()){
            stone = (TetrisStone*)e.b->GetBody()->GetUserData();
            collisionHandler(stone);
        }
    }
}

void Tetris::collisionHandler(TetrisStone* stone) {
    int minimumYPosToCreateStoneOnCollide = 1000;
    //check colliding objects produce new stone immediately on first collision of last created stone
    if(stone->getBody().size()>0) {
        
        if(!stone->collided){
            if(stone->getBody()[0]->getPosition().y > minimumYPosToCreateStoneOnCollide){
                if(stone->getPlayerId()==1){
                    lastStoneProductionTimePlayer1 =0;
                } else if(stone->getPlayerId()==2){
                    lastStoneProductionTimePlayer2 =0;
                }
            }
            stone->collide();
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
    
        if(getLastCreatedStone(player) == nullptr || getLastCreatedStone(player)->getBody()[0]->getPosition().y >500){
                //create stone
                auto stone = GameFactory::makeTetrisStone(objects,&params, params.nextCreationRule[player-1]);
                stone->setPlayer(player);
            
            
                //notify effect if present
                if (params.nextCreationRule[player - 1] != "base") {
                    ofJson out;
                    out["function"] = "effect";
                    out["effect"] = params.nextCreationRule[player - 1];
                    out["player"] = player;
                    params.notifyGameEvent(out);
                }
            
                if (params.nextCreationRule[player - 1] == "quicky") {
                    stone->getBody()[0]->addForce(ofVec2f(0, 1), 10000);
                }
                if (params.nextCreationRule[player - 1] == "rotary") {
                    stone->getBody()[0]->addImpulseForce(stone->getBody()[0]->getB2DPosition()+ofVec2f(10,0), ofVec2f(0,5000));
                }
            
                // set stone effect for active player back to base
                params.nextCreationRule[player-1] = "base";
            
                if(player == 1) {
                    lastStoneProductionTimePlayer1 = ofGetElapsedTimeMillis();
                    stone->setPosition(ofVec2f(300,0));
                }
                if(player == 2){
                    lastStoneProductionTimePlayer2 = ofGetElapsedTimeMillis();
                    stone->setPosition(ofVec2f(1500,0));
                }
                objects->addGameObject(stone);
                objects->getRule("DeleteOutOfScreenRule")->addObject(stone);
                gameObjects->registerEraseEvent(stone->eraseEvent);
        } else{
            if(player == 1) {
                lastStoneProductionTimePlayer1 = ofGetElapsedTimeMillis() +produceStoneIntervallInMillis/2 ;
            }
            if(player == 2){
                lastStoneProductionTimePlayer2 = ofGetElapsedTimeMillis()
                    +produceStoneIntervallInMillis/2 ;
            }
        }
}

float Tetris::getMinimalDistanceToOtherTowerStonesOrPaddle(shared_ptr<TetrisStone> stone, shared_ptr<Paddle> paddle) {
    
    float minimumDistance = 100000;
    float distance = 0;
    // check all stones and set sistance if its
    for (size_t i = objects->gameObjects.size()-1; i > 0; --i) {
        if(objects->gameObjects[i]->getName() == "TetrisStone" && objects->gameObjects[i]->getId() != stone->getId()){
            shared_ptr<TetrisStone> otherStone = std::static_pointer_cast<TetrisStone>(objects->gameObjects[i]);
            if(otherStone->getBody().size()>0 && otherStone->getIsPartOfTower()){
                distance = (stone->getBody()[0]->getPosition()-otherStone->getBody()[0]->getPosition()).length();
                if(distance < minimumDistance){
                    minimumDistance = distance;
                }
            }
        }
    }
    distance = (paddle->getPaddleBodyPosition() - stone->getBody()[0]->getPosition()).length();
    if(distance < minimumDistance){
        minimumDistance = distance;
    }
    return minimumDistance;
}

/**
 * setTetrisStoneRelativeToPaddlePosition
 * set Stone Position and get towerheight
 */
void Tetris::setTetrisStoneRelativeToPaddlePosition() {
    
    int towerHeightPaddleLeft = 0;
    int towerHeightPaddleRight = 0;
    
    // get Paddles
    shared_ptr<Paddle> paddleLeft = objects->getPaddle(Paddle::paddleNameLeft);
    shared_ptr<Paddle> paddleRight = objects->getPaddle(Paddle::paddleNameRight);
    
    // iterate over tetrisstones
    for (size_t i = objects->gameObjects.size()-1; i > 0; --i) {
        if(objects->gameObjects[i]->getName() == "TetrisStone"){
            if(objects->gameObjects[i]){
                shared_ptr<TetrisStone> stone = std::static_pointer_cast<TetrisStone>(objects->gameObjects[i]);
                
                int pId = stone->getPlayerId();
                int y = 10000;
                
                
                if(stone->getBody().size()>0 && stone->collided){
                    // get Height if its part of the tower
                    if(stone->getIsPartOfTower()){
                        y = stone->getBody()[0]->getPosition().y;
                    }
                    
                    if(pId == 1) {
                        ofVec2f plp =paddleLeft->getPaddleBodyPosition();
                        float distanceToPaddleOrOtherTetrisStone = getMinimalDistanceToOtherTowerStonesOrPaddle(stone,paddleLeft);
                        stone->updateRelativeToPaddlePosition(plp,distanceToPaddleOrOtherTetrisStone);
                        towerHeightPaddleLeft = max(towerHeightPaddleLeft,max(0, (int)plp.y-y));
                        paddleLeft->towerHeight = towerHeightPaddleLeft;
                        
                    }else if(pId == 2) {
                        ofVec2f prp =paddleRight->getPaddleBodyPosition();
                        float distanceToPaddleOrOtherTetrisStone = getMinimalDistanceToOtherTowerStonesOrPaddle(stone,paddleRight);
                        stone->updateRelativeToPaddlePosition(prp,distanceToPaddleOrOtherTetrisStone);
                        towerHeightPaddleRight  = max(towerHeightPaddleRight,max(0, (int)prp.y-y));
                        paddleRight->towerHeight = towerHeightPaddleRight;
                    }
                }
            }
        };
    }
}


shared_ptr<TetrisStone> Tetris::getLastCreatedStone(int playerId) {
    for (size_t i = objects->gameObjects.size()-1; i > 0; --i) {
        shared_ptr<TetrisStone> stone= std::static_pointer_cast<TetrisStone>(objects->gameObjects[i]);
        
        if(stone->getName() == "TetrisStone"){
            int pId = stone->getPlayerId();
            if(pId == playerId) {
                return stone;
            }
        };
    }
    return nullptr;
}

void Tetris::onOscMessage(ofxOscMessage & message)
{
    if (message.getAddress() == "paddlePosition") {
        playerControl.onPaddleMove(ofJson::parse(message.getArgAsString(0)));
    }
}

void Tetris::onControlEvent(ofJson & event)
{
    if (params.gamestate == "game") {
        if (event["control"] != nullptr && event["control"] == "pedal") {
            shared_ptr<TetrisStone> stone = getLastCreatedStone(event["player"]);
            if (event["direction"] == "left") {
                if(getLastCreatedStone(event["player"]) != nullptr){
                    stone->rotateLeft();
                }
            } else {
                if(stone!= nullptr){
                    stone->rotateRight();
                }
            }
        } else if (event["control"] != nullptr && event["control"] == "buzzer") {
            params.setRandomNextEffect();
        }
    }
}

void Tetris::onGameEvent(ofJson & event)
{
    if (event["function"] != nullptr && event["function"] == "createWorldEffect") {
        objects->addRule(GameFactory::makeWorldEffect(&params, event["params"]));
        
        ofJson out;
        out["function"] = "effect";
        out["effect"] = event["params"]["state"];
        out["player"] = 0;
        params.notifyGameEvent(out);
    }
}


//------------------------------------------------------------------
void Tetris::update() {
    playerControl.update();
    gameObjects->update();
    produceStoneByIntervall();
    setTetrisStoneRelativeToPaddlePosition();
}



//------------------------------------------------------------------
void Tetris::draw() {
    ofSetColor(255);
    //draw game
    gameFbo.begin();
    ofClear(0, 0);
    gameObjects->render();
    gameFbo.end();
    
    //do warping
    drawWarpedFbo(warperLeft,false);
    drawWarpedFbo(warperRight, true);
    
    ofDrawBitmapString("Anzahl der Objekte: " + ofToString(objects->physics.getBodyCount()), 50, 50);
    
}

void Tetris::keyPressed(ofKeyEventArgs & key)
{
	if(key.key)
    if (key.key == 'y') {
        ofJson state = ofJson{
            { "function","gamestate" },
            { "gamestate" , "end1" }
        };
        params.notifyGameEvent(state);
    }
    
    if (key.key == 'a') {
        // left Player
        auto stone = GameFactory::makeTetrisStone(objects, &params, params.nextCreationRule[0]);
        stone->setPlayer(1);
        objects->addGameObject(stone);
        objects->getRule("DeleteOutOfScreenRule")->addObject(stone);
        
        // right Player
        auto stone2 = GameFactory::makeTetrisStone(objects, &params, params.nextCreationRule[1]);
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
        gameObjects->reloadRenderer();
    }
    
    if (key.key == 'b') {
        auto stone = GameFactory::makeTetrisStone(objects, &params, "base");
        objects->addGameObject(stone);
        objects->getRule("DeleteOutOfScreenRule")->addObject(stone);
    }
    
    if (key.key == '2') {
        getLastCreatedStone(1)->makeBouncy();
    }
    
    // rotate last stone for player 1
    if (key.key == 'r') {
        if(getLastCreatedStone(1) != nullptr){
            getLastCreatedStone(1)->rotateRight();
        }
    }
    
    if (key.key == 'e') {
        if(getLastCreatedStone(1) != nullptr){
            getLastCreatedStone(1)->rotateLeft();
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
    if (key.key == 'm') {
        params.nextCreationRule[0] = "rotary";
        params.nextCreationRule[1] = "quicky";
    }
    if (key.key == 'n') {
        params.setNextEffect("wind");
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

