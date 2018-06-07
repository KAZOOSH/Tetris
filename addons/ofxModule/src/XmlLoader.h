/*
 *  XMLLoader.h
 *  example_server_sharedcanvas
 *
 *  Created by Brian Eschrich on 28.07.15
 *  Copyright 2015 reddo UG. All rights reserved.
 *
 */

#ifndef _XMLLoader
#define _XMLLoader

#include "ofMain.h"
#include "ModuleRunner.h"

namespace ofxModule {

/** 
 * @brief  loads and saves xml files (settings)
 * loads and saves xml files (settings)
 */
class XmlLoader {
	
  public:
    XmlLoader(ModuleRunner* moduleRunner);
    ~XmlLoader(){
    };
    
    int xmlHasModule(string modulname);
    void addModule(ModuleRunnable* module);
    void addModule(ModuleDrawable* mdrawable);
    
    string getAttribute (string module, string attribute, int indexModule = 0);
    void createModuleConnections();
	
protected:
    
    
    
private:
    
    ofXml XML;
    
    //for init
    
    //for building connections
    map<string, ModuleRunnable* > idMap;
    map<ModuleRunnable*, vector<string> > inputs;

    
    void addInput (ModuleRunnable* module, string input);
    void addInput (ModuleRunnable* module, vector<string> inputs);
    

    
    
    bool addToInputs(ModuleRunnable* module);
    void createInputList (ModuleRunnable* module);

    
    ModuleRunner* moduleRunner;
};
}

#endif
