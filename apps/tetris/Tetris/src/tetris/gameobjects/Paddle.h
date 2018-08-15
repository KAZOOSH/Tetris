#pragma once
#include "GameObject.h"
#include "ofxBox2d.h"

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
	Paddle(string name);
	~Paddle();
    void createBody(b2World* world);
    void render();
	void setAnchorPosition(ofVec2f anchor1, ofVec2f anchor2);
    //void setRotation(float rotation);
    //void setRotationDiff(float rotDiff);
	void updatePosition();
    void setDampingDiff(float damping);
    void setFrequencyDiff(float frequency);
    
private:
	ofVec2f position;
	ofVec2f anchorLeftPosition;
	ofVec2f anchorRightPosition;
    ofxBox2dCircle anchorLeft;
    ofxBox2dCircle anchorRight;
    ofxBox2dCircle anchorLeftStatic;
    ofxBox2dCircle anchorRightStatic;
    ofxBox2dCircle anchorBottom;
    
    ofxBox2dJoint anchorJointLeft;
    ofxBox2dJoint anchorJointRight;
    ofxBox2dJoint anchorJointLeftStatic;
    ofxBox2dJoint anchorJointRightStatic;
    ofxBox2dJoint anchorJointBottom;
 
	bool positionChanged = false;
    int paddleWidth = 250;
    int paddleHeight = 100;
    float frequencyHz = 1.0f;
    float damping = 5.0f;
};

