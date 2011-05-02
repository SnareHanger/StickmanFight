#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	
	isLive		= true;
	isTracking	= true;
	isRecording = false;
	isCloud		= false;
	isCPBkgnd	= true;
	isMasking   = true;
    hasTwoPlayers = false;
    showDepthMap = true;
	
	setupRecording();
    
	ofBackground(255, 255, 255);
    
    threshold = 50;
    imgCtr = -1;
    
    setupActionImages();
	
}

void testApp::setupActionImages(){
    for (int i = 0; i < 6; i++) {
        char imageName[255];
        
        sprintf(imageName, "pows%i.png", imgCtr+1);
        ofImage actionImage;
        actionImage.loadImage(imageName);
        actionImage.allocate(640, 480, OF_IMAGE_COLOR);
        actionImage.resize(160, 120);
        
        actionImages.push_back(actionImage);
    }
    
    
}

void testApp::setupRecording(string _filename) {
	
	if (!recordContext.isInitialized()) {
		
		recordContext.setup();
		recordContext.setupUsingXMLFile();
		recordDepth.setup(&recordContext);
		recordImage.setup(&recordContext);
		
		recordUser.setup(&recordContext, &recordDepth, &recordImage);
		
		recordDepth.toggleRegisterViewport(&recordImage);
		recordContext.toggleMirror();
		
		oniRecorder.setup(&recordContext, &recordDepth, &recordImage);	
		
	} else {
		
		currentFileName = _filename;
		cout << currentFileName << endl;
	}
    
}

//--------------------------------------------------------------
void testApp::update(){
	
	if (isLive) {
		recordContext.update();
		if (isTracking) {
            recordUser.update();	
            setupLimbs();
            testLimbHits();
        }        
	} 
}

void testApp::testLimbHits(){
    if(hasTwoPlayers){
        //check player1 ends against all of player 2
        
        contactPoints.clear();
        
        //player1
        for (int i = 0; i < p2LimbVecs.size(); i++) {
            ofxVec3f limbToLimb = ofxVec3f(p1Left_lower_armEnd - p2LimbVecs[i]);
            if(limbToLimb.length() < threshold){
                contactPoints.push_back(contactPoint(p1Left_lower_armEnd));
            } 
        }
        
        for (int i = 0; i < p2LimbVecs.size(); i++) {
            ofxVec3f limbToLimb = ofxVec3f(p1Right_lower_armEnd - p2LimbVecs[i]);
            if(limbToLimb.length() < threshold){
                contactPoints.push_back(contactPoint(p1Right_lower_armEnd));
            } 
        }
        
        for (int i = 0; i < p2LimbVecs.size(); i++) {
            ofxVec3f limbToLimb = ofxVec3f(p1Left_lower_legEnd - p2LimbVecs[i]);
            if(limbToLimb.length() < threshold){
                contactPoints.push_back(contactPoint(p1Left_lower_legEnd));
            } 
        }
        
        for (int i = 0; i < p2LimbVecs.size(); i++) {
            ofxVec3f limbToLimb = ofxVec3f(p1Right_lower_legEnd - p2LimbVecs[i]);
            if(limbToLimb.length() < threshold){
                contactPoints.push_back(contactPoint(p1Right_lower_legEnd));
            } 
        }
        
        //player2
        for (int i = 0; i < p1LimbVecs.size(); i++) {
            ofxVec3f limbToLimb = ofxVec3f(p2Left_lower_armEnd - p1LimbVecs[i]);
            if(limbToLimb.length() < threshold){
                contactPoints.push_back(contactPoint(p2Left_lower_armEnd));
            } 
        }
        
        for (int i = 0; i < p1LimbVecs.size(); i++) {
            ofxVec3f limbToLimb = ofxVec3f(p2Right_lower_armEnd - p1LimbVecs[i]);
            if(limbToLimb.length() < threshold){
                contactPoints.push_back(contactPoint(p2Right_lower_armEnd));    
            }
        }
        
        for (int i = 0; i < p1LimbVecs.size(); i++) {
            ofxVec3f limbToLimb = ofxVec3f(p2Left_lower_legEnd - p1LimbVecs[i]);
            if(limbToLimb.length() < threshold){
                contactPoints.push_back(contactPoint(p2Left_lower_legEnd));  
            } 
        }
        
        for (int i = 0; i < p1LimbVecs.size(); i++) {
            ofxVec3f limbToLimb = ofxVec3f(p2Right_lower_legEnd - p1LimbVecs[i]);
            if(limbToLimb.length() < threshold){
                contactPoints.push_back(contactPoint(p2Right_lower_legEnd));
            } 
        }
        
        for(vector<contactPoint>::iterator iter = contactPoints.begin(); iter != contactPoints.end(); ++iter){        
            if((ofGetElapsedTimeMillis() - iter->startTime) > 1000){
                contactPoints.erase(iter);
            }
            
            cout << "x: " << iter->thePoint.x << "y: " << iter->thePoint.y << endl;
        }
        
    }
}

