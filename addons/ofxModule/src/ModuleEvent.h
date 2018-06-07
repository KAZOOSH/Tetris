/*
 *  ModuleEvent.h
 *  opencvExample
 *
 *  Created by Brian Eschrich on 16.06.16
 *  Copyright 2017 reddo UG. All rights reserved.
 *
 */

#ifndef _ModuleEvent
#define _ModuleEvent

#include "ofMain.h"

/**
 * @brief event class for communication between modules
 * the event class provides 3 types : messages, images or textures
 */
namespace ofxModule {
    class ModuleEvent {
        
    public:
        enum EventType{
            TYPE_MESSAGE,
            TYPE_TEXTURE,
            TYPE_IMAGE
        };
        
        ModuleEvent(string moduleClass, string id, ofJson message);
        ~ModuleEvent();
        
        string moduleClass;
        string id;
        
        ofJson message;
        ofTexture* texture;
        ofImage* image;
        
        EventType type;
    };
}

#endif
