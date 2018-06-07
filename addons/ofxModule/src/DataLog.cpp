/*
 *  Log.cpp
 *  reddo_power_box
 *
 *  Created by Brian Eschrich on 19.08.15
 *  Copyright 2015 reddo UG. All rights reserved.
 *
 */

#include "DataLog.h"

namespace ofxModule {
//------------------------------------------------------------------
DataLog::DataLog() {
    messageType = STRING;
    message = "";
    logPath = "log";
    logFile = "";
    isAddToFile = true;
}
}