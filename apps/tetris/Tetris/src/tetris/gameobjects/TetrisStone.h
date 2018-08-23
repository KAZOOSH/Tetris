#pragma once
#include "ofxBox2d.h"
#include "GameObject.h"
#include "GameParameters.h"
#include "PolygonRenderer.h"

class TetrisStone : public GameObject
{
public:
    TetrisStone(string name, GameParameters* params, string activeEffect);
    ~TetrisStone();
    void addToWorld(b2World* world);
    void setPosition(ofVec2f position);
    void setPlayer(int player);
    void render();
    int getPlayerId();
    void rotateRight();
    void rotateLeft();
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
    int scale= 20;
    int offsetX = 400;
    int playerId;
    uint64_t lastCheckedRelativeToPaddleTime = 0;
    shared_ptr<ofxBox2dPolygon> body;
    map<string,string> stones;
    
    float distanceToPaddle=10000;
    float positionChangeRelativeToPaddleSmoothed = 1;
    float positionChangeRelativeToPaddle;
    GameParameters* params;
    bool isBouncy = false;
	bool isHeavy = false;
	bool isLarge = false;
    bool isPartOfTower = false;;
};

