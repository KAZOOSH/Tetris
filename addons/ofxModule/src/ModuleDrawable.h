/*
 *  ModuleDrawable.h
 *  voucher_printer
 *
 *  Created by Brian Eschrich on 18.09.15
 *  Copyright 2015 reddo UG. All rights reserved.
 *
 */

#ifndef _ModuleDrawable
#define _ModuleDrawable

#include "ofMain.h"
#include "ModuleRunnable.h"

namespace ofxModule {
    
    
    class ModuleDrawable : public ModuleRunnable{
	
  public:
	
        ModuleDrawable(string moduleClass, string moduleName, int fps = 60):ModuleRunnable(moduleClass,moduleName,fps){} ;
        ModuleDrawable(string moduleClass, string moduleName, bool isStartThread, int fps = 60):ModuleRunnable(moduleClass,moduleName,isStartThread,fps){};
	virtual void draw() = 0;
	
};
    
}

#endif
