#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    bgImage.loadImage("storm.jpg");
    vector<float> tempysplits;
    vector<float> tempxsplits;
    
    tempysplits.push_back(768);
    tempxsplits.push_back(500);
    
    myParticle.setup(
                     500, // float _xPos,
                     768, // float _yPos,
                     0.05, // float _splitPercentage,
                     0, // float _xVel,
                     -1, // float _yVel,
                     0, // float _xAcc,
                     ofRandom(-0.01,-0.04), // float _yAcc,
                     ofColor(0,0,0),
                     tempxsplits,
                     tempysplits); // ofColor _color);
    maxParticles = 20;
    numParticles = 1;
    particleVec.push_back(myParticle);
    isHit = false;
    timer = 350;



}

//--------------------------------------------------------------
void ofApp::update(){

    
    if(timer < 1) {
        cout << " ping ";
        vector<float> tempysplits;
        vector<float> tempxsplits;
        
        particleVec.erase(particleVec.begin(),particleVec.end());

        
        tempysplits.push_back(500);
        tempxsplits.push_back(768);
        
        myParticle.setup(
                         500, // float _xPos,
                         768, // float _yPos,
                         0.05, // float _splitPercentage,
                         0, // float _xVel,
                         -1, // float _yVel,
                         0, // float _xAcc,
                         ofRandom(-0.01,-0.04), // float _yAcc,
                         ofColor(0,0,0),
                         tempxsplits,
                         tempysplits); // ofColor _color);
        maxParticles = 20;
        numParticles = 1;
        particleVec.push_back(myParticle);
        isHit = false;
        timer = 350;
        ofSetColor(255,255,255,255);
        
    }
    
    for(int i = 0; i < particleVec.size(); i++){
        particleVec[i].update(vecref);
        
        if(particleVec[i].hit == true) {
            isHit = true;
        }
    }
    
    if(isHit == TRUE) {
        for(int i = 0; i < particleVec.size(); i++){
            particleVec[i].stopParticle();
        }
        
    }
    timer--;


}

//--------------------------------------------------------------
void ofApp::draw(){
    
        bgImage.draw(0,0,1200,768);
    
        for(int i = 0; i < particleVec.size(); i++){
            particleVec[i].draw(isHit);
        }
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
