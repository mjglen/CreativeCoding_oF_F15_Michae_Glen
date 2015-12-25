//
//  dfDisplacementMap.cpp
//  HIFOCUS
//
//  Created by Michael Glen on 11/12/15.
//
//

#include "dfDisplacementMap.h"
#include "ofxOpenCv.h"

void dfDisplacementMap::applyDisplaceMap(ofxCvColorImage& sourceImage,ofxCvColorImage& destImage, float hscale=0.05, float vscale=0.05){
    //apply displacement
    int width = 500;
    int height = 500;
    
    unsigned char * displacePixels  = this->getPixels();
    unsigned char * pixels          = sourceImage.getPixels();
    int displace,hdisplace,vdisplace;
    int totalPixels=height*width*3;
    for (int i = 0; i < totalPixels;i+=3){
        hdisplace = (int)((displacePixels[i] - 127)*hscale); //x coord
        vdisplace = (int)((displacePixels[i+2] - 127) *vscale); //y coord
        if( i%(width*3)+hdisplace*3 >0 &&
           i%(width*3)+hdisplace*3<width*3){
            displace=hdisplace+vdisplace*width;
        }else{
            displace = 0;
        }
        displace*= 3;
        if(i+displace>0 && i+displace<totalPixels){
            tempVideoDisplaced[i]   = pixels[i+displace];
            tempVideoDisplaced[i+1] = pixels[i+displace+1];
            tempVideoDisplaced[i+2] = pixels[i+displace+2];
        }
        //now fade the displacePixels
        if(displacePixels[i] > 127){
            displacePixels[i] = displacePixels[i] - 1;
        } else {
            displacePixels[i] = displacePixels[i] + 1;
        }
    }
    destImage.setFromPixels(tempVideoDisplaced, width, height);
}