#include "Paddle.h"


Paddle::Paddle(string name, shared_ptr<GameParameters> params_):GameObject(name)
{
    settings = params_;
    isPaddleLeft = name == paddleNameLeft;
    isPaddleRight = name == paddleNameRight;
}

Paddle::~Paddle()
{
}

void Paddle::createBody(b2World* world){
    int x = 1;
    int y = 1;
    
    if(isPaddleLeft){
        x = settings->settings["paddle"]["leftStartPosition"]["x"].get<int>();
        y = settings->settings["paddle"]["leftStartPosition"]["y"].get<int>();
    } else if(isPaddleRight){
        x = settings->settings["paddle"]["rightStartPosition"]["x"].get<int>();
        y = settings->settings["paddle"]["rightStartPosition"]["y"].get<int>();
    }
    
    // load from params and overwrite defaults
    paddleWidth = settings->settings["paddle"]["width"].get<int>();
    paddleHeight = settings->settings["paddle"]["height"].get<int>();
    anchorMargin = settings->settings["paddle"]["anchorMargin"].get<int>();
    
    frequencyHz = settings->settings["paddle"]["frequency"].get<float>();
    damping = settings->settings["paddle"]["damping"].get<float>();
    density = settings->settings["paddle"]["density"].get<float>();
    
    body = shared_ptr<ofxBox2dRect>(new ofxBox2dRect);
    body->enableGravity(false);
    body->setPhysics(3, 0, 1.0f);
    body->setup(world, x, y, paddleWidth, paddleHeight);
    addBody(body);
    
    anchorLeft.setup(world, x, y, 10);
    anchorRight.setup(world, x + paddleWidth, y, 10);
    anchorLeftStatic.setup(world, x - anchorMargin, y, 4);
    anchorRightStatic.setup(world, x + paddleWidth + anchorMargin, y, 4);
    anchorBottomStatic.setup(world, x-paddleWidth/2, y + anchorMargin, 4);
    
    //destroy fixture to avoid collisions
    anchorLeft.body->DestroyFixture(anchorLeft.body->GetFixtureList());
    anchorRight.body->DestroyFixture(anchorRight.body->GetFixtureList());
    anchorBottomStatic.body->DestroyFixture(anchorBottomStatic.body->GetFixtureList());
    anchorLeftStatic.body->DestroyFixture(anchorLeftStatic.body->GetFixtureList());
    anchorRightStatic.body->DestroyFixture(anchorRightStatic.body->GetFixtureList());
    
    // distance in box2d world
    float widthInBox2D = paddleWidth/OFX_BOX2D_SCALE;
    float marginInBox2D = anchorMargin/OFX_BOX2D_SCALE;
    float heightInBox2D = paddleHeight/OFX_BOX2D_SCALE;
    float xb2D = x/OFX_BOX2D_SCALE;
    float yb2D = y/OFX_BOX2D_SCALE;
    b2Vec2 paddlePosB2D = b2Vec2(xb2D,yb2D);
    
    // positions relative to center in box2d world for joints
    b2Vec2 paddleLeftTopPos = paddlePosB2D + b2Vec2(-widthInBox2D/2,-heightInBox2D/2);
    b2Vec2 paddleRightTopPos = paddlePosB2D + b2Vec2(widthInBox2D/2,-heightInBox2D/2);
    b2Vec2 paddleLeftBottomPos = paddlePosB2D + b2Vec2(-widthInBox2D/2,heightInBox2D/2);
    b2Vec2 paddleRightBottomPos = paddlePosB2D + b2Vec2(widthInBox2D/2,heightInBox2D/2);
    
    b2Vec2 anchorRightPos = paddlePosB2D + b2Vec2(widthInBox2D,0);
    b2Vec2 anchorLeftStaticPos = paddlePosB2D + b2Vec2(-marginInBox2D,0);
    b2Vec2 anchorRightStaticPos = paddlePosB2D + b2Vec2(widthInBox2D + marginInBox2D,0);
    b2Vec2 anchorBottomStaticPos = paddlePosB2D+ b2Vec2(-widthInBox2D/2,marginInBox2D);
    
    anchorJointLeft.setup(world, anchorLeft.body, body->body,paddlePosB2D, paddleLeftTopPos, frequencyHz, damping, false);
    anchorJointRight.setup(world, anchorRight.body, body->body, anchorRightPos, paddleRightTopPos, frequencyHz, damping, false);
    anchorJointLeftStatic.setup(world,anchorLeftStatic.body,body->body,anchorLeftStaticPos,paddleLeftTopPos,frequencyHz,damping,false);
    anchorJointRightStatic.setup(world,anchorRightStatic.body,body->body,anchorRightStaticPos,paddleRightTopPos,frequencyHz,damping,false);
    anchorJointBottomLeftStatic.setup(world,anchorBottomStatic.body,body->body,anchorBottomStaticPos,paddleLeftBottomPos, frequencyHz, damping, false);
    anchorJointBottomRightStatic.setup(world, anchorBottomStatic.body, body->body,anchorBottomStaticPos, paddleRightBottomPos, frequencyHz, damping, false);
    
    // Join Length to zero
    anchorJointLeft.setLength(0);
    anchorJointRight.setLength(0);
    anchorJointRightStatic.setLength(anchorMargin);
    anchorJointLeftStatic.setLength(anchorMargin);
    anchorJointBottomLeftStatic.setLength(anchorMargin);
    anchorJointBottomRightStatic.setLength(anchorMargin);

	//create paddle texture
	createTexture();
}

