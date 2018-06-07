/*
 *  ParameterParser.h
 *  reddo_power_box
 *
 *  Created by Brian Eschrich on 11.08.15
 *  Copyright 2015 reddo UG. All rights reserved.
 *
 */

#ifndef _ParameterParser
#define _ParameterParser

#include "ofMain.h"


namespace ofxModule {
    
/**
 *  @brief currently unused
 */
class ParameterParser {
	
  public:
	
public:
    static ParameterParser* get();
    static map<string, string> parseParameterString(string parameter);
    
   
    
protected:
    ParameterParser();
    ~ParameterParser(){
    };
    
private:
    static ParameterParser* instanz;
	
};
    
}

#endif
