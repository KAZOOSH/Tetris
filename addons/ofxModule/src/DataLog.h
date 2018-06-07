/*
 *  Log.h
 *  reddo_power_box
 *
 *  Created by Brian Eschrich on 19.08.15
 *  Copyright 2015 reddo UG. All rights reserved.
 *
 */

#ifndef _DataLog
#define _DataLog

//#include <iostream.h>
#include "ofMain.h"

namespace ofxModule {
    
enum LogMessageType {
    STRING,
    JSON,
    CSV
};

/**
 * @brief Format for DataLogging
 * not final
 * Format for DataLogging
 */
class DataLog {
	
  public:
	
	DataLog();
    
    LogMessageType messageType;
    string message;
    string logPath;
    string logFile;
    /**
    // add the message to logfile or delete the file before
    **/
    bool isAddToFile;
	
	
};
    
}

#endif
