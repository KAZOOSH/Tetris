/*
 */

#pragma once

#include "ofMain.h"
#include "ModuleDrawable.h"
#include "GameObjects.h"
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

	protected:
		void proceedModuleEvent(ModuleEvent &e);


	private:
		shared_ptr<GameControl> gameControl;
		shared_ptr<GameObjects> objects;

		ofParameter<int> width;
		ofParameter<int> height;
	};
    
}
