#include "GameFactory.h"

shared_ptr<Paddle> GameFactory::makePaddle(shared_ptr<GameObjectContainer> objects, string name)
{
	shared_ptr<Paddle> ret = shared_ptr<Paddle>(new Paddle(name));
	shared_ptr<ofxBox2dRect> body = shared_ptr<ofxBox2dRect>(new ofxBox2dRect);
	body->enableGravity(false);
	body->setup(objects->physics.getWorld(), 10, 10, 150, 10);
	ret->addBody(body);

	return ret;
}

shared_ptr<GameObject> GameFactory::makeBasicStone(shared_ptr<GameObjectContainer> objects)
{
	//create the game object
	shared_ptr<GameObject> basicStone = shared_ptr<GameObject>(new GameObject("BasicStone_" + ofGetElapsedTimeMillis()));

	//create some points to form the shape
	vector <ofDefaultVertexType> pts;
	pts.push_back(ofDefaultVertexType(0, 0, 0));
	pts.push_back(ofDefaultVertexType(100, 0, 0));
	pts.push_back(ofDefaultVertexType(100, 100, 0));
	pts.push_back(ofDefaultVertexType(0, 100, 0));


	vector <ofVec2f> texCoords;
	texCoords.push_back(ofVec2f(0, 0));
	texCoords.push_back(ofVec2f(1, 0));
	texCoords.push_back(ofVec2f(1, 1));
	texCoords.push_back(ofVec2f(0, 1));

	//create the physics object and add it to the physics world
	auto body = shared_ptr<ofxBox2dPolygon>(new ofxBox2dPolygon);
	body->addVertices(pts);
	
	body->setPhysics(1.0, 0.3, 0.3);
	body->triangulatePoly();
	body->create(objects->physics.getWorld());
	//add the body to the object
	basicStone->addBody(body);

	//create and add the renderer
	auto renderer = shared_ptr<PolygonRenderer>(new PolygonRenderer(body));
	basicStone->addRenderer(renderer);

	return basicStone;
}

shared_ptr<DeleteOutOfScreenRule> GameFactory::makeDeleteOutOfScreenRule(GameParameters* params)
{
	return shared_ptr<DeleteOutOfScreenRule>(new DeleteOutOfScreenRule(params));
}

shared_ptr<GameControlRule> GameFactory::makeGameControlRule(GameParameters * params)
{
	return shared_ptr<GameControlRule>(new GameControlRule(params));
}
