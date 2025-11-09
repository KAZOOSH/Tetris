#pragma once
#include "ofMain.h"


class GameParameters
{
public:
    GameParameters();
    ~GameParameters();
    
    void getRandomColorScheme(ofColor& base, ofColor& highlight);

	//util functions

    //settings
    ofJson settings;
    ofJson colorSchemes;
	ofJson effects;

	ofJson getEffect(string effect);

   

private:

    
};

