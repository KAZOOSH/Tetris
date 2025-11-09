#pragma once
#include "ofMain.h"

class SoundEffectPlayer
{
public:
	SoundEffectPlayer();
	~SoundEffectPlayer();

	void play(string sound,int player);

private:
	vector<map<string, vector<ofSoundPlayer>>> sounds;

};

