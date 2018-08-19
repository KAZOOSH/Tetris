#include "TetrisStone.h"


TetrisStone::TetrisStone(string name, GameParameters* params_):GameObject(name)
{
    //isTetrisStone= true;
    //collided = false;
    params = params_;
    createStoneVertecies();
    body = shared_ptr<ofxBox2dPolygon>(new ofxBox2dPolygon);
    
    float density = params->params["tetrisStone"]["density"].get<float>();
    
    vertecies = getRandomVertecies();
    body->addVertices(vertecies);
    body->setPhysics(density, 0, 1);
    body->triangulatePoly();

	//create and add the renderer
	auto renderer = shared_ptr<PolygonRenderer>(new PolygonRenderer(body));
	addRenderer(renderer);
}

bool TetrisStone::getIsPartOfTower(){
    return isPartOfTower;
}

float TetrisStone::getDistanceToPaddle(){
    return distanceToPaddle;
}

void TetrisStone::updateRelativeToPaddlePosition(ofVec2f paddlePosition){
    
    //check every 300ms
    if(lastCheckedRelativeToPaddleTime + 300 < ofGetElapsedTimeMillis()){
        
        ofVec2f vectorStoneToPaddle = body->getPosition() - paddlePosition;
        float newDistanceToPaddle = vectorStoneToPaddle.length();
        
        if(distanceToPaddle){
            positionChangeRelativeToPaddle = distanceToPaddle - newDistanceToPaddle;
        }
        distanceToPaddle = newDistanceToPaddle;
        
        positionChangeRelativeToPaddleSmoothed = 0.95 * positionChangeRelativeToPaddle + 0.05 * positionChangeRelativeToPaddleSmoothed;
        
        if(positionChangeRelativeToPaddleSmoothed < 10 && positionChangeRelativeToPaddleSmoothed > -10 ){
            isPartOfTower = true;
        } else {
            isPartOfTower = false;
        }
        
        lastCheckedRelativeToPaddleTime=ofGetElapsedTimeMillis();
    }
}

void TetrisStone::collide(){
    collided = true;
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
    if(collided){
        ofSetColor(0, 0, 255);
    }

    if(isPartOfTower){
         ofSetColor(255, 255, 0);
    }
    
    body->draw();
    //    for (auto& r : renderer) {
    //        r->render();
    //    }
    ofSetColor(255, 255, 255);
};


void TetrisStone::makeHeavy() {
    isHeavy = true;
//    not working todo: check this out dude
//    body->body->GetFixtureList()->SetDensity(10.0f);
//    body->body->ResetMassData();
}

void TetrisStone::makeBouncy() {
    isBouncy = true;
    body->body->GetFixtureList()->SetRestitution(0.5f);
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
    body->addImpulseForce(body->getB2DPosition()+ofVec2f(10,0), ofVec2f(0,0.2f));
}

void TetrisStone::rotateLeft() {
     body->addImpulseForce(body->getB2DPosition()-ofVec2f(10,0), ofVec2f(0,0.2f));
    //body->setRotation(body->getRotation() - 90);
}

void TetrisStone::createStoneVertecies(){
    string stone_L = "0,0; 1,0;1,2;2,2;2,3;0,3";
    string stone_Z = "0,0;2,0;2,1;3,1;3,2;1,2;1,1;0,1";
    string stone_I = "0,0;1,0;1,3;0,3";
    string stone_O = "0,0;2,0;2,2;0,2";
    string stone_T = "0,1;1,1;1,0;2,0;2,1;3,1;3,2;0,2";
    stones.push_back(stone_L);
    stones.push_back(stone_Z);
    stones.push_back(stone_I);
    stones.push_back(stone_O);
    stones.push_back(stone_T);
}

void TetrisStone::addToWorld(b2World* world){
    //create the physics object and add it to the physics world
    body->create(world);
    addBody(body);
    //create and add the renderer
    auto renderer = shared_ptr<PolygonRenderer>(new PolygonRenderer(body));
   // addRenderer(renderer);
}

vector <ofDefaultVertexType> TetrisStone::getRandomVertecies()
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

