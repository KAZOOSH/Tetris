#include "GameFactory.h"

shared_ptr<Paddle> GameFactory::makePaddle(shared_ptr<GameObjectContainer> objects, string name, GameParameters* params)
{
	shared_ptr<Paddle> paddle = shared_ptr<Paddle>(new Paddle(name, params));
    paddle->createBody(objects->physics.getWorld());
    return paddle;
}

shared_ptr<TetrisStone> GameFactory::makeTetrisStone(shared_ptr<GameObjectContainer> objects, GameParameters* params)
{
    shared_ptr<TetrisStone> stone = shared_ptr<TetrisStone>(new TetrisStone("TetrisStone", params));
    stone->addToWorld(objects->physics.getWorld());
    
	//create and add the renderer
	ofColor base;
	ofColor highlight;
	params->getRandomColorScheme(base, highlight);
	auto renderer = shared_ptr<TetrisStoneRenderer>(new TetrisStoneRenderer(stone, base, highlight));
	stone->addRenderer(renderer);

    stone->getBody()[0]->setData(stone.get());
    return stone;
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
