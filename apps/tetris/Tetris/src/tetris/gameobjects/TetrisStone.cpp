#include "TetrisStone.h"


TetrisStone::TetrisStone(string name, GameParameters* params_, string activeEffect):GameObject(name)
{
    //isTetrisStone= true;
    //collided = false;
    params = params_;
    createStoneVertecies();
    body = shared_ptr<ofxBox2dPolygon>(new ofxBox2dPolygon);
    
    float density = params->params["tetrisStone"]["density"].get<float>();
    
    auto vertsAndType = getRandomVertecies();
    vertecies = vertsAndType.second;
    stoneType = vertsAndType.first;
    
    body->addVertices(vertecies);
    
    
	if (activeEffect == "heavy") {
		body->setPhysics(5.0, 0, 1.0);
	}else if (activeEffect == "heavy") {
		body->setPhysics(1.0, 0, 0.5);
	} else {
		body->setPhysics(1.0, 0, 1.0);
	}

    
    body->triangulatePoly();
    
    //body->body->SetUserData(this->body);
    //body->setData(new TetrisStone(name,params_));
    
    //    int myInt = 123;
    //    body.get()->setData(this);
    //    TetrisStone * stone = (TetrisStone*)body.get()->getData();
    //    body->body->SetUserData(<#void *data#>)
    //    body->body->SetUserData((void*)myInt);
    
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

void TetrisStone::updateRelativeToPaddlePosition(ofVec2f paddlePosition, float distanceToPaddleOrOtherTetrisStone){
    
    //check every 300ms
    if(lastCheckedRelativeToPaddleTime + 300 < ofGetElapsedTimeMillis()){
        
        ofVec2f vectorStoneToPaddle = body->getPosition() - paddlePosition;
        float newDistanceToPaddle = vectorStoneToPaddle.length();
        
        if(distanceToPaddle){
            positionChangeRelativeToPaddle = distanceToPaddle - newDistanceToPaddle;
        }
        distanceToPaddle = newDistanceToPaddle;
        
        positionChangeRelativeToPaddleSmoothed = 0.95 * positionChangeRelativeToPaddle + 0.05 * positionChangeRelativeToPaddleSmoothed;
        
        if(positionChangeRelativeToPaddleSmoothed < 10 && positionChangeRelativeToPaddleSmoothed > -10 && distanceToPaddleOrOtherTetrisStone < 150 ){
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

int TetrisStone::getScale()
{
    return scale;
}

string TetrisStone::getType()
{
    return stoneType;
}

TetrisStone::~TetrisStone()
{
}

void TetrisStone::render() {
    /*if(isBouncy){
        ofSetColor(255, 0, 0);
    }
    if(isHeavy){
        ofSetColor(0, 255, 0);
    }
    if(collided){
        ofSetColor(0, 0, 255);
    }*/

    /*if(isPartOfTower){
         ofSetColor(255, 255, 0);
    }*/
    
    //body->draw();
        for (auto& r : renderer) {
            r->render();
        }
    ofSetColor(255, 255, 255);
};


void TetrisStone::makeHeavy() {
    isHeavy = true;
    //    not working todo: check this out dude
    // body->setPhysics(10.0f, 1.0f, 0.1f);
}

void TetrisStone::makeBouncy() {
    isBouncy = true;
    // body->setPhysics(1.0f, 0.0f, 0.2f);
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
    stones.insert(pair<string,string>("stone_L",stone_L));
    stones.insert(pair<string, string>("stone_Z", stone_Z));
    stones.insert(pair<string, string>("stone_I", stone_I));
    stones.insert(pair<string, string>("stone_O", stone_O));
    stones.insert(pair<string, string>("stone_T", stone_T));
}

void TetrisStone::addToWorld(b2World* world){
    //create the physics object and add it to the physics world
    body->create(world);
    addBody(body);
    //create and add the renderer
    // auto renderer = shared_ptr<PolygonRenderer>(new PolygonRenderer(body));
    // addRenderer(renderer);
}

pair<string, vector <ofDefaultVertexType>> TetrisStone::getRandomVertecies()
{
    vector <ofDefaultVertexType> pts;
    
    
    int max = ofRandom(stones.size());
    int i = 0;
    
    pair <string, string> stonePair;
    for (auto& v:stones){
        if (i == max) stonePair = v;
        ++i;
    }
    
    string randomStone = stonePair.second;
    vector<string> pairs = ofSplitString(randomStone, ";");
    for(int i=0; i < pairs.size(); i++){
        vector<string> values = ofSplitString(pairs[i], ",");
        pts.push_back(ofDefaultVertexType(ofToInt(values[0]) * scale + offsetX, ofToInt(values[1]) * scale, 0));
    }
    return pair<string, vector <ofDefaultVertexType>>(stonePair.first, pts);
}

