/*
 */

#pragma once

#include "ofMain.h"
#include "ModuleDrawable.h"
#include "GameObject.h"
#include "GameFactory.h"
#include "GameControl.h"
#include "PlayerControl.h"
#include "TetrisStone.h"
#include "ofxQuadWarp.h"
#include "GameComponents.h"

#include "GameComponents.h"

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
		shared_ptr<GameComponents> components;


        
    shared_ptr<GameControl> objects;
        

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
	



