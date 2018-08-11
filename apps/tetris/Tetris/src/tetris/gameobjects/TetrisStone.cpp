#include "TetrisStone.h"


TetrisStone::TetrisStone(string name):GameObject(name)
{
    createStones();
}

TetrisStone::~TetrisStone()
{
}

void TetrisStone::createStones(){
    string stone_L = "0,0; 1,0;1,2;2,2;2,3;0,3";
    string stone_Z = "0,0;2,0;2,1;3,1;3,2;1,2;1,1;0,1";
    string stone_I = "0,0;1,0;1,3;0,3";
    string stone_O = "0,0;2,0;2,2;0,2";
    stones.push_back(stone_L);
    stones.push_back(stone_Z);
    stones.push_back(stone_I);
    stones.push_back(stone_O);
}

void TetrisStone::createBody(b2World* world){
    //create the physics object and add it to the physics world
    auto body = shared_ptr<ofxBox2dPolygon>(new ofxBox2dPolygon);
    body->addVertices(getVertecies());
    body->setPhysics(0.1, 0.1, 1.0);
    body->triangulatePoly();
    body->create(world);
    addBody(body);
    
    //create and add the renderer
    auto renderer = shared_ptr<PolygonRenderer>(new PolygonRenderer(body));
    addRenderer(renderer);
    
}

vector <ofDefaultVertexType> TetrisStone::getVertecies()
{
    vector <ofDefaultVertexType> pts;
    
    string randomStone = stones[ofRandom(stones.size())];
    vector<string> pairs = ofSplitString(randomStone, ";");
    for(int i=0; i < pairs.size(); i++){
        vector<string> values = ofSplitString(pairs[i], ",");
        pts.push_back(ofDefaultVertexType(ofToInt(values[0]) * scale + offsetX, ofToInt(values[1]) * scale, 0));
    }
    return pts;
}

