#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"

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
    
        ofxAssimpModelLoader model;
    
		bool bAnimate;
        bool bAnimateMouse;
        float animationPosition;

        ofMesh mesh;
        ofMesh planeMesh;
        ofLight	light;
        ofCamera cam2;
        ofEasyCam cam;
        ofSpherePrimitive sfear;
        ofVec3f vert;
        ofVec3f nullVec;
        ofVec3f spherePos;
        ofVec3f spherePos2;
        ofVec3f oVec;
    
        vector<ofVec3f>  meshVel;
        vector<ofVec3f>  meshPos;
        vector<ofVec3f>  attractMesh;
        vector<ofVec3f>  meshAcc;
        vector<ofVec3f>  particles;
        vector<ofVec3f>  pVel;
        vector<ofVec3f>  pAcc;
    
        vector<ofVec3f>  planeMeshVel;
        vector<ofVec3f>  planeMeshPos;
        vector<ofVec3f>  planeAttractMesh;
        vector<ofVec3f>  planeMeshAcc;
    
        float attractScalar;
        float sphereScalar;
    
        ofVideoPlayer vid;
        ofTexture vidTexture;
        //ofPixels frame;
        ofPlanePrimitive vidPlane;
    
        bool forceOne;
        bool forceTwo;
        bool forceThree;
        bool forceFour;
        bool forceFive;
        bool forceSix;
        bool forceSeven;
        bool forceEight;
    
};

#endif
