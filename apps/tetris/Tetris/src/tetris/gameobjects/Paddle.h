#pragma once
#include "GameObject.h"
#include "ofxBox2d.h"

class PaddlePosition {
public:
	void update(ofVec2f pos, float rot) {
		position = pos;
		rotation = rot;
		hasChanged = true;
	}
	ofVec2f position;
	float rotation;
	bool hasChanged = false;
};

class Paddle : public GameObject
{
public:
	Paddle(string name);
	~Paddle();
    void createBody(b2World* world);
    void render();
	void setPosition(int x, int y);
    void setRotation(float rotation);
    void setRotationDiff(float rotDiff);
	void updatePosition();
    void setDampingDiff(float damping);
    void setFrequencyDiff(float frequency);
    
private:
	PaddlePosition position;
    ofxBox2dCircle anchorLeft;
    ofxBox2dCircle anchorRight;
    ofxBox2dJoint anchorJointLeft;
    ofxBox2dJoint anchorJointRight;
    
    int paddleWidth = 250;
    int paddleHeight = 100;
    float frequencyHz = 1.0f;
    float damping = 5.0f;
};

