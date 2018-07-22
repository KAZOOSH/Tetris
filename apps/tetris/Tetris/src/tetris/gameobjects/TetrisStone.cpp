#include "TetrisStone.h"


TetrisStone::TetrisStone(string name):GameObject(name)
{
    
    
}

TetrisStone::~TetrisStone()
{
}

void TetrisStone::createBody(shared_ptr<GameObjectContainer> objects){
    //create the physics object and add it to the physics world
    auto body = shared_ptr<ofxBox2dPolygon>(new ofxBox2dPolygon);
    body->addVertices(getVertecies());
    body->setPhysics(1.0, 0.3, 0.3);
    body->triangulatePoly();
    body->create(objects->physics.getWorld());
    addBody(body);
    
    //create and add the renderer
    auto renderer = shared_ptr<PolygonRenderer>(new PolygonRenderer(body));
    addRenderer(renderer);
    
}

vector <ofDefaultVertexType> TetrisStone::getVertecies()
{
    vector <ofDefaultVertexType> pts;
    vector<string> pairs = ofSplitString(stone_L, ";");
    for(int i=0; i < pairs.size(); i++){
        vector<string> values = ofSplitString(pairs[i], ",");
        pts.push_back(ofDefaultVertexType(ofToInt(values[0]) * scale + offsetX, ofToInt(values[1]) * scale, 0));
    }
    return pts;
//    vector <ofDefaultVertexType> pts;
//    pts.push_back(ofDefaultVertexType(0, 0, 0));
//    pts.push_back(ofDefaultVertexType(100, 0, 0));
//    pts.push_back(ofDefaultVertexType(100, 100, 0));
//    pts.push_back(ofDefaultVertexType(0, 100, 0));
//    return pts;
}

