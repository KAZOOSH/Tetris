#include "Paddle.h"



Paddle::Paddle(string name):GameObject(name)
{
}

Paddle::~Paddle()
{
}

void Paddle::createBody(b2World* world){
    
    anchorLeft.setup(world, 1, 1, 4);
    anchorRight.setup(world, paddleWidth, 1, 4);
    anchorLeftStatic.setup(world, 1, 1, 4);
    anchorRightStatic.setup(world, paddleWidth, 1, 4);
    anchorBottom.setup(world, paddleWidth/2, 1, 4);

    shared_ptr<ofxBox2dRect> body = shared_ptr<ofxBox2dRect>(new ofxBox2dRect);
    body->enableGravity(false);
    body->setPhysics(1, 0, 1);
    body->setup(world, 1, 1, paddleWidth, paddleHeight);
    addBody(body);    

    
    //destroy fixture to avoid collisions
    anchorLeft.body->DestroyFixture(anchorLeft.body->GetFixtureList());
    anchorRight.body->DestroyFixture(anchorRight.body->GetFixtureList());
    anchorBottom.body->DestroyFixture(anchorBottom.body->GetFixtureList());
    anchorLeftStatic.body->DestroyFixture(anchorLeftStatic.body->GetFixtureList());
    anchorRightStatic.body->DestroyFixture(anchorRightStatic.body->GetFixtureList());
    float widthInBox2D = (paddleWidth/2)/OFX_BOX2D_SCALE;
    
    anchorJointLeft.setup(world, anchorLeft.body, body->body, b2Vec2(0,0), b2Vec2(-widthInBox2D,0), frequencyHz, damping,false);
    
    anchorJointRight.setup(world, anchorRight.body, body->body,b2Vec2((paddleWidth/OFX_BOX2D_SCALE),0), b2Vec2(widthInBox2D,0), frequencyHz, damping,false);

    anchorJointLeftStatic.setup(world, anchorLeftStatic.body, body->body, b2Vec2(0,0), b2Vec2(-widthInBox2D,0), frequencyHz, damping,false);
    
    anchorJointRightStatic.setup(world, anchorRightStatic.body, body->body,b2Vec2(((paddleWidth)/OFX_BOX2D_SCALE),0), b2Vec2(widthInBox2D,0), frequencyHz, damping,false);
    
    
    anchorJointBottom.setup(world, anchorBottom.body,body->body, b2Vec2(widthInBox2D,0), b2Vec2(0,0), frequencyHz, damping,false);
//
    // Join Length to zero
    anchorJointLeft.setLength(0);
    anchorJointRight.setLength(0);
    anchorJointBottom.setLength(0);
}

///\brief for testing perpuses, we should finally use a renderer for this
void Paddle::render()
{
	static_pointer_cast<ofxBox2dRect>(body[0])->draw();
    ofSetColor(255,100,100);
    anchorLeft.draw();
    anchorJointLeft.draw();
    anchorRight.draw();
    anchorJointRight.draw();
    
    anchorLeftStatic.draw();
    anchorJointLeftStatic.draw();
    anchorRightStatic.draw();
    anchorJointRightStatic.draw();
    anchorBottom.draw();
    anchorJointBottom.draw();
    ofSetColor(255,255,255);
    
    // draw values
    ofDrawBitmapString("frequencyHz: "+ ofToString(frequencyHz), 10, 10);
    ofDrawBitmapString("damping: " + ofToString(damping), 10, 40);
}

void Paddle::setDampingDiff(float diffDamping)
{
    damping += diffDamping;
    anchorJointLeft.setDamping(damping);
    anchorJointRight.setDamping(damping);
    anchorJointBottom.setDamping(damping);
}
void Paddle::setFrequencyDiff(float diffFrequency)
{
    frequencyHz += diffFrequency;
    anchorJointLeft.setFrequency(frequencyHz);
    anchorJointRight.setFrequency(frequencyHz);
    anchorJointBottom.setFrequency(frequencyHz);
}

void Paddle::setPosition(int x, int y)
{
	position.position = ofVec2f(x, y);
	position.hasChanged = true;
}

void Paddle::setRotation(float rotation)
{
    position.rotation = rotation;
}

void Paddle::setRotationDiff(float rotDiff){
    position.rotation +=rotDiff;
}

void Paddle::updatePosition()
{
    
    anchorLeft.setPosition(position.position.x, position.position.y - position.rotation);
    anchorRight.setPosition(position.position.x + 250, position.position.y + position.rotation);
    
    anchorLeftStatic.setPosition(position.position.x - 100, position.position.y);
    anchorRightStatic.setPosition(position.position.x + 350, position.position.y);
    
    anchorBottom.setPosition(position.position.x + 125, position.position.y+200);

//    anchorWithoutFixture->SetTransform(b2Vec2(b2dNum(position.position.x), b2dNum(position.position.y)), 0);
//    anchorWithoutFixture->SetLinearVelocity(b2Vec2(0, 0)); // maybe bring this back...
//    anchorWithoutFixture->SetAwake(true);
    
//    if (position.hasChanged) {
//        static_pointer_cast<ofxBox2dRect>(body[0])->setPosition(position.position.x, position.position.y);
//        static_pointer_cast<ofxBox2dRect>(body[0])->setRotation(position.rotation);
//        position.hasChanged = false;
//    }
}
