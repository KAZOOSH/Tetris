#pragma once
#include "ofMain.h"
#include "SoundEffectPlayer.h"

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

	SoundEffectPlayer soundPlayer;

private:
	vector<string> nextEffectList;
	vector<string> effectList;
    
};

