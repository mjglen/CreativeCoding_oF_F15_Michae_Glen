//
//  systemUI.cpp
//  HIFOCUS
//
//  Created by Michael Glen on 10/16/15.
//
//

#include "systemUI.h"

void systemUI::setup() {
    myfont.loadFont("verdana.ttf", 24);
}

void systemUI::update(float _position, float _velocity, float _acceleration, float _fps, bool _state, float _acc_scalar, float _drag, float _spring) {
    state = _state;
    acceleration = _acceleration;
    velocity = _velocity;
    position = _position;
    acc_scalar = _acc_scalar;
    drag = _drag;
    spring = _spring;
    
}

void systemUI::draw(int _context) {
    ofSetColor(200,200,200);
    ofRect(25,(65+_context*50),700,50);
    ofSetHexColor(00000000);

    char tempStr[255]; // an array of chars
    
    sprintf(tempStr, "acc scalar: %f", acc_scalar);
    myfont.drawString(tempStr, 100,100);
    
    sprintf(tempStr, "drag: %f", drag);
    myfont.drawString(tempStr, 100,150);
    
    sprintf(tempStr, "spring: %f", spring);
    myfont.drawString(tempStr, 100,200);
    
    //myfont.drawString("fps", 100,250);

    sprintf(tempStr, "frame rate: %f state: %d velocity: %f position: %f", ofGetFrameRate(), state, velocity, position);
    myfont.drawString(tempStr, 100,250);
    
    //myfont.drawString("state", 250,250);
    
    //myfont.drawString("velocity", 400,250);
    //myfont.drawString("position", 550,250);
    
}