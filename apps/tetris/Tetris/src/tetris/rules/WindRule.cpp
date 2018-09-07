#include "WindRule.h"



WindRule::WindRule(shared_ptr<GameComponents> components,int runtime):GameRule("WindRule", components,runtime)
{

}

void WindRule::applyRule()
{
	float now = ofGetElapsedTimef();
	int i = 0;
	auto objects = components->objects()->objects;
	for (auto& obj : objects) {
			auto bodies = obj->getBody();
			if (obj->getName() == "TetrisStone") {
				float v = ofSignedNoise(now*0.4 +i*112) * 20;
				shared_ptr<TetrisStone> stone = std::static_pointer_cast<TetrisStone>(obj);
				if (!stone->collided) {
					for (auto& body : bodies) {
						body->setVelocity(body->getVelocity() + ofVec2f(v, 0));
						//body->addForce(ofVec2f(1.0, 0.0), 1.0);
					}
				}
				
			}
			++i;
		}
}

