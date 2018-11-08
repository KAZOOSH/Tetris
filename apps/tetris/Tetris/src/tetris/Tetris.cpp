/*
 *
 */

#include "Tetris.h"

using namespace ofxModule;

Tetris::Tetris(string moduleName):ModuleDrawable("Tetris",moduleName,false){
    setSingleThreaded();
    loadSettings();
    
	components = make_shared<GameComponents>(GameComponents());

	auto gameParams = components->params();
    //create osc
    if (gameParams->settings["isOsc"]) {
		//receiver.setup(12346);
       addOSCServer(new OSCServer(12346));
       ofAddListener(oscServer->oscEvent, this, &Tetris::onOscMessage);
    }

	
    
	ofSetWindowPosition(0, 0);
	ofSetWindowShape(gameParams->settings["width"], gameParams->settings["height"]);

    
    //create Warper
    gameFbo.allocate(gameParams->settings["width"], gameParams->settings["height"]);
    warperLeft.setSourceRect(ofRectangle(0, 0, gameFbo.getWidth()/2, gameFbo.getHeight()));              // this is the source rectangle which is the size of the image and located at ( 0, 0 )
    warperLeft.setTargetRect(ofRectangle(0, 0, gameFbo.getWidth() / 2, gameFbo.getHeight()));
    warperLeft.setup();
    warperLeft.load("_Tetris/warper_left.json");
    
    warperRight.setSourceRect(ofRectangle(0, 0, gameFbo.getWidth() / 2, gameFbo.getHeight()));              // this is the source rectangle which is the size of the image and located at ( 0, 0 )
    warperRight.setTargetRect(ofRectangle(gameFbo.getWidth()/2+10, 0, gameFbo.getWidth() / 2, gameFbo.getHeight()));
    warperRight.setup();
    warperRight.load("_Tetris/warper_right.json");
    
    //create objects
	components->gameControl()->initPhysics(gameParams->settings["physics"]["gravity"].get<float>());
    ofAddListener(components->events()->gameEvent, this, &Tetris::onGameEvent);
    
    //create GameControl
	gameControl = shared_ptr<GameControl>(new GameControl(components->gameControl(), components->events()));
    ofAddListener(components->events()->controlEvent, this, &Tetris::onControlEvent);
    
    // add contact listener
	components->gameControl()->physics.enableEvents();
    
    //add Background
	components->gameControl()->addGameObject(GameFactory::makeBackgroundObject(components));
    
    //add paddles
	shared_ptr<Paddle> p1 =  GameFactory::makePaddle(components,Paddle::paddleNameLeft);
	components->gameControl()->addPaddle(p1);
    
	shared_ptr<Paddle> p2 =  GameFactory::makePaddle(components,Paddle::paddleNameRight);
	components->gameControl()->addPaddle(p2);
    
	playerControl.setup(components);
    
    //add rules
	components->gameControl()->addRule(GameFactory::makeDeleteOutOfScreenRule(components));
	components->gameControl()->addRule(GameFactory::makeGameControlRule(components));
	components->gameControl()->addRule(GameFactory::makeGameEventRule(components));
	components->gameControl()->addRule(GameFactory::makeStoneControlRule(components));
	components->gameControl()->addRule(GameFactory::makeStoneCreationRule(components));

    ofRegisterKeyEvents(this);
}




//------------------------------------------------------------------
void Tetris::stopModule() {
    
}



void Tetris::onOscMessage(ofxOscMessage & message)
{
    if (message.getAddress() == "paddlePosition") {
        playerControl.onPaddleMove(ofJson::parse(message.getArgAsString(0)));
	} else if (message.getAddress() == "buzzer") {
		ofJson out;
		out["control"] = "buzzer";
		components->events()->notifyControlEvent(out);
	}
}

void Tetris::onControlEvent(ofJson & event)
{

}

void Tetris::onGameEvent(ofJson & event)
{
    if (event["function"] != nullptr && event["function"] == "createWorldEffect") {

		auto rule = GameFactory::makeWorldEffect(components, event["params"]);

		/*for (auto obj : components->objects()->objects) {
			if (obj->getName() == "TetrisStone") rule->addObject(obj);
		}*/
        components->gameControl()->addRule(rule);
        
        ofJson out;
        out["function"] = "effect";
        out["effect"] = event["params"]["state"];
        out["player"] = 0;
        components->events()->notifyGameEvent(out);
    }
}


//------------------------------------------------------------------
void Tetris::update() {

	//while (receiver.hasWaitingMessages()) {

	//	// get the next message
	//	ofxOscMessage m;
	//	receiver.getNextMessage(m);
	//	onOscMessage(m);
	//}

    playerControl.update();
    gameControl->update();
	//if(components->events()->gamestate == "game") produceStoneByIntervall();
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
    
    //ofDrawBitmapString("Anzahl der Objekte: " + ofToString(components->gameControl()->physics.getBodyCount()), 50, 50);
    
}

void Tetris::keyPressed(ofKeyEventArgs & key)
{
	if(key.key)
    if (key.key == 'y') {
        ofJson state = ofJson{
            { "function","gamestate" },
            { "gamestate" , "end1" }
        };
		components->events()->notifyGameEvent(state);
    }
    
    if (key.key == 'a') {
        // left Player
		auto stone = GameFactory::makeTetrisStone(components, components->events()->nextCreationRule[0]);
        stone->setPlayer(1);
		components->gameControl()->addGameObject(stone);
		//components->objects()->getRule("DeleteOutOfScreenRule")->addObject(stone);
        
        // right Player
        auto stone2 = GameFactory::makeTetrisStone(components, components->events()->nextCreationRule[1]);
        stone2->setPosition(ofVec2f(600, 0));
        stone2->setPlayer(2);
		components->gameControl()->addGameObject(stone2);
		//components->objects()->getRule("DeleteOutOfScreenRule")->addObject(stone2);
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
        auto stone = GameFactory::makeTetrisStone(components, "base");
        components->gameControl()->addGameObject(stone);
      //  objects->getRule("DeleteOutOfScreenRule")->addObject(stone);
    }
    
   /* if (key.key == '2') {
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
    }*/
    
    if (key.key == 'i') {
        for (size_t i = 0; i < 2; ++i) {
			components->gameControl()->paddles[i]->setDampingDiff(0.1f);
        }
    }
    if (key.key == 'k') {
        for (size_t i = 0; i < 2; ++i) {
			components->gameControl()->paddles[i]->setDampingDiff(-0.1f);
        }
    }
    if (key.key == 'o') {
        for (size_t i = 0; i < 2; ++i) {
			components->gameControl()->paddles[i]->setFrequencyDiff(0.1f);
        }
    }
    if (key.key == 'l') {
        for (size_t i = 0; i < 2; ++i) {
			components->gameControl()->paddles[i]->setFrequencyDiff(-0.1f);
        }
    }
    if (key.key == 'm') {
		components->events()->setRandomNextEffect();
    }
    if (key.key == 'n') {
		components->events()->setNextEffect("icy");
    }
    
}

void Tetris::proceedModuleEvent(ModuleEvent &e)
{
   // cout << e.message.dump(4) << endl;
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

