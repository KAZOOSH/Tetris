/*
 */

#pragma once

#include "ofMain.h"
#include "ModuleDrawable.h"


namespace ofxModule {
    
	/// \brief the main game
    class Tetris : public ModuleDrawable{
        
    public:
        
		Tetris(string moduleName = "Tetris");
        
        void update();
        void stopModule();
        void draw();

	protected:
		void proceedModuleEvent(ModuleEvent &e);
	};
    
}
