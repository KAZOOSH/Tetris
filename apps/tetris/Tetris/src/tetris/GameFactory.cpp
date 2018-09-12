#include "GameFactory.h"

shared_ptr<Paddle> GameFactory::makePaddle(shared_ptr<GameComponents> components, string name)
{
    shared_ptr<Paddle> paddle = shared_ptr<Paddle>(new Paddle(name, components->params()));
    paddle->createBody(components->gameControl()->physics.getWorld());
    return paddle;
}

shared_ptr<TetrisStone> GameFactory::makeTetrisStone(shared_ptr<GameComponents> components, string activeEffect)
{
    shared_ptr<TetrisStone> stone = shared_ptr<TetrisStone>(new TetrisStone("TetrisStone", components->params(), activeEffect));
    
	//test: changed unique pointer
	stone->addToWorld(components->gameControl()->physics.world.get());
    //create and add the renderer
    shared_ptr<TetrisStoneRenderer> renderer;
    ofColor base;
    ofColor highlight;
    

	auto settings = components->params();
    if (activeEffect == "heavy") {
        ofJson c = settings->colorSchemes["heavy"];
        base = ofColor(c["base"][0], c["base"][1], c["base"][2]);
        highlight = ofColor(c["highlight"][0], c["highlight"][1], c["highlight"][2]);
        renderer = shared_ptr<HeavyStoneRenderer>(new HeavyStoneRenderer(stone, base, highlight));
    } else if (activeEffect == "bouncy") {
        ofJson c = settings->colorSchemes["bouncy"];
        base = ofColor(c["base"][0], c["base"][1], c["base"][2]);
        highlight = ofColor(c["highlight"][0], c["highlight"][1], c["highlight"][2]);
        renderer = shared_ptr<BouncyStoneRenderer>(new BouncyStoneRenderer(stone, base, highlight));
    } else if (activeEffect == "big") {
        settings->getRandomColorScheme(base, highlight);
        renderer = shared_ptr<TetrisStoneRenderer>(new TetrisStoneRenderer(stone, base, highlight,"BigStoneRenderer",25,40,5));
    } else if (activeEffect == "small") {
        settings->getRandomColorScheme(base, highlight);
        renderer = shared_ptr<TetrisStoneRenderer>(new TetrisStoneRenderer(stone, base, highlight, "SmallStoneRenderer", 25,0,0));
    } else {
        settings->getRandomColorScheme(base, highlight);
        renderer = shared_ptr<TetrisStoneRenderer>(new TetrisStoneRenderer(stone, base, highlight));
    }
    
    stone->addRenderer(renderer);
    
    stone->getBody()[0]->setData(stone.get());
    
    return stone;
}

shared_ptr<GameObject> GameFactory::makeBackgroundObject(shared_ptr<GameComponents> components)
{
    shared_ptr<GameObject> ret = shared_ptr<GameObject>(new GameObject("Background"));
    auto renderer = shared_ptr<BackgroundRenderer>(new BackgroundRenderer(components));
    ret->addRenderer(renderer);
    return ret;
}

shared_ptr<GameObject> GameFactory::makeBasicStone(shared_ptr<GameComponents> components)
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
    body->create(components->gameControl()->physics.getWorld());
    //add the body to the object
    basicStone->addBody(body);
    
    //create and add the renderer
    auto renderer = shared_ptr<PolygonRenderer>(new PolygonRenderer(body));
    basicStone->addRenderer(renderer);
    
    return basicStone;
}

shared_ptr<DeleteOutOfScreenRule> GameFactory::makeDeleteOutOfScreenRule(shared_ptr<GameComponents> components)
{
    return shared_ptr<DeleteOutOfScreenRule>(new DeleteOutOfScreenRule(components));
}

shared_ptr<GameControlRule> GameFactory::makeGameControlRule(shared_ptr<GameComponents> components)
{
    return shared_ptr<GameControlRule>(new GameControlRule(components));
}

shared_ptr<GameEventRule> GameFactory::makeGameEventRule(shared_ptr<GameComponents> components)
{
    return shared_ptr<GameEventRule>(new GameEventRule(components));
}

shared_ptr<StoneControlRule> GameFactory::makeStoneControlRule(shared_ptr<GameComponents> components)
{
	return shared_ptr<StoneControlRule>(new StoneControlRule(components));
}

shared_ptr<StoneCreationRule> GameFactory::makeStoneCreationRule(shared_ptr<GameComponents> components)
{
	return shared_ptr<StoneCreationRule>(new StoneCreationRule(components));
}

shared_ptr<Rule> GameFactory::makeWorldEffect(shared_ptr<GameComponents> components, ofJson config)
{
    if (config["state"] != nullptr) {
        if (config["state"] == "wind") {
            return shared_ptr<WindRule>(new WindRule(components, config["runtime"]));
        }
    }
    return shared_ptr<Rule>();
}
