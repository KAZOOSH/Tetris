/*
 *  IModuleRunnable.cpp
 *  reddo_power_box
 *
 *  Created by Brian Eschrich on 21.08.15
 *  Copyright 2015 reddo UG. All rights reserved.
 *
 */

#include "ModuleRunnable.h"

namespace ofxModule {
    
    
    ModuleRunnable::ModuleRunnable(string moduleClass_, string moduleName_, int fps_){
        initModule(moduleClass_, moduleName_, fps_);
        startThread();
    }
    
    ModuleRunnable::ModuleRunnable(string moduleClass_, string moduleName_, bool isStartThread, int fps_){
        initModule(moduleClass_, moduleName_, fps_);
        if(isStartThread) startThread();
    }
    
    void ModuleRunnable::initModule(string moduleClass_, string moduleName_, int fps_){
        fps = fps_;
        moduleClass = moduleClass_;
        moduleName = moduleName_;
        settingsPath = "_" + moduleName_ + "/settings.xml";
        parameters.setName("parameters");
        isIdle = false;
        hasOSCServer = false;
		isSingleThreaded = false;
    }
    
	bool ModuleRunnable::getSingleThreaded()
	{
		return isSingleThreaded;
	}

	void ModuleRunnable::setSingleThreaded()
	{
		isSingleThreaded = true;
	}

	/**
     * function that runs in the thread
     * executes proceedInput for subclasses
     */
    void ModuleRunnable::threadedFunction(){
        while(isThreadRunning())
        {
            sleep(1000/fps);
            if(lock())
            {
                update();
                unlock();
            }
            else
            {
                ofLogWarning("threadedFunction()") << "Unable to lock mutex.";
                sleep(1000);
            }
        }
        
    }
    
    /**
     * idle/unidle module (in idle module is not allowed to send messages)
     *      "setIdle":"true,false"
     *  sends message to subclass for proceeding
     */
    /*void ModuleRunnable::newModuleEvent(ofJson &eventText){
        string idT = "";
        if (!eventText["id"].is_null()) {
            idT = eventText["id"].get<string>();
        }
        
        string functionName = "";
        if (!eventText["function"].is_null()) {
            functionName = eventText["function"].get<string>();
        }
        
        if (idT == "" || idT == moduleName) {
            if (functionName == "setIdle"){
                if(eventText["value"].get<string>() == "true") setIsIdle(true);
                else setIsIdle(false);
            }
            else if (functionName == "setParameter"){
                setParameterJson(eventText, getParameterTypeJson(eventText));
            }
        proceedModuleEvent(eventText);
        }
    }*/
    
    /**
     * idle/unidle module (in idle module is not allowed to send messages)
     *      "setIdle":"true,false"
     *  sends message to subclass for proceeding
     */
    void ModuleRunnable::onModuleEvent(ModuleEvent &e){
        string idT = "";
		string iClass = "";
        if (!e.message["id"].is_null()) {
            idT = e.message["id"].get<string>();
        }

		if (!e.message["class"].is_null()) {
			iClass = e.message["class"].get<string>();
		}
        
        string functionName = "";
        if (!e.message["function"].is_null()) {
            functionName = e.message["function"].get<string>();
        }

        if ((idT == "" && iClass == "") || idT == moduleName || iClass == moduleClass) {
            if (functionName == "setIdle"){
                if(e.message["value"].get<string>() == "true") setIsIdle(true);
                else setIsIdle(false);
            }
            else if (functionName == "setParameter"){
                setParameterJson(e.message, getParameterTypeJson(e.message));
            }
            proceedModuleEvent(e);
        }
    }
    
    
    
    string ModuleRunnable::getParameterTypeJson(ofJson parameters){
        return parameters["type"];
    }
    
    /**
     * register events between modules
     */
    void ModuleRunnable::registerModuleEvent(ModuleRunnable* module){
        if(lock())
        {
           // ofAddListener(module->moduleEvent, this, &ModuleRunnable::newModuleEvent);
            
            ofAddListener(module->moduleEvent, this, &ModuleRunnable::onModuleEvent);
            unlock();
        }
        else
        {
            ofLogWarning("ModuleRunnable::newModuleEvent()") << "Unable to lock mutex.";
            sleep(1000);
        }
    }
    
    string ModuleRunnable::getModuleClass(){
        return moduleClass;
    }
    
    string ModuleRunnable::getModuleName(){
        return moduleName;
    }
    
    void ModuleRunnable::addOSCServer(OSCServer* oscServer_){
        oscServer = oscServer_;
        hasOSCServer = true;
    }
    
    void ModuleRunnable::sendOSCMessage(ofxOscMessage & message){
        if (hasOSCServer) {
            oscServer->sendMessage(message);
        }
        else
        {
            ofLogError("ModuleRunnable::sendOSCMessage","error sending OSC message - no OSC server available");
        }
    }
    
    /**
     * for event notification use this instead of standard ofNotify
     */
    /*void ModuleRunnable::notifyEvent(ofJson message){
        if(!isIdle) ofNotifyEvent(moduleEvent,message);
    }*/
    
