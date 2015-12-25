//
//  particle.h
//  lightning
//
//  Created by Michael Glen on 9/24/15.
//
//

#ifndef __lightning__particle__
#define __lightning__particle__

#include <stdio.h>
#include "ofMain.h"

class particle : public ofBaseApp{
    
public:
    void setup(float _xPos,
               float _yPos,
               float _splitPercentage,
               float _xVel,
               float _yVel,
               float _xAcc,
               float _yAcc,
               ofColor _color,
               vector<float> _xSplits,
               vector<float> _ySplits);
    void update(vector<particle>& _vecref);
    void draw(bool isHit);
    void bolt();
    void stopParticle();
    bool hit;
    
private:
    
    float xPos;
    float yPos; //position
    float xVel, yVel; //width, length
    float xAcc, yAcc; //width, length
    float splitPercentage; //splitPercentage
    ofColor color; // color of branches...
    vector<float> xSplits;
    vector<float> ySplits;

    
};

#endif /* defined(__lightning__particle__) */
