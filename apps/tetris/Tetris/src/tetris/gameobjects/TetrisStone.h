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
    bool isTetrisStone = true;
    bool collided = false;
    void collide();
    //void makeLarge();
    
private:
    vector <ofDefaultVertexType> getRandomVertecies();
    vector <ofDefaultVertexType> vertecies;
    void createStoneVertecies();
    int scale= 40;
    int offsetX = 200;
    int playerId;
    shared_ptr<ofxBox2dPolygon> body;
    vector<string> stones;
    
    GameParameters* params;
    bool isBouncy;
	bool isHeavy;
	bool isLarge;
};

