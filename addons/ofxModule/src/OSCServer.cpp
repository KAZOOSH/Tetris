/*
 *  OSCServer.cpp
 *  reddo_power_box
 *
 *  Created by Brian Eschrich on 27.08.15
 *  Copyright 2015 reddo UG. All rights reserved.
 *
 */

#include "OSCServer.h"

namespace ofxModule {
    
    
OSCServer::OSCServer() {
    oscServer.setup(12345);
    //cout << senders.size() << endl;
    ofAddListener(ofxOscEvent::packetIn, this, &OSCServer::onPacketIn);
}

/**
 * sends OSC message to specific port and ip
 */
void OSCServer::sendMessage(ofxOscMessage message, int port, string ip) {
    getSender(port, ip)->sendMessage(message);
}

/**
 * triggered when OSC message arrives
 * automatically answers /ping with /pong and int value 0
 */
void OSCServer::onPacketIn(ofxOscMessage & message) {
    if (message.getAddress() == "/ping") {
        ofxOscMessage m;
        m.setAddress("/pong");
        m.addIntArg(1);
        sendMessage(m);
    }
    else
    {
        ofNotifyEvent(oscEvent, message);
    }
	
}

ofxOscSender* OSCServer::getSender(int port, string ip){
    if (senders.empty()) {
        auto sender = createSender(port, ip);
        senders.insert(sender);
        return sender.second;
    }
    else if(senders.find(make_pair(ip, port)) == senders.end())
    {
        auto sender = createSender(port, ip);
        senders.insert(sender);
        return sender.second;
    }
    else
    {
        return senders.find(make_pair(ip, port))->second;
    }
}

pair< pair<string,int>, ofxOscSender*> OSCServer::createSender(int port, string ip)
{
    pair<string,int> key = make_pair(ip, port);
    ofxOscSender* value = new ofxOscSender();
    value->setup(ip, port);
    cout << "new sender created" <<endl;
    return make_pair(key, value);
}

}