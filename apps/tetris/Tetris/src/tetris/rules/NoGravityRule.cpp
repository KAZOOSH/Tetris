#include "NoGravityRule.h"

NoGravityRule::NoGravityRule(shared_ptr<GameComponents> components,int runtime):GameRule("WindRule", components,runtime){
    
}

void NoGravityRule::applyRule()
{

    bool disableOnRuleEnd = ofGetElapsedTimef()-getCreationTime() > runtime -5;
    
    if(!gravityDisabled && !disableOnRuleEnd) {
        int i = 0;
        // apply on runtime start
        
        gravityDisabled = true;
    } else {
        if(disableOnRuleEnd) {
            // apply on runtime end
           
        }
    }
    

}
