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
    //anchorWithoutFixture = world->CreateBody(&anchorWithoutFixtureBodyDef);
    
    shared_ptr<ofxBox2dRect> body = shared_ptr<ofxBox2dRect>(new ofxBox2dRect);
    body->enableGravity(false);
    body->setPhysics(20.0f, 0, 2.0);
    body->setup(world, 1, 1, paddleWidth, paddleHeight);
    addBody(body);    

//    anchorJointLeft.setup(world, anchorLeft.body, body->body, b2Vec2(0,0), b2Vec2(0,height/2));
//    anchorJointRight.setup(world, anchorRight.body, body->body, b2Vec2(0,0), b2Vec2(width,height/2));
    
    anchorLeft.body->DestroyFixture(anchorLeft.body->GetFixtureList());
    anchorRight.body->DestroyFixture(anchorRight.body->GetFixtureList());
    
    float widthInBox2D = (paddleWidth/2)/OFX_BOX2D_SCALE;
    
    anchorJointLeft.setup(world, anchorLeft.body, body->body, b2Vec2(0,0), b2Vec2(-widthInBox2D,0), frequencyHz, damping,false);
    anchorJointRight.setup(world, anchorRight.body, body->body,b2Vec2(paddleWidth/OFX_BOX2D_SCALE,0), b2Vec2(widthInBox2D,0), frequencyHz, damping,false);
    
    // Join Length to zero
    anchorJointLeft.setLength(0);
    anchorJointRight.setLength(0);
    
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
}
void Paddle::setFrequencyDiff(float diffFrequency)
{
    frequencyHz += diffFrequency;
    anchorJointLeft.setFrequency(frequencyHz);
    anchorJointRight.setFrequency(frequencyHz);
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

//    anchorWithoutFixture->SetTransform(b2Vec2(b2dNum(position.position.x), b2dNum(position.position.y)), 0);
//    anchorWithoutFixture->SetLinearVelocity(b2Vec2(0, 0)); // maybe bring this back...
//    anchorWithoutFixture->SetAwake(true);
    
//    if (position.hasChanged) {
//        static_pointer_cast<ofxBox2dRect>(body[0])->setPosition(position.position.x, position.position.y);
//        static_pointer_cast<ofxBox2dRect>(body[0])->setRotation(position.rotation);
//        position.hasChanged = false;
//    }
}
