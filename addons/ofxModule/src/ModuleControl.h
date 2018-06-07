/*
 *  ofxWebModule.h
 *  reddo_power_box
 *
 *  Created by Brian Eschrich on 08.09.15
 *  Copyright 2015 reddo UG. All rights reserved.
 *
 */

#ifndef _ofxModule
#define _ofxModule

#include "DataLog.h"
#include "DataLogger.h"
#include "GeneralPurposeFunctions.h"
#include "ModuleRunnable.h"
#include "ModuleRunner.h"
#include "OSCServer.h"
#include "ParameterParser.h"
#include "XmlLoader.h"

namespace ofxModule {

class ModuleControl {
    
public:
    
	ModuleControl();
    
    XmlLoader*      getXmlLoader();
    ModuleRunner*   getModuleRunner();
    OSCServer*      getOscServer();
    
private:
    XmlLoader*      xmlLoader;
    ModuleRunner*   moduleRunner;
    OSCServer*      oscServer;
    
    
};
    
}

#endif

