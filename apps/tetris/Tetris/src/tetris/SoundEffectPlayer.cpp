#include "SoundEffectPlayer.h"



SoundEffectPlayer::SoundEffectPlayer()
{
	ofJson soundJson;
	ofFile fileParams("_Tetris/sounds.json");
	if (fileParams.exists()) {
		fileParams >> soundJson;
	} else {
		ofLogError(" _Tetris/sounds.json does not exist");
	}
	
	sounds.push_back(map<string, vector<ofSoundPlayer>>());
	sounds.push_back(map<string, vector<ofSoundPlayer>>());
	
	int p = 0;
	for (auto& person : sounds) {
		for (auto& s : soundJson) {
			vector<ofSoundPlayer> player;
			for (auto& track : s["sounds"]) {
				player.push_back(ofSoundPlayer());
				player.back().load("sound/effekte/" + track.get<string>());
				player.back().setMultiPlay(true);
				player.back().setPan(p == 0 ? -1.0 : 1.0);
			}
			sounds[p].insert(pair<string, vector<ofSoundPlayer>>(s["name"], player));
		}
		++p;
	}
	
}


SoundEffectPlayer::~SoundEffectPlayer()
{
}

void SoundEffectPlayer::play(string sound, int player)
{
	player -= 1;
	if (sounds[player].find(sound) != sounds[player].end()) {
		int nSample = ofRandom(sounds[player][sound].size());
		sounds[player][sound][nSample].play();
	}
}
