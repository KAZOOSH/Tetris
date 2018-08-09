#include "GameParameters.h"



GameParameters::GameParameters()
{
	ofFile file("_Tetris/params.json");
	if (file.exists()) {
		file >> params;
	} else {
		ofLogError(" _Tetris/params.json does not exist");
	}
}


GameParameters::~GameParameters()
{
}
