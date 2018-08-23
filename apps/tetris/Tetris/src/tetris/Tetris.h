/*
 */

#pragma once

#include "ofMain.h"
#include "ModuleDrawable.h"
#include "GameObject.h"
#include "GameFactory.h"
#include "GameControl.h"
#include "GameParameters.h"
#include "PlayerControl.h"
#include "TetrisStone.h"
#include "ofxQuadWarp.h"

using namespace ofxModule;

/// \brief the main game class, also does mapping
class Tetris : public ModuleDrawable{
    
public:
    
    Tetris(string moduleName = "Tetris");
    
    void update();
    void stopModule();
    void draw();
    
    void produceStoneByIntervall();
    
    void keyPressed(ofKeyEventArgs & key);
    void keyReleased(ofKeyEventArgs & key) {};
    
    shared_ptr<TetrisStone> getLastCreatedStone(int playerId);
    void onOscMessage(ofxOscMessage & message);
	void onControlEvent(ofJson& event);
	void onGameEvent(ofJson& event);
    
	protected:
		void proceedModuleEvent(ModuleEvent &e);
		void drawWarpedFbo(ofxQuadWarp warper, bool isRight);
        void contactStart(ofxBox2dContactArgs &e);
        
	private:
        float getMinimalDistanceToOtherTowerStonesOrPaddle(shared_ptr<TetrisStone> stone, shared_ptr<Paddle> paddle);
		shared_ptr<GameControl> gameControl;
    shared_ptr<GameControl> gameObjects;
		shared_ptr<GameObjectContainer> objects;
        void setTetrisStoneRelativeToPaddlePosition();
		GameParameters params;
		PlayerControl playerControl;
        void produceStone(int player);
		ofxQuadWarp warperLeft;
		ofxQuadWarp warperRight;
		ofFbo gameFbo;
		ofParameter<int> width;
		ofParameter<int> height;
        uint64 produceStoneIntervallInMillis= 3000;
        uint64 lastStoneProductionTimePlayer1 = 0;
		uint64 lastStoneProductionTimePlayer2 = 0;
        void collisionHandler(TetrisStone* stone);
        bool makeHeavyStone = false;
		bool makeBouncyStone = false;
};
	



