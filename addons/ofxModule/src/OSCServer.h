/*
 *  OSCServer.h
 *  reddo_power_box
 *
 *  Created by Brian Eschrich on 27.08.15
 *  Copyright 2015 reddo UG. All rights reserved.
 *
 */

#ifndef _OSCServer
#define _OSCServer

//#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxOscEvent.h"

namespace ofxModule {
    
/**
 * @brief OSC server and client
 * creates an OSC server at port 12345
 * modules can register on messages and use them to send messages
 */
class OSCServer : public ofxOscEventListener{
	
  public:
    OSCServer();
	OSCServer(int port);
    ~OSCServer(){
    };
	
	void sendMessage(ofxOscMessage message, int port = 12346, string ip = "localhost");
	void update();
	void draw();
    
    ofEvent<ofxOscMessage> oscEvent;
    
protected:
    
    
    void onPacketIn(ofxOscMessage & message);
    ofxOscSender* getSender(int port, string ip);
    
private:
    
    pair< pair<string,int>, ofxOscSender*> createSender(int port, string ip);
    ofxOscEvent oscServer;
    map< pair<string,int>, ofxOscSender*> senders;
	
};
    
}

#endif
