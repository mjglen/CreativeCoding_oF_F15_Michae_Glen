//
//  particle.cpp
//  lightning
//
//  Created by Michael Glen on 9/24/15.
//
//

#include "particle.h"


void particle::setup(float _xPos,
                     float _yPos,
                     float _splitPercentage,
                     float _xVel,
                     float _yVel,
                     float _xAcc,
                     float _yAcc,
                     ofColor _color,
                     vector<float> _xSplits,
                     vector<float> _ySplits){
    
    // set incoming values based on what was passed in from previous instance of branch
    xPos = _xPos;
    yPos = _yPos;
    splitPercentage = _splitPercentage;
    xVel = _xVel;
    yVel = _yVel;
    xAcc = _xAcc;
    yAcc = _yAcc;
    color = _color;
    hit = false;
    xSplits = _xSplits;
    ySplits = _ySplits;
    xSplits.push_back(xPos);
    ySplits.push_back(yPos);
}

//--------------------------------------------------------------
void particle::update(vector<particle>& _vecref){
    xVel += xAcc;
    yVel += yAcc;
    xPos += xVel;
    yPos += yVel;
    if(ofRandom(1) < splitPercentage) {
        float thing = ofRandom(-1,1);
        particle tempParticle;
        xVel = -1*thing;
        xSplits.push_back(xPos);
        ySplits.push_back(yPos);
        cout << " split- " << yPos;
        tempParticle.setup(xPos, // float _xPos,
                           yPos, // float _yPos,
                           0.02, // float _splitPercentage,
                           thing, // float _xVel,
                           -1, // float _yVel,
                           0, // float _xAcc,
                           0, // float _yAcc,
                           ofColor(0,0,0),
                           xSplits,
                           ySplits); // ofColor _color);
        _vecref.push_back(tempParticle);
        
        
    }
    
    if((yPos < 50)&&(hit==false)) {
        hit = true;
        xSplits.push_back(xPos);
        ySplits.push_back(yPos);

    }
    
}

//--------------------------------------------------------------
void particle::draw(bool isHit){
    if(isHit == false) {
        ofCircle(xPos, yPos*-1+768, 3, 3);
    } else {
    bolt();
    }
    
}
void particle::bolt(){
    //ofCircle(xPos, yPos*-1+768, 50, 50);
    if(xSplits.size() > 1) {
        if(hit==true) {
            ofSetLineWidth(ofRandom(4,7));
            ofSetColor(255,255,255,255);
        } else {
            ofSetLineWidth(ofRandom(1,2));
            ofSetColor(255,255,255,20);
        }
        for(int i = 1; i < (xSplits.size()-1); i++){
            ofLine(xSplits[i],-1*ySplits[i]+768,xSplits[i+1],-1*ySplits[i+1]+768);
           // cout << " bolt at " << ySplits[i];
           // ofLine(0,0,400,700);
        }
        ofSetColor(255,255,255,200);
    }
    
}

void particle::stopParticle(){
    xVel = 0;
    yVel = 0;
    xAcc = 0;
    yAcc = 0;
    splitPercentage = 0;
    
}