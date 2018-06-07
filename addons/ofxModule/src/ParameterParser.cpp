/*
 *  ParameterParser.cpp
 *  reddo_power_box
 *
 *  Created by Brian Eschrich on 11.08.15
 *  Copyright 2015 reddo UG. All rights reserved.
 *
 */

#include "ParameterParser.h"

namespace ofxModule {

ParameterParser::ParameterParser(){};

ParameterParser* ParameterParser::instanz = 0;

ParameterParser* ParameterParser::get()
{
    if ( instanz == 0)
    {
        instanz = new ParameterParser();
    }
    return instanz;
}

/**
 * Example: Input : "order1 = 3; fish = good;"
 * Output; <order1,3> <fish,good>
 */
map<string, string> ParameterParser::parseParameterString(string parameter){
    vector<string> commands = ofSplitString(parameter, ";", true,true);
    map<string,string> ret;
    for (int i=0; i<commands.size(); ++i) {
        vector<string> commandValue = ofSplitString(commands[i], "=",true,true);
        ret.insert(pair<string, string>(commandValue[0],commandValue[1]));
    }
    return ret;
    
}

}