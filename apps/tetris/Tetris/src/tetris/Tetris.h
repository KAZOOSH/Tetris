/*
 */

#pragma once

#include "ofMain.h"
#include "ModuleDrawable.h"
#include "GameObject.h"
#include "GameFactory.h"
#include "GameControl.h"


namespace ofxModule {
    
	/// \brief the main game class
    class Tetris : public ModuleDrawable{
        
    public:
        
		Tetris(string moduleName = "Tetris");
        
        void update();
        void stopModule();
        void draw();

        void produceStoneByIntervall(UInt64 intervall);
        
		void keyPressed(ofKeyEventArgs & key);
		void keyReleased(ofKeyEventArgs & key) {};

        shared_ptr<GameObject> getLastCreatedStone(int playerId);
        
	protected:
		void proceedModuleEvent(ModuleEvent &e);


	private:
		shared_ptr<GameControl> gameControl;
		shared_ptr<GameObjectContainer> objects;

		ofParameter<int> width;
		ofParameter<int> height;
        
        UInt64 lastStoneProductionTime = ofGetElapsedTimeMillis();
        UInt64 produceStoneIntervallInMillis = 2000;
        Boolean makeHeavyStone = false;
        Boolean makeBouncyStone = false;
	};
    
}
