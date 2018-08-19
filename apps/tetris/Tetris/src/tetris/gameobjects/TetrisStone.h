#pragma once
#include "PolygonRenderer.h"
#include "ofxBox2d.h"
#include "GameObject.h"
#include "GameParameters.h"

class TetrisStone : public GameObject
{
public:
    TetrisStone(string name, GameParameters* params);
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
    void updateRelativeToPaddlePosition(ofVec2f paddlePosition);
    //void makeLarge();
    
private:
    vector <ofDefaultVertexType> getRandomVertecies();
    vector <ofDefaultVertexType> vertecies;
    void createStoneVertecies();
    int scale= 40;
    int offsetX = 200;
    int playerId;
    UInt64 lastCheckedRelativeToPaddleTime = 0;
    shared_ptr<ofxBox2dPolygon> body;
    vector<string> stones;
    float distanceToPaddle=10000;
    float positionChangeRelativeToPaddleSmoothed = 1;
    float positionChangeRelativeToPaddle;
    GameParameters* params;
    bool isBouncy;
	bool isHeavy;
	bool isLarge;
    bool isPartOfTower;
};

