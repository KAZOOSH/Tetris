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
        body->setPhysics(10.0, 0, 1.0);
    } else if (activeEffect == "bouncy") {
        body->setPhysics(1.0, 0.1, 1.0);
    } else if (activeEffect == "icy") {
        body->setPhysics(1.0, 0, 0.1);
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
    //body->addImpulseForce(body->getB2DPosition()+ofVec2f(10,0), ofVec2f(0,0.2f));
    if(!collided){
        //        body->setFixedRotation(true);
        body->setRotation(body->getRotation() + 90);
        //        body->body->SetTransform(b2Vec2(0, 0), DEG_TO_RAD * 90);
        
        //     body->body->SetTransform(body->body->GetWorldCenter(), DEG_TO_RAD * 90);    }
    }
}

void TetrisStone::rotateLeft() {
    //body->addImpulseForce(body->getB2DPosition()-ofVec2f(10,0), ofVec2f(0,0.2f));
    if(!collided){
        body->setRotation(body->getRotation() - 90);
    }
}


// super weired !!!! setzt man die größe auf die hälfte und verdoppelt den scale funktioniert die kollision bei manchen steinen nicht mehr
void TetrisStone::createStoneVertecies(){
    string stone_L = "0,0; 2,0;2,4;4,4;4,6;0,6";
    string stone_Z = "0,0;4,0;4,2;6,2;6,4;2,4;2,2;0,2";
    string stone_I = "0,0;2,0;2,6;0,6";
    string stone_O = "0,0;4,0;4,4;0,4";
    string stone_T = "0,2;2,2;2,0;4,0;4,2;6,2;6,4;0,4";
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
    
    int width=0;
    int height=0;
    
    // parse stone strings
    // get maximum height and width of stone
    for(int i=0; i < pairs.size(); i++){
        vector<string> values = ofSplitString(pairs[i], ",");
        int x= ofToInt(values[0]);
        int y= ofToInt(values[1]);
        if(x>width)
        {width = x;}
        if(y>height)
        {height = y;}
    }
    // use height and width to create centered stones for easy rotation
    for(int i=0; i < pairs.size(); i++){
        vector<string> values = ofSplitString(pairs[i], ",");
        pts.push_back(ofDefaultVertexType((ofToFloat(values[0]) - width/2) * scale, (ofToInt(values[1]) - 1.5) * scale, 0));
    }
    return pair<string, vector <ofDefaultVertexType>>(stonePair.first, pts);
}

