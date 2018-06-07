/*
 *  DataLogger.cpp
 *  reddo_power_box
 *
 *  Created by Brian Eschrich on 19.08.15
 *  Copyright 2015 reddo UG. All rights reserved.
 *
 */

#include "DataLogger.h"

/**
 * saves Datalog in File
 */

namespace ofxModule {
    
    DataLogger::DataLogger(){
        maxEntries = 50;
    }
    
    bool DataLogger::logData(DataLog data){
        ofBuffer buffer = openFile(data.logFile, data.logPath);
        
        if (data.isAddToFile || buffer.size() > 0) {
            
            
        }else{
            buffer.clear();
            buffer.append("TYPE" + ofToString(data.messageType));
        }
        
        buffer.append("%§%"); // escape sequence
        buffer.append(data.message);
        ofBufferToFile(data.logPath+"/"+data.logFile, buffer);
        return true;
    }
    
    /**
     * logs a simple json (only one hierarchy layer)
     */
    bool DataLogger::logToCSV(string message, string logFile, string logPath, bool isAppendMessage, LogMessageType type){
        /* todo
        ofBuffer buffer = openFile(logFile, logPath);
        
        //parse string as json
        ofJson json = ofJson(message);
        
        
        //create new header
        if (buffer.size() == 0 || !isAppendMessage) {
            string header = "";
            for (int i=0; i<json.size(); ++i) {
                header += json.getMemberNames()[i];
                if (i<json.size()-1) {
                    header += ";";
                }
                else
                {
                    header += "\n";
                }
            }
            buffer.append(header);
        }
        
        //add content
        string content = "";
        for (int i=0; i<json.size(); ++i) {
            string value = json[json.getMemberNames()[i]].toStyledString();
            ofStringReplace(value, ";","," );
            ofStringReplace(value, "\n","  ");
            content += value;
            if (i<json.size()-1) {
                content += ";";
            }
            else
            {
                content += "\n";
            }
        }
        buffer.append(content);
        */
        //return ofBufferToFile(logPath+"/"+logFile, buffer);
        return false;
    }
    
    ofBuffer DataLogger::openFile(string file, string directory){
        ofDirectory dir;
        if(!dir.doesDirectoryExist(directory))
        {
            dir.createDirectory(directory);
        }
        return ofBufferFromFile(directory+"/"+file);
    }
    
    void DataLogger::addEntry(string module, string function, string message, ofLogLevel logLevel){
        LogEntry l;
        l.timestamp = ofGetElapsedTimeMillis();
        l.date = ofToString(ofGetYear()) + "-" + ofToString(ofGetMonth()) + "-" + ofToString(ofGetDay()) + "_" + ofToString(ofGetHours()) + ":" + ofToString(ofGetMinutes()) + ":" + ofToString(ofGetSeconds());
        l.module = module;
        l.function = function;
        l.message = message;
        l.logLevel = logLevel;
        logEntries.push_front(l);
        
        if (logEntries.size() > maxEntries) {
            logEntries.pop_back();
        }
    }
    
    void DataLogger::logVerbose(string module,string function, string message){
        addEntry(module, function, message, OF_LOG_VERBOSE);
        ofLogVerbose(module + ":" + function, message );
    }
    
    void DataLogger::logNotice(string module,string function, string message){
        addEntry(module, function, message, OF_LOG_NOTICE);
        ofLogNotice(module + ":" + function, message );
    }
    
    void DataLogger::logWarning(string module,string function, string message){
        addEntry(module, function, message, OF_LOG_WARNING);
        ofLogWarning(module + ":" + function, message );
    }
    
    void DataLogger::logError(string module,string function, string message){
        addEntry(module, function, message, OF_LOG_ERROR);
        ofLogError(module + ":" + function, message );
    }
    
    void DataLogger::logFatalError(string module,string function, string message){
        addEntry(module, function, message, OF_LOG_FATAL_ERROR);
        ofLogFatalError(module + ":" + function, message );
    }
    
    vector<LogEntry> DataLogger::getEntries(ofLogLevel logLevel, int maxLogs){
        vector<LogEntry> out;
        for(auto log : logEntries){
            if (logLevel >= log.logLevel && maxLogs > out.size()) {
                out.push_back(log);
            }
        }
        return out;
    }
    
    ofJson DataLogger::getEntriesJson(int maxLogs){
       /* vector<LogEntry> logs = getEntries(ofGetLogLevel(), maxLogs);
        vector<ofJson> msg;
        for (auto log:logs) {
            ofJson m = new ofJson({
                {"timestamp", log.timestamp},
                {"date", log.date},
                {"module", log.module},
                {"function", log.function},
                {"message", log.message}});
            msg.push_back(m);
        }*/
        ofJson out;
        //out["log"] = msg;
        out["function"] = "getLog";
        return out;
    }
    
    string DataLogger::getEntriesString(int maxLogs){
        return getEntriesJson(maxLogs).dump();
    }
    
    string DataLogger::getLog(int maxLogs){
       return getEntriesString(maxLogs);
    }
    
}
