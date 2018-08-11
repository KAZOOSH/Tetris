#pragma once
#include "PolygonRenderer.h"
#include "ofxBox2d.h"
#include "GameObject.h"

class TetrisStone : public GameObject
{
public:
    TetrisStone(string name);
    ~TetrisStone();
    void createBody(b2World* world);
    
private:
    vector <ofDefaultVertexType> getVertecies();
    void createStones();
    int scale= 20;
    int offsetX = 200;

    vector<string> stones;

};

