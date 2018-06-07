/*
 *  ParameterParser.cpp
 *  reddo_power_box
 *
 *  Created by Brian Eschrich on 11.08.15
 *  Copyright 2015 reddo UG. All rights reserved.
 *
 */

#include "GeneralPurposeFunctions.h"

namespace ofxModule {

GeneralPurposeFunctions::GeneralPurposeFunctions(){};

GeneralPurposeFunctions* GeneralPurposeFunctions::instanz = 0;

GeneralPurposeFunctions* GeneralPurposeFunctions::get()
{
    if ( instanz == 0)
    {
        instanz = new GeneralPurposeFunctions();
    }
    return instanz;
}

string GeneralPurposeFunctions::IsoToUnixTimeStampString(string parameter){
    return "text";
}

int GeneralPurposeFunctions::IsoToUnixTimeStampInt(string parameter){
    return 0;
}

string GeneralPurposeFunctions::UnixToIsoTimeStamp(string parameter){
    char newTime[300];
	int intTime = atoi(parameter.c_str());
	time_t rawTime = intTime;
	struct tm *timeinfo = localtime(&rawTime);
	strftime(newTime,300,"%y-%m-%dT%H:%M:%S+0000",timeinfo);
	std::string time = newTime;
	return newTime;
}

string GeneralPurposeFunctions::UnixToIsoTimeStamp(int parameter){
    return "text";
}

}