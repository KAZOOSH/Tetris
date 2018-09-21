#include "NoGravityRule.h"



NoGravityRule::NoGravityRule(GameParameters* params,int runtime):Rule("NoGravityRule", params,runtime)
{
    
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
