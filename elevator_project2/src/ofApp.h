#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"
#include "systemUI.h"
#include "ofxAVFVideoPlayer.h"
#include "ofxOpenCv.h"
#include "dfDisplacementMap.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofxAVFVideoPlayer	aMovie;
    ofxAVFVideoPlayer 	bMovie;
    ofxAVFVideoPlayer 	cMovie;
    ofxAVFVideoPlayer 	dMovie;
    
    systemUI myUI;
    
    bool                frameByframe;

    float velocity;
    float position;
    float absPos;
    float acceleration;
    float drag;
    float spring;
    float stick;
    float nearest;
    float acc_scalar;
    float screenPosA;
    float screenPosB;
    float screenPosC;
    float screenPosD;
    float distanceTo;
    float escapeVel;
    float escapeVel2;
    int target2;
    int absTarget2;
    int yRes;
    int xRes;
    int input;
    int closestSpot;
    int horizon;
    int target;
    int easeCounter;
    int easeCounter2;
    int cMovieCounter;
    int cMovieCounter2;
    float cMoviePos;
    bool cPlaying;
    int bMovieCounter;
    bool state;
    bool hallStart;
    bool tripped;
    bool escapeSwitch;
    float fps;
    float tempVel;
    float framesInit;
    float velInit;
    bool dPerspective;
    int UIcontext;
    int Ctrl;
    
    
    ofTexture tex;
    ofTexture tempTex;
    ofFbo frameBuffer;
    ofFbo tempBuffer;
    ofxSyphonServer individualTextureSyphonServer;
    
    ofSoundPlayer  soundDing;
    ofSoundPlayer  soundUpUp;
    ofSoundPlayer  soundUpDown;
    ofSoundPlayer  soundDown;
    ofSoundPlayer  soundFloorA;
    ofSoundPlayer  soundFloorB;
    ofSoundPlayer  soundFloorC;
    ofSoundPlayer  soundFloorD;
    ofSoundPlayer &soundFloor = soundFloorA;
    int floorArrayPos;
    int floorArray[4] = {0,2,-1,1};
    ofSoundPlayer  soundRain;
    float soundFloorVol;
    
    ofxCvColorImage img;
    
		
};
