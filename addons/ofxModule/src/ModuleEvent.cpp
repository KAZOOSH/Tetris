/*
 *  ModuleEvent.cpp
 *  opencvExample
 *
 *  Created by Brian Eschrich on 16.06.16
 *  Copyright 2017 reddo UG. All rights reserved.
 *
 */

#include "ModuleEvent.h"

namespace ofxModule {
    
    ModuleEvent::ModuleEvent(string moduleClass_, string id_, ofJson message_)
    {
        moduleClass = moduleClass_;
        id = id_;
        message = message_;
        type = TYPE_MESSAGE;
        
        texture = nullptr;
        image = nullptr;
    }
    
    ModuleEvent::~ModuleEvent()
    {
       
    }
    
    
}