///\brief for testing perpuses, we should finally use a renderer for this
void Paddle::render()
{
    // draw towerheight
    float x = getPaddleBodyPosition().x;
    float y = getPaddleBodyPosition().y - towerHeight - paddleHeight/2;
    
	ofPushMatrix();
	ofTranslate(body->ofxBox2dBaseShape::getPosition());
	ofRotateDeg(body->getRotation());
	ofSetColor(255);
	texture.draw(-body->getWidth()*0.5, -body->getHeight()*0.5);
	ofPopMatrix();

	
	//debug
	
	/*
	ofDrawLine(x - 200, y, x + 200, y);
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
    anchorJointBottomLeftStatic.draw();
    anchorJointBottomRightStatic.draw();
    anchorBottomStatic.draw();
    ofSetColor(255,255,255);
    
    // draw values
    ofDrawBitmapString("frequencyHz: "+ ofToString(frequencyHz), 10, 10);
    ofDrawBitmapString("damping: " + ofToString(damping), 10, 40);
	*/
}

ofVec2f Paddle::getPaddleBodyPosition(){
    return body->getPosition();
}

void Paddle::createTexture()
{
	int w = body->getWidth();
	int h = body->getHeight();
	texture.allocate(w, h);
	texture.begin();
	ofSetColor(100);
	ofDrawRectangle(0, 0, w,h);

	ofSetColor(240, 13, 13);

	int dx = 50;
	int x = dx;
	int ws = 20;
	while (x<w*2)
	{
		ofPushMatrix();
		ofTranslate(x, 0);
		ofPushMatrix();
		ofRotate(45.f);
		ofDrawRectangle(-50, 0, ws, h+100);
		x += dx;
		ofPopMatrix();
		ofPopMatrix();
	}


	/*ofSetColor(220);
	int d1 = w * 0.01;
	ofDrawRectangle(d1, 0, h, h);
	ofDrawRectangle(w-h-d1, 0, h, h);

	ofDrawRectangle((w-h)*0.5, 0, h, h);

	ofSetColor(240,13,13);
	int d2 = w*0.25;
	ofDrawRectangle(d2, 0, h*1.7, h);
	ofDrawRectangle(w - h*1.7 - d2, 0, h*1.7, h);

	ofSetColor(220);
	ofNoFill();
	ofSetLineWidth(2);
	ofDrawRectangle(0, 0, w, h);*/

	texture.end();
}

void Paddle::setDampingDiff(float diffDamping)
{
    damping += diffDamping;
    anchorJointLeft.setDamping(damping);
    anchorJointRight.setDamping(damping);
    anchorJointLeftStatic.setDamping(damping);
    anchorJointRightStatic.setDamping(damping);
    anchorJointBottomLeftStatic.setDamping(damping);
    anchorJointBottomRightStatic.setDamping(damping);
}

void Paddle::setFrequencyDiff(float diffFrequency)
{
    frequencyHz += diffFrequency;
    anchorJointLeft.setFrequency(frequencyHz);
    anchorJointRight.setFrequency(frequencyHz);
    anchorJointLeftStatic.setDamping(frequencyHz);
    anchorJointRightStatic.setDamping(frequencyHz);
    anchorJointBottomLeftStatic.setFrequency(frequencyHz);
    anchorJointBottomRightStatic.setFrequency(frequencyHz);
}

void Paddle::setAnchorPosition(ofVec2f anchorLeft, ofVec2f anchorRight)
{
    anchorLeftPosition = anchorLeft;
    anchorRightPosition = anchorRight;
    
    // get center
    position = (anchorLeft + anchorRight) /2;
    positionChanged = true;
}

void Paddle::updatePosition()
{
    if (positionChanged) {
        anchorLeft.setPosition(anchorLeftPosition.x, anchorLeftPosition.y);
        anchorRight.setPosition(anchorRightPosition.x, anchorRightPosition.y);
        
        // set anchors relative to paddle center
        anchorLeftStatic.setPosition(position.x - paddleWidth/2 - anchorMargin, position.y);
        anchorRightStatic.setPosition(position.x + paddleWidth/2 + anchorMargin, position.y);
        anchorBottomStatic.setPosition(position.x, position.y + paddleHeight/2 + anchorMargin);
    }
    // add little force to paddle to avoid it gets stuck
    body->addImpulseForce(body->getB2DPosition()-ofVec2f(1,0), ofVec2f(0,0.1f));

}
