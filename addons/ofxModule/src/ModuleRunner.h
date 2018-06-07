/*
 *  ModuleRunner.h
 *  example_server_sharedcanvas
 *
 *  Created by Brian Eschrich on 29.07.15
 *  Copyright 2015 reddo UG. All rights reserved.
 *
 */

#ifndef _ModuleRunner
#define _ModuleRunner

//#include "ofMain.h"
#include "ModuleRunnable.h"
#include "ModuleDrawable.h"

namespace ofxModule {
    
    
/**
 * @brief start, stop and init modules
 * start, stop and init modules
 */
class ModuleRunner {
	
  public:
    ModuleRunner(){};
    ~ModuleRunner(){
    };
    void addModule(ModuleRunnable* module);
    void addModule(ModuleDrawable* mdrawable);
    void drawModules();
	void updateModules();
    
    
protected:
    
    
private:
    vector<ModuleRunnable*> modules;
    vector<ModuleDrawable*> modulesDrawable;
};
    
}

#endif
