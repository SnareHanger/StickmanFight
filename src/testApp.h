#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxOpenNI.h"
#include "contactPoint.h"


class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    
    void	setupRecording(string _filename = "");
    void    testLimbHits();
    void    setupLimbs();
    void    drawStickMen();
	void    setupActionImages();
    
    bool				isLive, isTracking, isRecording, isCloud, isCPBkgnd, isMasking, hasTwoPlayers, showDepthMap;
    
    string				currentFileName;
    int     imgCtr;
    
    float threshold;
	
    ofxOpenNIContext	recordContext, playContext;
    ofxDepthGenerator	recordDepth, playDepth;
    ofxImageGenerator	recordImage, playImage;
    ofxUserGenerator	recordUser, playUser;
    ofxOpenNIRecorder	oniRecorder;
    
    vector<ofxVec3f>    p1LimbVecs, p2LimbVecs;
    vector<contactPoint>    contactPoints;
    vector<ofImage>     actionImages;
    
    
    //Player1 Limb Begins
    ofxVec3f p1NeckBegin;
	
	// left arm + shoulder
	ofxVec3f p1Left_shoulderBegin;
	ofxVec3f p1Left_upper_armBegin;
	ofxVec3f p1Left_lower_armBegin;
	
	// right arm + shoulder
	ofxVec3f p1Right_shoulderBegin;
	ofxVec3f p1Right_upper_armBegin;
	ofxVec3f p1Right_lower_armBegin;
	
	// torso
	ofxVec3f p1Left_upper_torsoBegin;
	ofxVec3f p1Right_upper_torsoBegin;
	
	// left lower torso + leg
	ofxVec3f p1Left_lower_torsoBegin;
	ofxVec3f p1Left_upper_legBegin;
	ofxVec3f p1Left_lower_legBegin;
	
	// right lower torso + leg
	ofxVec3f p1Right_lower_torsoBegin;
	ofxVec3f p1Right_upper_legBegin;
	ofxVec3f p1Right_lower_legBegin;
    
	ofxVec3f p1HipBegin;
    
    //Player1 Limb Ends
    ofxVec3f p1NeckEnd;
	
	// left arm + shoulder
	ofxVec3f p1Left_shoulderEnd;
	ofxVec3f p1Left_upper_armEnd;
	ofxVec3f p1Left_lower_armEnd;
	
	// right arm + shoulder
	ofxVec3f p1Right_shoulderEnd;
	ofxVec3f p1Right_upper_armEnd;
	ofxVec3f p1Right_lower_armEnd;
	
	// torso
	ofxVec3f p1Left_upper_torsoEnd;
	ofxVec3f p1Right_upper_torsoEnd;
	
	// left lower torso + leg
	ofxVec3f p1Left_lower_torsoEnd;
	ofxVec3f p1Left_upper_legEnd;
	ofxVec3f p1Left_lower_legEnd;
	
	// right lower torso + leg
	ofxVec3f p1Right_lower_torsoEnd;
	ofxVec3f p1Right_upper_legEnd;
	ofxVec3f p1Right_lower_legEnd;
    
	ofxVec3f p1HipEnd;
    
    
    //Player2 Limb Begins
    ofxVec3f p2NeckBegin;
	
	// left arm + shoulder
	ofxVec3f p2Left_shoulderBegin;
	ofxVec3f p2Left_upper_armBegin;
	ofxVec3f p2Left_lower_armBegin;
	
	// right arm + shoulder
	ofxVec3f p2Right_shoulderBegin;
	ofxVec3f p2Right_upper_armBegin;
	ofxVec3f p2Right_lower_armBegin;
	
	// torso
	ofxVec3f p2Left_upper_torsoBegin;
	ofxVec3f p2Right_upper_torsoBegin;
	
	// left lower torso + leg
	ofxVec3f p2Left_lower_torsoBegin;
	ofxVec3f p2Left_upper_legBegin;
	ofxVec3f p2Left_lower_legBegin;
	
	// right lower torso + leg
	ofxVec3f p2Right_lower_torsoBegin;
	ofxVec3f p2Right_upper_legBegin;
	ofxVec3f p2Right_lower_legBegin;
    
	ofxVec3f p2HipBegin;
    
    //Player2 Limb Ends
    ofxVec3f p2NeckEnd;
	
	// left arm + shoulder
	ofxVec3f p2Left_shoulderEnd;
	ofxVec3f p2Left_upper_armEnd;
	ofxVec3f p2Left_lower_armEnd;
	
	// right arm + shoulder
	ofxVec3f p2Right_shoulderEnd;
	ofxVec3f p2Right_upper_armEnd;
	ofxVec3f p2Right_lower_armEnd;
	
	// torso
	ofxVec3f p2Left_upper_torsoEnd;
	ofxVec3f p2Right_upper_torsoEnd;
	
	// left lower torso + leg
	ofxVec3f p2Left_lower_torsoEnd;
	ofxVec3f p2Left_upper_legEnd;
	ofxVec3f p2Left_lower_legEnd;
	
	// right lower torso + leg
	ofxVec3f p2Right_lower_torsoEnd;
	ofxVec3f p2Right_upper_legEnd;
	ofxVec3f p2Right_lower_legEnd;
    
	ofxVec3f p2HipEnd;    
};

#endif
