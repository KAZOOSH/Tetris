#pragma once
#include "ofMain.h"
//#include "CreationRules.h"

class CreationRules;

class GameParameters
{
public:
    GameParameters();
    ~GameParameters();
    
    ofEvent<ofJson> gameEvent;
    ofEvent<ofJson> controlEvent;
    
    void notifyGameEvent(ofJson eventText);
    void notifyControlEvent(ofJson eventText);
    
    void getRandomColorScheme(ofColor& base, ofColor& highlight);
    
    //enum effects{ base, heavy, bouncy };
    

	void setRandomNextEffect();
	void setNextEffect(string name);

	//util functions

    //settings
    ofJson params;
    ofJson colorSchemes;
	ofJson effects;
    
    //game params
    float winningHeight = 0.9;
    vector<string> nextCreationRule;

	string gamestate = "idle";

	ofJson getEffect(string effect);

private:
	vector<string> nextEffectList;
	vector<string> effectList;
    
};