    void ModuleRunnable::notifyEvent(ofTexture* texture, ofJson message){
        if(!isIdle) {
            ModuleEvent e = ModuleEvent(moduleClass,moduleName,message);
            e.texture = texture;
            e.type = ModuleEvent::TYPE_TEXTURE;
            ofNotifyEvent(moduleEvent,e);
        }
    }
    
    void ModuleRunnable::notifyEvent(ofImage* image, ofJson message){
        if(!isIdle) {
            ModuleEvent e = ModuleEvent(moduleClass,moduleName,message);
            e.image = image;
            e.type = ModuleEvent::TYPE_IMAGE;
            ofNotifyEvent(moduleEvent,e);
        }
    }
    
    void ModuleRunnable::notifyEvent(ofJson message){
        if(!isIdle) {
            ModuleEvent e = ModuleEvent(moduleClass,moduleName,message);
            ofNotifyEvent(moduleEvent,e);
        }
    }
    
    bool ModuleRunnable::getIsIdle(){
        return isIdle;
    }
    void ModuleRunnable::setIsIdle(bool isIdle_){
        isIdle = isIdle_;
    }
    
    
    // ----- Parameter functions -------- //
    template<class PARAMETERVALUE>
    void ModuleRunnable::setParameter(string parameterName, PARAMETERVALUE value){
    }
    
    template<> void ModuleRunnable::setParameter<float>(string parameterName, float value){
        string name = getParameterNameFromGroup(parameterName);
        ofParameterGroup g = getParameterGroup(parameterName);
        g.getFloat(name).set(value);
    }
    template<> void ModuleRunnable::setParameter<int>(string parameterName, int value){
        string name = getParameterNameFromGroup(parameterName);
        ofParameterGroup g = getParameterGroup(parameterName);
        g.getInt(name).set(value);
    }
    template<> void ModuleRunnable::setParameter<string>(string parameterName, string value){
        string name = getParameterNameFromGroup(parameterName);
        ofParameterGroup g = getParameterGroup(parameterName);
        g.getString(name).set(value);
    }
    template<> void ModuleRunnable::setParameter<bool>(string parameterName, bool value){
        string name = getParameterNameFromGroup(parameterName);
        ofParameterGroup g = getParameterGroup(parameterName);
        g.getBool(name).set(value);
    }
    template<> void ModuleRunnable::setParameter<ofVec2f>(string parameterName, ofVec2f value){
        string name = getParameterNameFromGroup(parameterName);
        ofParameterGroup g = getParameterGroup(parameterName);
        g.getVec2f(name).set(value);
    }
    template<> void ModuleRunnable::setParameter<ofVec3f>(string parameterName, ofVec3f value){
        string name = getParameterNameFromGroup(parameterName);
        ofParameterGroup g = getParameterGroup(parameterName);
        g.getVec3f(name).set(value);
    }
    template<> void ModuleRunnable::setParameter<ofVec4f>(string parameterName, ofVec4f value){
        string name = getParameterNameFromGroup(parameterName);
        ofParameterGroup g = getParameterGroup(parameterName);
        g.getVec4f(name).set(value);
    }
    
    ofParameterGroup ModuleRunnable::getParameterGroup(string parameterName){
        ofStringReplace(parameterName, "\"", "");
        vector<string> groups = ofSplitString(parameterName, ":");
        ofParameterGroup group = parameters;
        if (groups.size()>1) {
            for (int i=0; i<groups.size()-1; ++i) {
                group = group.getGroup(groups[i]);
            }
        }
        return group;
    }
    
    string ModuleRunnable::getParameterNameFromGroup(string parameterName){
        ofStringReplace(parameterName, "\"", "");
        ofStringReplace(parameterName, "\n", "");
        vector<string> groups = ofSplitString(parameterName, ":");
        return groups.back();
    }
    
    void ModuleRunnable::setParameterMin(string parameterName, float value){
        int pos = parameters.getPosition(parameterName);
        string type = parameters.getType(pos);
        if (type == "11ofParameterIiE") {//integer
            setParameterMin(parameterName, value);
        }else if (type == "11ofParameterIfE") {//float
            parameters.getFloat(pos).setMin(value);
        }else{
            ofLogNotice("ModuleRunnable::setParameterMin","datatype not valid");
        }
    }
    
    void ModuleRunnable::setParameterMin(string parameterName, int value){
        parameters.getInt(parameterName).setMin(value);
    }
    
    void ModuleRunnable::setParameterMax(string parameterName, float value){
        int pos = parameters.getPosition(parameterName);
        string type = parameters.getType(pos);
        if (type == "11ofParameterIiE") {//integer
            setParameterMax(parameterName, value);
        }else if (type == "11ofParameterIfE") {//float
            parameters.getFloat(pos).setMax(value);
        }else{
            ofLogNotice("ModuleRunnable::setParameterMin","datatype not valid");
        }
    }
    
    void ModuleRunnable::setParameterMax(string parameterName, int value){
        parameters.getInt(parameterName).setMax(value);
    }
    
    ofParameterGroup ModuleRunnable::getParameters(){
        return parameters;
    }
    
