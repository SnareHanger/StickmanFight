//
//  contactPoint.h
//  StickManFight
//
//  Created by Michael Cohen on 4/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ofMain.h"
#include "ofxVectorMath.h"

class contactPoint {  
    
public:
    contactPoint(ofxVec3f newPoint);
    void ageIt();
    
    ofxVec3f thePoint;
    int startTime;
    int lifeTimer;
    bool drawIt;
    
    bool killIt;
    
};