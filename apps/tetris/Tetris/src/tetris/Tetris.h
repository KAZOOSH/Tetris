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

#include "ofxQuadWarp.h"

namespace ofxModule {
    
	/// \brief the main game class, also does mapping
    class Tetris : public ModuleDrawable{
        
    public:
        
		Tetris(string moduleName = "Tetris");
        
        void update();
        void stopModule();
        void draw();

        void produceStoneByIntervall(uint64 intervall);
        
		void keyPressed(ofKeyEventArgs & key);
		void keyReleased(ofKeyEventArgs & key) {};

        shared_ptr<GameObject> getLastCreatedStone(int playerId);
        
	protected:
		void proceedModuleEvent(ModuleEvent &e);
		void drawWarpedFbo(ofxQuadWarp warper, bool isRight);

	private:
		shared_ptr<GameControl> gameControl;
		shared_ptr<GameObjectContainer> objects;
		GameParameters params;
		PlayerControl playerControl;

		ofxQuadWarp warperLeft;
		ofxQuadWarp warperRight;
		ofFbo gameFbo;
		ofParameter<int> width;
		ofParameter<int> height;
        
        uint64 lastStoneProductionTime = ofGetElapsedTimeMillis();
		uint64 produceStoneIntervallInMillis = 3000;
        bool makeHeavyStone = false;
		bool makeBouncyStone = false;
	};
    
}
