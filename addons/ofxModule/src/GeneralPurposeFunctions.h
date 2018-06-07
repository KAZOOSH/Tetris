/*
 *  ParameterParser.h
 *  reddo_power_box
 *
 *  Created by Brian Eschrich on 11.08.15
 *  Copyright 2015 reddo UG. All rights reserved.
 *
 */

#ifndef _GeneralPurposeFunctions
#define _GeneralPurposeFunctions

#include "ofMain.h"

/**
 *  @brief currently unused
 */

namespace ofxModule {

class GeneralPurposeFunctions {
	
  public:
	
public:
    static GeneralPurposeFunctions* get();
    static int IsoToUnixTimeStampInt(string parameter);
	static string IsoToUnixTimeStampString(string parameter);
    static string UnixToIsoTimeStamp(int parameter);
	static string UnixToIsoTimeStamp(string parameter);

protected:
    GeneralPurposeFunctions();
    ~GeneralPurposeFunctions(){
    };
    
private:
    static GeneralPurposeFunctions* instanz;
	
};
    
}

#endif
