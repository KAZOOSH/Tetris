/*
 *
 */

#include "Tetris.h"

using namespace ofxModule;

Tetris::Tetris(string moduleName):ModuleDrawable("Tetris",moduleName,false){
    setSingleThreaded();
	loadSettings();



}
//------------------------------------------------------------------
void Tetris::stopModule() {


}


//------------------------------------------------------------------
void Tetris::update() {

}


//------------------------------------------------------------------
void Tetris::draw() {
	ofSetColor(255);
	ofDrawBitmapString(" I am the Tetris game", 300,300);
}