void testApp::setupLimbs(){
    if(recordUser.getTrackedUsers().size() > 0){
        
        p1LimbVecs.clear();
        
        
        //player1
        p1HipBegin = recordUser.getTrackedUsers()[0]->hip.begin; 
        p1NeckBegin = recordUser.getTrackedUsers()[0]->neck.begin;
        p1Left_lower_torsoBegin = recordUser.getTrackedUsers()[0]->left_lower_torso.begin;
        p1Left_upper_torsoBegin = recordUser.getTrackedUsers()[0]->left_upper_torso.begin;
        p1Left_lower_armBegin = recordUser.getTrackedUsers()[0]->left_lower_arm.begin;
        p1Left_upper_armBegin = recordUser.getTrackedUsers()[0]->left_upper_arm.begin;
        p1Left_lower_legBegin = recordUser.getTrackedUsers()[0]->left_lower_leg.begin;
        p1Left_upper_legBegin = recordUser.getTrackedUsers()[0]->left_upper_leg.begin;
        
        p1Right_lower_torsoBegin = recordUser.getTrackedUsers()[0]->right_lower_torso.begin;
        p1Right_upper_torsoBegin = recordUser.getTrackedUsers()[0]->right_upper_torso.begin;
        p1Right_lower_armBegin = recordUser.getTrackedUsers()[0]->right_lower_arm.begin;
        p1Right_upper_armBegin = recordUser.getTrackedUsers()[0]->right_upper_arm.begin;
        p1Right_lower_legBegin = recordUser.getTrackedUsers()[0]->right_lower_leg.begin;
        p1Right_upper_legBegin = recordUser.getTrackedUsers()[0]->right_upper_leg.begin;
        
        p1HipEnd = recordUser.getTrackedUsers()[0]->hip.end; 
        p1NeckEnd = recordUser.getTrackedUsers()[0]->neck.end;
        p1Left_lower_armEnd = recordUser.getTrackedUsers()[0]->left_lower_arm.end;
        p1Left_lower_legEnd = recordUser.getTrackedUsers()[0]->left_lower_leg.end;
        p1Right_lower_armEnd = recordUser.getTrackedUsers()[0]->right_lower_arm.end;
        p1Right_lower_legEnd = recordUser.getTrackedUsers()[0]->right_lower_leg.end;
        
        p1LimbVecs.push_back(p1HipBegin);
        p1LimbVecs.push_back(p1NeckBegin);
        p1LimbVecs.push_back(p1Left_lower_torsoBegin);
        p1LimbVecs.push_back(p1Left_upper_torsoBegin);
        p1LimbVecs.push_back(p1Left_lower_armBegin);
        p1LimbVecs.push_back(p1Left_lower_armBegin);
        p1LimbVecs.push_back(p1Left_lower_legBegin);
        p1LimbVecs.push_back(p1Left_upper_legBegin);
        
        p1LimbVecs.push_back(p1Right_lower_torsoBegin);
        p1LimbVecs.push_back(p1Right_upper_torsoBegin);
        p1LimbVecs.push_back(p1Right_lower_armBegin);
        p1LimbVecs.push_back(p1Right_lower_armBegin);
        p1LimbVecs.push_back(p1Right_lower_legBegin);
        p1LimbVecs.push_back(p1Right_upper_legBegin);
        
        p1LimbVecs.push_back(p1HipEnd);
        p1LimbVecs.push_back(p1Left_lower_armEnd);
        p1LimbVecs.push_back(p1Left_lower_legEnd);
        p1LimbVecs.push_back(p1Right_lower_armEnd);
        p1LimbVecs.push_back(p1Right_lower_legEnd);
    }
    
    if(recordUser.getTrackedUsers().size() > 1){
        
        hasTwoPlayers = true;
        //player2
        p2LimbVecs.clear();
        
        p2HipBegin = recordUser.getTrackedUsers()[1]->hip.begin; 
        p2NeckBegin = recordUser.getTrackedUsers()[1]->neck.begin;
        p2Left_lower_torsoBegin = recordUser.getTrackedUsers()[1]->left_lower_torso.begin;
        p2Left_upper_torsoBegin = recordUser.getTrackedUsers()[1]->left_upper_torso.begin;
        p2Left_lower_armBegin = recordUser.getTrackedUsers()[1]->left_lower_arm.begin;
        p2Left_upper_armBegin = recordUser.getTrackedUsers()[1]->left_upper_arm.begin;
        p2Left_lower_legBegin = recordUser.getTrackedUsers()[1]->left_lower_leg.begin;
        p2Left_upper_legBegin = recordUser.getTrackedUsers()[1]->left_upper_leg.begin;
        
        p2Right_lower_torsoBegin = recordUser.getTrackedUsers()[1]->right_lower_torso.begin;
        p2Right_upper_torsoBegin = recordUser.getTrackedUsers()[1]->right_upper_torso.begin;
        p2Right_lower_armBegin = recordUser.getTrackedUsers()[1]->right_lower_arm.begin;
        p2Right_upper_armBegin = recordUser.getTrackedUsers()[1]->right_upper_arm.begin;
        p2Right_lower_legBegin = recordUser.getTrackedUsers()[1]->right_lower_leg.begin;
        p2Right_upper_legBegin = recordUser.getTrackedUsers()[1]->right_upper_leg.begin;
        
        p2HipEnd = recordUser.getTrackedUsers()[1]->hip.end; 
        p2NeckEnd = recordUser.getTrackedUsers()[1]->neck.end;
        p2Left_lower_armEnd = recordUser.getTrackedUsers()[1]->left_lower_arm.end;
        p2Left_lower_legEnd = recordUser.getTrackedUsers()[1]->left_lower_leg.end;
        p2Right_lower_armEnd = recordUser.getTrackedUsers()[1]->right_lower_arm.end;
        p2Right_lower_legEnd = recordUser.getTrackedUsers()[1]->right_lower_leg.end;
        
        p2LimbVecs.push_back(p2HipBegin);
        p2LimbVecs.push_back(p2NeckBegin);
        p2LimbVecs.push_back(p2Left_lower_torsoBegin);
        p2LimbVecs.push_back(p2Left_upper_torsoBegin);
        p2LimbVecs.push_back(p2Left_lower_armBegin);
        p2LimbVecs.push_back(p2Left_lower_armBegin);
        p2LimbVecs.push_back(p2Left_lower_legBegin);
        p2LimbVecs.push_back(p2Left_upper_legBegin);
        
        p2LimbVecs.push_back(p2Right_lower_torsoBegin);
        p2LimbVecs.push_back(p2Right_upper_torsoBegin);
        p2LimbVecs.push_back(p2Right_lower_armBegin);
        p2LimbVecs.push_back(p2Right_lower_armBegin);
        p2LimbVecs.push_back(p2Right_lower_legBegin);
        p2LimbVecs.push_back(p2Right_upper_legBegin);
        
        p2LimbVecs.push_back(p2HipEnd);
        p2LimbVecs.push_back(p2Left_lower_armEnd);
        p2LimbVecs.push_back(p2Left_lower_legEnd);
        p2LimbVecs.push_back(p2Right_lower_armEnd);
        p2LimbVecs.push_back(p2Right_lower_legEnd);      
    }
    else hasTwoPlayers = false;
}

