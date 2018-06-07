/*
 *  ModuleRunner.cpp
 *  example_server_sharedcanvas
 *
 *  Created by Brian Eschrich on 29.07.15
 *  Copyright 2015 reddo UG. All rights reserved.
 *
 */

#include "ModuleRunner.h"
namespace ofxModule {
    
    
void ModuleRunner::addModule(ModuleRunnable* module) {
    modules.push_back(module);
    
}

void ModuleRunner::addModule(ModuleDrawable* mdrawable) {
    modulesDrawable.push_back(mdrawable);
    modules.push_back(mdrawable);
    
}

void ModuleRunner::drawModules(){
    for (int i=0; i<modulesDrawable.size(); ++i) {
        modulesDrawable[i]->draw();
    }
}

void ModuleRunner::updateModules()
{
	for (auto& module : modules) {
		if (module->getSingleThreaded())
		{
			module->update();
		}
	}
}

}