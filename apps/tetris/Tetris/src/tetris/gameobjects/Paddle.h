#pragma once
#include "GameObject.h"
#include "ofxBox2d.h"
#include "GameParameters.h"

//class PaddlePosition {
//public:
//	void update(ofVec2f pos, float rot) {
//		position = pos;
//		rotation = rot;
//		hasChanged = true;
//	}
//	ofVec2f position;
//	float rotation;
//	bool hasChanged = false;
//};

class Paddle : public GameObject
{
    
public:
	Paddle(string name, GameParameters* params_);
	~Paddle();
    void createBody(b2World* world);
    void render();
	void setAnchorPosition(ofVec2f anchor1, ofVec2f anchor2);
    //void setRotation(float rotation);
    //void setRotationDiff(float rotDiff);
	void updatePosition();
    void setDampingDiff(float damping);
    void setFrequencyDiff(float frequency);
    
    bool isPaddleLeft;
    bool isPaddleRight;
    
    //statics
    static constexpr const char * paddleNameLeft = "leftPaddle";
    static constexpr const char * paddleNameRight = "rightPaddle";
 
    
private:
	ofVec2f position;
	ofVec2f anchorLeftPosition;
	ofVec2f anchorRightPosition;
    ofxBox2dCircle anchorLeft;
    ofxBox2dCircle anchorRight;
    ofxBox2dCircle anchorLeftStatic;
    ofxBox2dCircle anchorRightStatic;
    ofxBox2dCircle anchorBottomStatic;
    
    ofxBox2dJoint anchorJointLeft;
    ofxBox2dJoint anchorJointRight;
    ofxBox2dJoint anchorJointLeftStatic;
    ofxBox2dJoint anchorJointRightStatic;
    ofxBox2dJoint anchorJointBottomLeftStatic;
    ofxBox2dJoint anchorJointBottomRightStatic;
    
    GameParameters* params;
    
	bool positionChanged = false;
    int paddleWidth = 300;
    int paddleHeight = 100;
    float frequencyHz = 1.0f;
    float damping = 5.0f;
    
    int anchorMargin = 100;
    // positionen ausgehend von der linken oberen ecke des paddles
    ofVec2f anchorLeftStaticRelativePosition = ofVec2f(-anchorMargin, 0);
    ofVec2f anchorRightStaticRelativePosition = ofVec2f(paddleWidth + anchorMargin, 0);
    ofVec2f anchorBottomStaticRelativePosition = ofVec2f(paddleWidth/2, 0);
};