//--------------------------------------------------------------
void testApp::draw(){
	
	glPushMatrix();
	glScalef(0.75, 0.75, 0.75);
	
	if (isLive) {
		
		if(showDepthMap)
            recordDepth.draw(0,0,1280,960);
        
		if (isTracking) {
			
            glPushMatrix();
            glScalef(2.0, 2.0, 0);
            ofSetColor(0, 0, 0);
            drawStickMen();
			//recordUser.draw();
            for (int i = 0; i < contactPoints.size(); i++) {
                ofSetColor(255, 255, 255);
                if(imgCtr > 5)
                    imgCtr = -1;
                else 
                    imgCtr++;
                actionImages[imgCtr].draw(contactPoints[i].thePoint.x, contactPoints[i].thePoint.y);
                
            }
            glPopMatrix();
            
        }
	} 
	
	glPopMatrix();
}

void testApp::drawStickMen(){
    if(recordUser.getTrackedUsers().size() > 0){
        ofNoFill();
        
        float p1HipCenterX = (p1HipBegin.x + p1HipEnd.x)/2;
        float p1HipCenterY = (p1HipBegin.y + p1HipEnd.y)/2;
        
        ofCircle(p1NeckBegin.x, p1NeckBegin.y, 50);
        ofLine(p1NeckEnd.x, p1NeckEnd.y, (p1HipBegin.x + p1HipEnd.x)/2, (p1HipBegin.y + p1HipEnd.y)/2);
        ofLine(p1NeckEnd.x, p1NeckEnd.y, p1Left_lower_armBegin.x, p1Left_lower_armBegin.y);
        ofLine(p1NeckEnd.x, p1NeckEnd.y, p1Right_lower_armBegin.x, p1Right_lower_armBegin.y);
        ofLine(p1Left_lower_armBegin.x, p1Left_lower_armBegin.y, p1Left_lower_armEnd.x, p1Left_lower_armEnd.y);
        ofLine(p1Right_lower_armBegin.x, p1Right_lower_armBegin.y, p1Right_lower_armEnd.x, p1Right_lower_armEnd.y);
        ofLine(p1HipCenterX, p1HipCenterY, p1Left_lower_legBegin.x, p1Left_lower_legBegin.y);
        ofLine(p1HipCenterX, p1HipCenterY, p1Right_lower_legBegin.x, p1Right_lower_legBegin.y);
        ofLine(p1Left_lower_legBegin.x, p1Left_lower_legBegin.y, p1Left_lower_legEnd.x, p1Left_lower_legEnd.y);
        ofLine(p1Right_lower_legBegin.x, p1Right_lower_legBegin.y, p1Right_lower_legEnd.x, p1Right_lower_legEnd.y);
        
        
    }
    
    if(hasTwoPlayers){
        ofNoFill();
        
        float p2HipCenterX = (p2HipBegin.x + p2HipEnd.x)/2;
        float p2HipCenterY = (p2HipBegin.y + p2HipEnd.y)/2;
        
        ofCircle(p2NeckBegin.x, p2NeckBegin.y, 50);
        ofLine(p2NeckEnd.x, p2NeckEnd.y, (p2HipBegin.x + p2HipEnd.x)/2, (p2HipBegin.y + p2HipEnd.y)/2);
        ofLine(p2NeckEnd.x, p2NeckEnd.y, p2Left_lower_armBegin.x, p2Left_lower_armBegin.y);
        ofLine(p2NeckEnd.x, p2NeckEnd.y, p2Right_lower_armBegin.x, p2Right_lower_armBegin.y);
        ofLine(p2Left_lower_armBegin.x, p2Left_lower_armBegin.y, p2Left_lower_armEnd.x, p2Left_lower_armEnd.y);
        ofLine(p2Right_lower_armBegin.x, p2Right_lower_armBegin.y, p2Right_lower_armEnd.x, p2Right_lower_armEnd.y);
        ofLine(p2HipCenterX, p2HipCenterY, p2Left_lower_legBegin.x, p2Left_lower_legBegin.y);
        ofLine(p2HipCenterX, p2HipCenterY, p2Right_lower_legBegin.x, p2Right_lower_legBegin.y);
        ofLine(p2Left_lower_legBegin.x, p2Left_lower_legBegin.y, p2Left_lower_legEnd.x, p2Left_lower_legEnd.y);
        ofLine(p2Right_lower_legBegin.x, p2Right_lower_legBegin.y, p2Right_lower_legEnd.x, p2Right_lower_legEnd.y);
        
        
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	switch (key) {
		case 'd':
            showDepthMap = !showDepthMap;
            break;
        case 'q':
            threshold++;
            break;
        case 'a':
            threshold--;
            break;
		default:
			break;
	}	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

