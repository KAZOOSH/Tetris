/*
 *  DataLogger.h
 *  reddo_power_box
 *
 *  Created by Brian Eschrich on 19.08.15
 *  Copyright 2015 reddo UG. All rights reserved.
 *
 */

#ifndef _DataLogger
#define _DataLogger

#include "ofMain.h"
#include "DataLog.h"

namespace ofxModule {
    
    struct LogEntry{
        int timestamp;
        string date;
        string module;
        string function;
        string message;
        ofLogLevel logLevel;
    };
    
    /**
     * @brief contains static methods to log Data
     */
    class DataLogger {
        
    public:
        
        DataLogger();
        
        static bool logToCSV(string message, string logFile, string logPath="log", bool isAppendMessage = true, LogMessageType type = JSON);
        static bool logData(DataLog data);
        
        
        virtual string getLog(int maxLogs = 10);
        ofJson getEntriesJson(int maxLogs = 10);
        string getEntriesString(int maxLogs = 10);
        vector<LogEntry> getEntries(ofLogLevel logLevel, int maxLogs = 10);
        
    protected:
        void addEntry(string module, string function, string message, ofLogLevel logLevel);
        void logVerbose(string module,string function, string message);
        void logNotice(string module,string function, string message);
        void logWarning(string module,string function, string message);
        void logError(string module,string function, string message);
        void logFatalError(string module,string function, string message);
        
    private:
        static ofBuffer openFile(string file, string directory);
        
        std::deque<LogEntry> logEntries;
        int maxEntries;
    };
    
}

#endif
