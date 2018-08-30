#pragma once
#include "ofMain.h"
#include "SoundEffectPlayer.h"

class GameParameters
{
public:
    GameParameters();
    ~GameParameters();
    
    void getRandomColorScheme(ofColor& base, ofColor& highlight);

	//util functions

    //settings
    ofJson params;
    ofJson colorSchemes;
	ofJson effects;
    
    //game params
    float winningHeight = 0.9;

	ofJson getEffect(string effect);

	SoundEffectPlayer soundPlayer;

private:
	//GameObjectContainer objects;

	vector<string> effectList;
    
};

