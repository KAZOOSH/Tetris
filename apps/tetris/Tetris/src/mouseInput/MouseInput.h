/*
 */

#pragma once

#include "ofMain.h"
#include "ModuleDrawable.h"


namespace ofxModule {
    
	/// \brief control for a webcam 
	/// \ outputes the current Picture as ofTexture via ModuleEvent 
	/// \ outputes can be controlled using ModuleEvents
    class MouseInput : public ModuleDrawable{
        
    public:
        
		MouseInput(string moduleName = "MouseInput");
        
        void update();
        void stopModule();
        void draw();

    protected:
        
    private:

    };
    
}
