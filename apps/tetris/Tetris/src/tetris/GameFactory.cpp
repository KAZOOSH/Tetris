#include "GameFactory.h"

shared_ptr<Paddle> GameFactory::makePaddle(shared_ptr<GameObjectContainer> objects, string name, GameParameters* params)
{
    shared_ptr<Paddle> paddle = shared_ptr<Paddle>(new Paddle(name, params));
    paddle->createBody(objects->physics.getWorld());
    return paddle;
}

shared_ptr<TetrisStone> GameFactory::makeTetrisStone(shared_ptr<GameObjectContainer> objects, GameParameters* params, string activeEffect)
{
    shared_ptr<TetrisStone> stone = shared_ptr<TetrisStone>(new TetrisStone("TetrisStone", params, activeEffect));
    
    stone->addToWorld(objects->physics.getWorld());
    
    //create and add the renderer
	shared_ptr<TetrisStoneRenderer> renderer;
    ofColor base;
    ofColor highlight;

	activeEffect = "small";

	if (activeEffect == "base") {
		params->getRandomColorScheme(base, highlight);
		renderer = shared_ptr<TetrisStoneRenderer>(new TetrisStoneRenderer(stone, base, highlight));
	}else if (activeEffect == "heavy") {
		ofJson c = params->colorSchemes["heavy"];
		base = ofColor(c["base"][0], c["base"][1], c["base"][2]);
		highlight = ofColor(c["highlight"][0], c["highlight"][1], c["highlight"][2]);
		renderer = shared_ptr<HeavyStoneRenderer>(new HeavyStoneRenderer(stone, base, highlight));
	} else if (activeEffect == "bouncy") {
		ofJson c = params->colorSchemes["bouncy"];
		base = ofColor(c["base"][0], c["base"][1], c["base"][2]);
		highlight = ofColor(c["highlight"][0], c["highlight"][1], c["highlight"][2]);
		renderer = shared_ptr<BouncyStoneRenderer>(new BouncyStoneRenderer(stone, base, highlight));
	} else if (activeEffect == "big") {
		params->getRandomColorScheme(base, highlight);
		renderer = shared_ptr<TetrisStoneRenderer>(new TetrisStoneRenderer(stone, base, highlight,"BigStoneRenderer",25,40,5));
	} else if (activeEffect == "small") {
		params->getRandomColorScheme(base, highlight);
		renderer = shared_ptr<TetrisStoneRenderer>(new TetrisStoneRenderer(stone, base, highlight, "SmallStoneRenderer", 25,0,0));
	}
    
    stone->addRenderer(renderer);
    
    stone->getBody()[0]->setData(stone.get());
    
    return stone;
}

shared_ptr<GameObject> GameFactory::makeBackgroundObject(shared_ptr<GameObjectContainer> objects, GameParameters * params)
{
    shared_ptr<GameObject> ret = shared_ptr<GameObject>(new GameObject("Background"));
    auto renderer = shared_ptr<BackgroundRenderer>(new BackgroundRenderer(params, objects));
    ret->addRenderer(renderer);
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

shared_ptr<GameControlRule> GameFactory::makeGameControlRule(GameParameters * params, GameObjectContainer* gameObjects)
{
    return shared_ptr<GameControlRule>(new GameControlRule(params,gameObjects));
}

shared_ptr<GameEventRule> GameFactory::makeGameEventRule(GameParameters * params)
{
	return shared_ptr<GameEventRule>(new GameEventRule(params));
}

shared_ptr<Rule> GameFactory::makeWorldEffect(GameParameters * params, ofJson config)
{
	if (config["state"] != nullptr) {
		if (config["state"] == "wind") {
			return shared_ptr<WindRule>(new WindRule(params, config["runtime"]));
		}
	}
	return shared_ptr<Rule>();
}
