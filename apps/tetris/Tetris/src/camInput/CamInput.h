/*
 */

#pragma once

#include "ofMain.h"
#include "ModuleDrawable.h"


namespace ofxModule {
    
	/// \brief control for a webcam 
	/// \ outputes the current Picture as ofTexture via ModuleEvent 
	/// \ outputes can be controlled using ModuleEvents
    class CamInput : public ModuleDrawable{
        
    public:
        
		CamInput(string moduleName = "CamInput");
        
        void update();
        void stopModule();
        void draw();
		void sendPositions();

    protected:
        
    private:

		ofParameter<int> deviceId;
		ofParameter<int> width;
		ofParameter<int> height;
		
		ofVideoGrabber vidGrabber;
    };
    
}
