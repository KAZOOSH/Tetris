//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//

#pragma once


#include "ofMain.h"
#include "ofxSerial.h"


class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    ofx::IO::SerialDevice device;

};
