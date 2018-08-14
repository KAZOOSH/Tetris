#pragma once
#include "PolygonRenderer.h"
#include "GameObjectContainer.h"
#include "ofxBox2d.h"
#include "GameObject.h"

class TetrisStone : public GameObject
{
public:
    TetrisStone(string name);
    ~TetrisStone();
    void createBody(shared_ptr<GameObjectContainer> objects);
    
private:
    vector <ofDefaultVertexType> getVertecies();
    int scale= 20;
    int offsetX = 200;
    string stone_L = "0,0; 1,0;1,3;2,3;2,4;0,4";
    string stone_Z = "100,100;200,100;200,200;100,200";
    string stone_I = "100,100;200,100;200,200;100,200";
};