    ofJson ModuleRunnable::getParametersJson(){
        ofJson paramlist;
        for (int i=0; i<parameters.size(); ++i) {
            paramlist["parameters"].push_back(getParameterJson(i));
        }
        return paramlist;
    }
    
    ofJson ModuleRunnable::getParameterJson(string name){
        return getParameterJson(parameters.getPosition(name));
    }
    
    ofJson ModuleRunnable::getParameterJson(int pos){
        ofJson msg;
        
        string type = parameters.getType(pos);
        if (type == "11ofParameterIbE") {//bool
            type = "bool";
            msg["value"] = parameters.getBool(pos).toString();
        }else if (type == "11ofParameterIiE") {//integer
            type = "int";
            msg["value"] = parameters.getInt(pos).toString();
            msg["max"] =  parameters.getInt(pos).getMax();
            msg["min"] = parameters.getInt(pos).getMin();
        }else if (type == "11ofParameterIfE") {//float
            type = "float";
            msg["value"] = parameters.getFloat(pos).toString();
            msg["max"] =  parameters.getFloat(pos).getMax();
            msg["min"] =  parameters.getFloat(pos).getMin();
        }else if (type == "11ofParameterISsE") {//string
            type = "string";
            msg["value"] = parameters.getString(pos);
        }else if (type == "11ofParameterI7ofVec2fE") {//vec2
            type = "vec2";
            msg["value"]["x"] = parameters.getVec2f(pos)->x;
            msg["value"]["y"] = parameters.getVec2f(pos)->y;
        }else if (type == "11ofParameterI7ofVec3fE") {//vec3
            type = "vec3";
            msg["value"]["x"] = parameters.getVec3f(pos)->x;
            msg["value"]["y"] = parameters.getVec3f(pos)->y;
            msg["value"]["z"] = parameters.getVec3f(pos)->z;
        }else if (type == "11ofParameterI7ofVec4fE") {//vec4
            type = "vec4";
            msg["value"]["x"] = parameters.getVec4f(pos)->x;
            msg["value"]["y"] = parameters.getVec4f(pos)->y;
            msg["value"]["z"] = parameters.getVec4f(pos)->z;
            msg["value"]["w"] = parameters.getVec4f(pos)->w;
        }
        msg["type"] = type;
        
        msg["name"] = parameters.getName(pos);
        return msg;
    }
    
    void ModuleRunnable::logVerbose(string function, string message){
        DataLogger::logVerbose(moduleName, function, message);
    }
    
    void ModuleRunnable::logNotice(string function, string message){
        DataLogger::logNotice(moduleName, function, message);
    }
    
    void ModuleRunnable::logWarning(string function, string message){
        DataLogger::logWarning(moduleName, function, message);
    }
    
    void ModuleRunnable::logError(string function, string message){
        DataLogger::logError(moduleName, function, message);
    }
    
    void ModuleRunnable::logFatalError(string function, string message){
        DataLogger::logFatalError(moduleName, function, message);
    }
    
    void ModuleRunnable::loadSettings(){
		if (settings.load(settingsPath)) {
			ofDeserialize(settings, parameters);
			ofLogNotice(moduleName + " : settings successfully loaded");
		}
		else {
			ofLogNotice(moduleName + " : loading settings failed");
		}
	
    }
    
    void ModuleRunnable::saveSettings(){
        //settings.serialize(parameters);
		parameters.setSerializable(true);
		ofSerialize(settings, parameters);
		settings.save(settingsPath);
		
    }
    /*
    void ModuleRunnable::addToModuleLog(string function, string message, ofLogLevel level){
        ModuleLog logEntry;
        logEntry.message = moduleClass + "::" + function + " - " + message;
        logEntry.logLevel = level;
        log.push_front(logEntry);
        if (log.size()>128) {
            log.pop_back();
        }
    }*/
    
    void ModuleRunnable::setParameterJson(ofJson parameters, string valueType){
        
        string valueName = parameters["name"];
        //cout << parameters.getRawString() <<endl;
        if (valueType == "int") {
            setParameter(valueName, parameters["value"].get<int>());
        }else if (valueType == "float") {
            setParameter(valueName, parameters["value"].get<float>());
        }else if (valueType == "string") {
            setParameter(valueName, parameters["value"].get<string>());
        }else if (valueType == "bool") {
            setParameter(valueName, parameters["value"].get<bool>());
        }else if (valueType == "vec2f") {
            setParameter(valueName,
                         ofVec2f(parameters["value"]["x"].get<float>(),parameters["value"]["y"].get<float>()));
        }else if (valueType == "vec3f") {
            setParameter(valueName,
                         ofVec3f(parameters["value"]["x"].get<float>(),
                                 parameters["value"]["y"].get<float>(),
                                 parameters["value"]["z"].get<float>()));
        }else if (valueType == "vec4f") {
            setParameter(valueName,
                         ofVec4f(parameters["value"]["x"].get<float>(),
                                 parameters["value"]["y"].get<float>(),
                                 parameters["value"]["z"].get<float>(),
                                 parameters["value"]["w"].get<float>()));
        }
        
        
    }
    
}
