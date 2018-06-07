/*
 *  ofxWebModule.cpp
 *  voucher_printer
 *
 *  Created by Brian Eschrich on 24.09.15
 *  Copyright 2015 reddo UG. All rights reserved.
 *
 */

#include "ModuleControl.h"

namespace ofxModule {
//------------------------------------------------------------------
	ModuleControl::ModuleControl() {
    
    moduleRunner = new ModuleRunner();
    xmlLoader = new XmlLoader(moduleRunner);
    oscServer = new OSCServer();
}


XmlLoader* ModuleControl::getXmlLoader(){
    return xmlLoader;
}

ModuleRunner* ModuleControl::getModuleRunner(){
    return moduleRunner;
}

OSCServer* ModuleControl::getOscServer(){
    return oscServer;
}

}