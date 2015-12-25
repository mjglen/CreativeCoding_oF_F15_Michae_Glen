//
//  dfDisplacementMap.h
//  HIFOCUS
//
//  Created by Michael Glen on 11/12/15.
//
//

#ifndef __HIFOCUS__dfDisplacementMap__
#define __HIFOCUS__dfDisplacementMap__

#include <stdio.h>
#include "ofMain.h"
#include "ofxOpenCv.h"

class dfDisplacementMap : public ofBaseApp{
    
public:
    void applyDisplaceMap(ofxCvColorImage& sourceImage,ofxCvColorImage& destImage, float hscale, float vscale);
private:

};

#endif /* defined(__HIFOCUS__dfDisplacementMap__) */
