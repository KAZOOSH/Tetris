/*
 *  IModuleRunnable.h
 *  example_server_sharedcanvas
 *
 *  Created by Brian Eschrich on 29.07.15
 *  Copyright 2015 reddo UG. All rights reserved.
 *
 */

#ifndef _IModuleRunnable
#define _IModuleRunnable

#include "OSCServer.h"
#include "DataLogger.h"
#include "ModuleEvent.h"

/**
 * @brief interface for modules
 * every part of the app, except the core is defined as a module
 * modules can be loaded through xml and run in a seperate thread
 */

namespace ofxModule {
    
    /*
     struct ModuleLog{
     string message;
     ofLogLevel logLevel;
     };*/
    
    class ModuleRunnable : public ofThread, public DataLogger{
        
    public:
        /*
         * actual function that proceedes function of subclasses
         */
        virtual void update() = 0;
        virtual void stopModule() = 0;
        
        ModuleRunnable(string moduleClass, string moduleName, int fps = 60);
        ModuleRunnable(string moduleClass, string moduleName, bool isStartThread, int fps = 60);
        ~ModuleRunnable(){saveSettings(); stopThread();};

        void addOSCServer(OSCServer* oscServer);
        
		bool getSingleThreaded();
		void setSingleThreaded();
        void threadedFunction();
        void registerModuleEvent(ModuleRunnable* module);
        string getModuleClass();
        string getModuleName();
        
        
        
        bool getIsIdle();
        void setIsIdle(bool isIdle);
        
        //--- parameter functions --- //
        template<class PARAMETERVALUE>
        void setParameter(string parameterName, PARAMETERVALUE value);
        void setParameterMin(string parameterName, int value);
        void setParameterMin(string parameterName, float value);
        void setParameterMax(string parameterName, int value);
        void setParameterMax(string parameterName, float value);
        
        
        
        ofParameterGroup getParameters();
        ofJson getParametersJson();
        ofJson getParameterJson(int pos);
        ofJson getParameterJson(string name);
        
        virtual void loadSettings();
        virtual void saveSettings();
        
        //ofEvent<ofJson> moduleEvent;
        ofEvent<ModuleEvent> moduleEvent;
       // void newModuleEvent(ofJson& eventText);
        void onModuleEvent(ModuleEvent& e);
        void setParameterJson(ofJson parameters, string valueType);
        string getParameterTypeJson(ofJson parameters);
        
		//called when all modules loaded
		virtual void onAllModulesLoaded() {};

    protected:
        int fps;
        /*
         * function for sublasses to react on input
         */
        //virtual void proceedModuleEvent(ofJson& eventText){};
        virtual void proceedModuleEvent(ModuleEvent& e){};

		
        
        void initModule(string moduleClass, string moduleName, int fps);
        string moduleClass;
        string moduleName;
        
        ofParameterGroup getParameterGroup(string parameterName);
        string getParameterNameFromGroup(string parameterName);
        
        //void notifyEvent(ofJson message);
        void notifyEvent(ofJson message);
        void notifyEvent(ofTexture* texture, ofJson message = ofJson({{"function","texture"}}));
        void notifyEvent(ofImage* image, ofJson message = ofJson({{"function","image"}}));
        void sendOSCMessage(ofxOscMessage & message);
        
        ofParameterGroup parameters;
        
        bool isIdle;
		bool isSingleThreaded;

        bool hasOSCServer;
        OSCServer* oscServer;
        
        void logVerbose(string function, string message);
        void logNotice(string function, string message);
        void logWarning(string function, string message);
        void logError(string function, string message);
        void logFatalError(string function, string message);
        
        
        
    private:
        //void addToModuleLog(string function, string message, ofLogLevel level);
        //deque<ModuleLog> log;
        
        ofXml settings;
        string settingsPath;
    };
    
}
#endif
