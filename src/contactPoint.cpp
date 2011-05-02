//
//  contactPoint.cpp
//  StickManFight
//
//  Created by Michael Cohen on 4/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "contactPoint.h"

contactPoint::contactPoint(ofxVec3f newPoint){
    thePoint = newPoint; //ofxVec3f(newPoint.x * 2, newPoint.y * 2, newPoint.z);
    startTime = ofGetElapsedTimeMillis(); 
};