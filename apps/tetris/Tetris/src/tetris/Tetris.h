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
   
    
    void keyPressed(ofKeyEventArgs & key);
    void keyReleased(ofKeyEventArgs & key) {};
    
    
    void onOscMessage(ofxOscMessage & message);
	void onControlEvent(ofJson& event);
	void onGameEvent(ofJson& event);
    
	protected:
		void proceedModuleEvent(ModuleEvent &e);
		void drawWarpedFbo(ofxQuadWarp warper, bool isRight);
        
        
	private:
		shared_ptr<GameComponents> components;


        
    shared_ptr<GameControl> gameControl;
        

		PlayerControl playerControl;
		ofxQuadWarp warperLeft;
		ofxQuadWarp warperRight;
		ofFbo gameFbo;
		ofParameter<int> width;
		ofParameter<int> height;
        
        bool makeHeavyStone = false;
		bool makeBouncyStone = false;
};
	



