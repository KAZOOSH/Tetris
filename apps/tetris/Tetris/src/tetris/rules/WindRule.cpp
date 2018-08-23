#include "WindRule.h"



WindRule::WindRule(GameParameters* params,int runtime):Rule("WindRule", params,runtime)
{

}

void WindRule::applyRule()
{
	for (auto& obj : objects) {
		auto bodies = obj->getBody();
		for (auto& body : bodies) {
			//body->addForce(ofVec2f(1.0, 0.0), 1.0);
		}
	}
}

