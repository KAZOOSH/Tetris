/*
 */

#pragma once

#include "ofMain.h"
#include "ModuleDrawable.h"
#include "GameObject.h"
#include "GameFactory.h"
#include "GameControl.h"
#include "GameParameters.h"

#include "ofxQuadWarp.h"

namespace ofxModule {
    
	/// \brief the main game class, also does mapping
    class Tetris : public ModuleDrawable{
        
    public:
        
		Tetris(string moduleName = "Tetris");
        
        void update();
        void stopModule();
        void draw();

		void keyPressed(ofKeyEventArgs & key);
		void keyReleased(ofKeyEventArgs & key) {};

	protected:
		void proceedModuleEvent(ModuleEvent &e);
		void drawWarpedFbo(ofxQuadWarp warper, bool isRight);

	private:
		shared_ptr<GameControl> gameControl;
		shared_ptr<GameObjectContainer> objects;
		GameParameters params;

		ofxQuadWarp warperLeft;
		ofxQuadWarp warperRight;
		ofFbo gameFbo;
	};
    
}
