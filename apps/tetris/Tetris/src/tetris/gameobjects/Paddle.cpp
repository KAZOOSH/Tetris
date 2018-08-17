#include "Paddle.h"



Paddle::Paddle(string name):GameObject(name)
{
}

Paddle::~Paddle()
{
}

void Paddle::createBody(b2World* world){
    
    anchorLeft.setup(world, 1, 1, 10);
    anchorRight.setup(world, paddleWidth, 1, 10);
    anchorLeftStatic.setup(world, 1, 1, 4);
    anchorRightStatic.setup(world, paddleWidth, 1, 4);
    anchorBottom.setup(world, paddleWidth/2, 1, 4);

    shared_ptr<ofxBox2dRect> body = shared_ptr<ofxBox2dRect>(new ofxBox2dRect);
    body->enableGravity(false);
    body->setPhysics(0.1, 0, 1);
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
    ofSetColor(100,100,255);
    anchorLeft.draw();
    anchorJointLeft.draw();
    anchorRight.draw();
    anchorJointRight.draw();
    
	ofSetColor(255, 100, 100);
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

void Paddle::setAnchorPosition(ofVec2f anchorLeft, ofVec2f anchorRight)
{
	
	anchorLeftPosition = anchorLeft;
	anchorRightPosition = anchorRight;

	position = anchorLeft - 0.5*(anchorLeft - anchorRight) - ofVec2f(0,100);

	positionChanged = true;

}

//void Paddle::setRotation(float rotation)
//{
//    position.rotation = rotation;
//}

//void Paddle::setRotationDiff(float rotDiff){
//    position.rotation +=rotDiff;
//}

void Paddle::updatePosition()
{
	if (positionChanged) {
		anchorLeft.setPosition(anchorLeftPosition.x, anchorLeftPosition.y);
		anchorRight.setPosition(anchorRightPosition.x + 250, anchorRightPosition.y);

		anchorLeftStatic.setPosition(position.x - 200, position.y);
		anchorRightStatic.setPosition(position.x + 450, position.y);

		anchorBottom.setPosition(position.x + 125, position.y + 200);
	}


//    anchorWithoutFixture->SetTransform(b2Vec2(b2dNum(position.position.x), b2dNum(position.position.y)), 0);
//    anchorWithoutFixture->SetLinearVelocity(b2Vec2(0, 0)); // maybe bring this back...
//    anchorWithoutFixture->SetAwake(true);
    
//    if (position.hasChanged) {
//        static_pointer_cast<ofxBox2dRect>(body[0])->setPosition(position.position.x, position.position.y);
//        static_pointer_cast<ofxBox2dRect>(body[0])->setRotation(position.rotation);
//        position.hasChanged = false;
//    }
}
