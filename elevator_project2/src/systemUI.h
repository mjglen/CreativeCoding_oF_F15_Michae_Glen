//
//  systemUI.h
//  HIFOCUS
//
//  Created by Michael Glen on 10/16/15.
//
//

#ifndef __HIFOCUS__systemUI__
#define __HIFOCUS__systemUI__

#include <stdio.h>
#include "ofMain.h"

class systemUI : public ofBaseApp{
    
    public:
        void setup();
        void update(float _position, float _velocity, float _acceleration, float _fps, bool _state, float _acc_scalar, float _drag, float _spring);
        void draw(int _context);
    private:
        float position;
        float spring;
        float drag;
        float acc_scalar;
        float velocity;
        float acceleration;
        float fps;
        bool state;
        ofTrueTypeFont myfont;
    
        int context;
};

#endif /* defined(__HIFOCUS__systemUI__) */
