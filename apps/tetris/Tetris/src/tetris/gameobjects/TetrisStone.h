#pragma once
#include "ofxBox2d.h"
#include "GameObject.h"
#include "GameParameters.h"
#include "PolygonRenderer.h"

class TetrisStone : public GameObject
{
public:
    TetrisStone(string name, GameParameters* params, GameParameters::effects activeEffect);
    ~TetrisStone();
    void addToWorld(b2World* world);
    void setPosition(ofVec2f position);
    void setPlayer(int player);
    void render();
    int getPlayerId();
    void rotateRight();
    void rotateLeft();
    void makeHeavy();
    void makeBouncy();
    float getDistanceToPaddle();
    bool isTetrisStone = true;
    bool collided = false;
    bool getIsPartOfTower();
    void collide();
    void updateRelativeToPaddlePosition(ofVec2f paddlePosition,float distanceToPaddleOrOtherTetrisStone);
    int getScale();
    string getType();
    
private:
    pair<string,vector <ofDefaultVertexType>> getRandomVertecies();
    vector <ofDefaultVertexType> vertecies;
    string stoneType;
    void createStoneVertecies();
    int scale= 40;
    int offsetX = 200;
    int playerId;
    uint64_t lastCheckedRelativeToPaddleTime = 0;
    shared_ptr<ofxBox2dPolygon> body;
    map<string,string> stones;
    
    float distanceToPaddle=10000;
    float positionChangeRelativeToPaddleSmoothed = 1;
    float positionChangeRelativeToPaddle;
    GameParameters* params;
    bool isBouncy;
	bool isHeavy;
	bool isLarge;
    bool isPartOfTower = false;

};

