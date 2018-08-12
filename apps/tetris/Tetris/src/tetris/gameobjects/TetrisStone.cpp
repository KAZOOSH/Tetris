#include "TetrisStone.h"


TetrisStone::TetrisStone(string name):GameObject(name)
{
    createStoneVertecies();
    body = shared_ptr<ofxBox2dPolygon>(new ofxBox2dPolygon);
    body->addVertices(getVertecies());
    body->setPhysics(5, 0, 1);
    body->triangulatePoly();
}

TetrisStone::~TetrisStone()
{
}

void TetrisStone::render() {
    if(isBouncy){
        ofSetColor(255, 0, 0);
    }
    if(isHeavy){
        ofSetColor(0, 255, 0);
    }
    for (auto& r : renderer) {
        r->render();
    }
    ofSetColor(255, 255, 255);
};


void TetrisStone::makeHeavy() {
    //this.b2body.GetFixtureList().SetFriction(friction);
    isHeavy = true;
    body->body->GetFixtureList()->SetDensity(2500.0f);
    //body->body->
    //body->setPhysics(500, 0, 1);
}

void TetrisStone::makeBouncy() {
    //body->setPhysics(5, 1, 1);
    isBouncy = true;
    body->body->GetFixtureList()->SetRestitution(1.0f);
}

void TetrisStone::setPosition(ofVec2f position){
    body->setPosition(position);
}

void TetrisStone::setPlayer(int player){
    playerId = player;
}

int TetrisStone::getPlayerId(){
    return playerId;
}

void TetrisStone::rotateRight() {
    body->addImpulseForce(body->getB2DPosition()+ofVec2f(10,0), ofVec2f(0,0.1f));
}

void TetrisStone::rotateLeft() {
     body->addImpulseForce(body->getB2DPosition()-ofVec2f(10,0), ofVec2f(0,0.1f));
    //body->setRotation(body->getRotation() - 90);
}

void TetrisStone::createStoneVertecies(){
    string stone_L = "0,0; 1,0;1,2;2,2;2,3;0,3";
    string stone_Z = "0,0;2,0;2,1;3,1;3,2;1,2;1,1;0,1";
    string stone_I = "0,0;1,0;1,3;0,3";
    string stone_O = "0,0;2,0;2,2;0,2";
    stones.push_back(stone_L);
    stones.push_back(stone_Z);
    stones.push_back(stone_I);
    stones.push_back(stone_O);
}

void TetrisStone::addToWorld(b2World* world){
    //create the physics object and add it to the physics world
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

