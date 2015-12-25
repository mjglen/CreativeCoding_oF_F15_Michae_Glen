#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetWindowTitle("ofxSyphon Example");
    
    individualTextureSyphonServer.setName("Texture Output");
    
    
    ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.

    
    ofBackground(255,255,255);
    ofSetVerticalSync(true);
    frameByframe = false;
    
    yRes = 1280;
    xRes = 3072;
    horizon = 640;
    
    tex.allocate(xRes, yRes, GL_RGB);
    frameBuffer.allocate(xRes, yRes, GL_RGB);
    tempTex.allocate(xRes, yRes, GL_RGB);
    tempBuffer.allocate(xRes, yRes, GL_RGB);
    
    aMovie.loadMovie("movies/3ktestcompA.mov");
    aMovie.play();
    bMovie.loadMovie("movies/3ktestcompB.mov");
    bMovie.play();
    cMovie.loadMovie("movies/3ktestcompC.mov");
    cMovie.play();
    dMovie.loadMovie("movies/3ktestcompD_1.mov");
    dMovie.play();
    state = FALSE;
    tripped = FALSE;
    fps = 0;
    position = 0;
    absPos = 0;
    velocity = 0;
    acc_scalar = 0.00005;
    spring = 0.0001;
    acceleration = 0;
    input = 0;
    drag = 0.99;
    closestSpot = 0;
    distanceTo = 0;
    target = 0;
    absTarget2 = 0;
    easeCounter = 100;
    easeCounter2 = 200;
    escapeVel = 0.004;
    escapeVel2 = 0.005;
    hallStart = FALSE;
    escapeSwitch = FALSE;
    framesInit = 0;
    velInit = 0;
    cMoviePos = 0;
    dPerspective = TRUE;
    
    UIcontext = 0;
    Ctrl = 0;
    myUI.setup();
    
    cMovieCounter = 0;
    bMovieCounter = 0;
    cPlaying = FALSE;
    soundFloorVol = 0.5;
    
    soundDing.loadSound("sounds/ding.wav");
    soundUpUp.loadSound("sounds/soundUpUp.wav");
    soundUpDown.loadSound("sounds/soundUpDown.wav");
    soundDown.loadSound("sounds/soundDown.wav");
    soundFloorA.loadSound("sounds/soundA.wav");
    soundFloorB.loadSound("sounds/soundB.wav");
    soundFloorC.loadSound("sounds/soundC.wav");
    soundFloorD.loadSound("sounds/soundD.wav");
    soundRain.loadSound("sounds/soundRain.wav");
    soundFloor = soundFloorA;
    soundDing.setVolume(0.1f);
    soundUpUp.setVolume(0.75f);
    soundUpDown.setVolume(0.75f);
    soundDown.setVolume(0.75f);
    soundFloor.setVolume(soundFloorVol);
    soundFloor.play();
    soundDing.setMultiPlay(TRUE);
    soundRain.setMultiPlay(TRUE);
    floorArrayPos = 0;


}

//--------------------------------------------------------------
void ofApp::update(){
    //cout << ofGetFrameRate() << "   ";
    ofSoundUpdate();
    aMovie.update();
    bMovie.update();
    cMovie.update();
    dMovie.update();
    soundFloorVol = 1/(fabsf((target2-position))+1);
    //cout << " soundVol " << soundFloorVol;
    soundFloorVol = 1/(velocity*1000+0.75);
    soundFloor.setVolume(soundFloorVol);
    
    if(hallStart == TRUE) {
        aMovie.play();
        if(aMovie.getPosition() > 0.9) aMovie.stop();
    } else {
        aMovie.stop();
    }
    
    //aMovie.stop();
    //bMovie.play();
    //cMovie.play();
    dMovie.play();
    bMovie.stop();
    
    if(cMovieCounter2 > 200) {
        cMovieCounter = 0;
    }
    if(cMovie.getPosition() > cMoviePos) {
        cPlaying = FALSE;
    }
    
    if(cPlaying == TRUE) {
        cMovie.play();
    } else {
        cMovie.stop();
    }
  

    
    bMovie.setPosition((absPos/1.5)+0.5);
//    if(dPerspective == TRUE) {
//        dMovie.setPosition(((absPos-2)/1.5)+0.5);
//    }
    
    // accelerator (previous position, previous velocity, input)
        // int velocity, position, acceleration, drag, stick,  value, nearest
        // acceleration = input state * scalar
    acceleration = input*acc_scalar;
    closestSpot = round(absPos);
//    distanceTo = absPos - closestSpot;
    
    if(input == 0) {

        velocity = velocity*drag;
        if(escapeSwitch == TRUE) {
            velocity = (velInit/framesInit)*easeCounter2*-1+velInit;
            easeCounter2 ++;
            if(easeCounter2 > framesInit) {
                easeCounter2 = 0;
                escapeSwitch = FALSE;
                soundDown.stop();
                soundDing.play();
                velocity = 0;
            }
            
        } else {
            if(fabsf(velocity) < escapeVel) {
               // velocity = tempVel;
                target = round(position+velocity*velocity*100);
                velocity = (target-position)/easeCounter;
                //if(fabsf(velocity) > escapeVel) velocity = tempVel;
                easeCounter --;
                if(easeCounter == 0) {
                    easeCounter = 1;
                }
            } else {
                easeCounter = 100;
            }
        }
    }

    velocity = velocity + acceleration;
        // if drag < stick value velocity is zero
        // position =  previous position + velocity
    position = position + velocity;
        // if under -2 add 4 if over 2 subtract 4


    

    
    if(input == 0) {
        if((velocity < 0.001)&&(velocity>-0.001)&&(distanceTo*distanceTo < .00001)) {
            absPos = closestSpot;
            velocity = 0;
            acceleration = 0;
        }
    }
    absPos = fmod(float(position),float(4));
    if(absPos > 2) {
        absPos -= 4;
   }
    if(absPos < -2) {
        absPos += 4;
    }
    


    
    myUI.update(position, velocity, acceleration, fps, state, acc_scalar, drag, spring);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    

    
    ofSetHexColor(0xFFFFFF);
    
    frameBuffer.begin();
    hallStart = FALSE;
    screenPosB = -1*(absPos*-1*yRes);
    if(absPos>0) {
        screenPosD = -1*(absPos*-1*yRes+2*yRes);
        screenPosC = -1*(absPos*-1*yRes+3*yRes);
        screenPosA = -1*(absPos*-1*yRes+yRes);
        
    } else {
        screenPosD = -1*(absPos*-1*yRes-2*yRes);
        screenPosC = -1*(absPos*-1*yRes-1*yRes);
        screenPosA = -1*(absPos*-1*yRes+yRes);
    }
    
    if((absPos - closestSpot)*(absPos - closestSpot) < .00005) {
       // absPos = closestSpot;
        if(closestSpot == 0) {
            bMovie.draw(0,screenPosB);
        } else if(closestSpot == 1) {
            hallStart = TRUE;
            aMovie.draw(0,screenPosA);
        } else if(closestSpot == 2) {
            dMovie.draw(0,screenPosD);
        } else if(closestSpot == -2) {
            dMovie.draw(0,screenPosD);
        } else if(closestSpot == -1) {
            cMovieCounter ++;
            if(cPlaying == TRUE){
                cMovieCounter2 ++;
            }
            if((tripped == FALSE)&&(cMovieCounter > 100)) {
                state = TRUE;
            }
            cMovie.draw(0,screenPosC);
        }
    } else {
        if((absPos > 1)&&(absPos < 2)) {
            aMovie.draw(0,screenPosA);
//            tempTex = aMovie.getTextureReference();
//            tempBuffer.begin();
//                tempTex.drawSubsection(0, 0, xRes, yRes-horizon, 0, 0, xRes, yRes-horizon);
//                tempTex.drawSubsection(0, horizon, xRes, horizon, 0, horizon, xRes, horizon*(((absPos-1)*-1.2)+1));
//                ofRect(0,horizon+(horizon*(((absPos+1)*-1.2)+1)),xRes,horizon*(((absPos+1)*-1.2)+1));
//            tempBuffer.end();
//            tempBuffer.draw(0,screenPosA);
            
            dMovie.draw(0,screenPosD);
            
        } else if((absPos > 0)&&(absPos < 1)) {
            aMovie.draw(0,screenPosA);
//            tempTex = aMovie.getTextureReference();
//            tempBuffer.begin();
//                tempTex.drawSubsection(0, 0, xRes, yRes-horizon, 0, 0, xRes, yRes-horizon);
//                tempTex.drawSubsection(0, horizon, xRes, horizon, 0, horizon, xRes, horizon*(((absPos-1)*-1.2)+1));
//                ofSetColor(0,0,0);
//                ofRect(0,horizon+horizon*(((absPos-1)*1.2)+1),xRes,yRes);
//                ofSetColor(255,255,255);
//            tempBuffer.end();
//            tempBuffer.draw(0,screenPosA);
            
            bMovie.draw(0,screenPosB);
        } else if((absPos > -1)&&(absPos < 0)) {
            bMovie.draw(0,screenPosB);
            //cMovie.draw(0,screenPosC);
            tempTex = cMovie.getTextureReference();
            tempBuffer.begin();
                tempTex.drawSubsection(0, 0, xRes, yRes-horizon, 0, 0, xRes, yRes-horizon);
                tempTex.drawSubsection(0, horizon, xRes, horizon, 0, horizon, xRes, horizon*(((absPos+1)*-1.2)+1));
                //ofRect(0,horizon+(horizon*(((absPos+1)*-1.2)+1)),xRes,horizon*(((absPos+1)*-1.2)+1));
            tempBuffer.end();
            tempBuffer.draw(0,screenPosC);
        } else if((absPos > -2)&&(absPos < -1)) {
            //cMovie.draw(0,screenPosC);
            tempTex = cMovie.getTextureReference();
            dMovie.draw(0,screenPosC);
            tempBuffer.begin();
            
            
                tempTex.drawSubsection(0, 0, xRes, yRes-horizon, 0, 0, xRes, yRes-horizon);
                tempTex.drawSubsection(0, horizon, xRes, horizon, 0, horizon, xRes, horizon*(((absPos+1)*-2)+1));
            
//                ofSetColor(0,0,0);
//                ofRect(0,horizon+horizon*(((absPos+1)*1.2)+1),xRes,yRes);
//                ofSetColor(255,255,255);
            tempBuffer.end();
            tempBuffer.draw(0,screenPosC);
            dMovie.draw(0,screenPosD);
        } else {
            bMovie.draw(0,screenPosA);
            bMovie.draw(0,screenPosB);
            cMovie.draw(0,screenPosC);
            dMovie.draw(0,screenPosD);
        }
        
        cMovieCounter = 0;
        cMovieCounter2 = 0;
        tripped = FALSE;
    }
    
    frameBuffer.end();
    tex = frameBuffer.getTextureReference();
    frameBuffer.draw(0,300,xRes/2,yRes/2);

    individualTextureSyphonServer.publishTexture(&tex);
    myUI.draw(UIcontext);


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_DOWN) {
        UIcontext ++;
    }
    
    if(key == OF_KEY_UP) {
        UIcontext --;
    }
    
    if(key == 'r') {
        position = 0;
        acceleration = 0;
        hallStart = FALSE;
        escapeSwitch = FALSE;
        framesInit = 0;
        velInit = 0;
        cMoviePos = 0;
        
        UIcontext = 0;
        Ctrl = 0;
        myUI.setup();
        
        cMovieCounter = 0;
        bMovieCounter = 0;
        cPlaying = FALSE;
        state = FALSE;
        tripped = FALSE;
        cMoviePos = 0;
        aMovie.setPosition(0);
        cMovie.setPosition(0);
    }
    
    if(UIcontext > 2) {
        UIcontext = 0;
    }
    
    if(key == OF_KEY_RIGHT) {
        if(UIcontext == 0) {
            acc_scalar += 0.00001;
        } else if(UIcontext == 1) {
            drag += 0.001;
        } else if(UIcontext == 2) {
            spring += 0.00001;
        }
    } else if(key == OF_KEY_LEFT) {
        if(UIcontext == 0) {
            acc_scalar -= 0.00001;
        } else if(UIcontext == 1) {
            drag -= 0.001;
        } else if(UIcontext == 2) {
            spring -= 0.00001;
        }
    } else {
        Ctrl = 0;
    }
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
    if(state == FALSE) {
        if(button == 0) {
            soundUpUp.play();
            input = 1;
            easeCounter = 100;
        } else if(button == 2) {
            soundUpDown.play();
            input = -1;
            easeCounter = 100;
        }
    } else if(state == TRUE) {
        if(button == 0) {
            cPlaying = TRUE;
            soundRain.play();
            cMoviePos += 0.2;
            cMovieCounter2 ++;
        } else if(button == 2) {
            cPlaying = FALSE;
            state = FALSE;
            tripped = TRUE;
        }
    }

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    input = 0;
    soundUpUp.stop();
    soundUpDown.stop();
    if((state == FALSE)&&(velocity!=0)) {
        soundDown.play();
    }
    if(fabsf(velocity) > escapeVel2) {
        escapeSwitch = TRUE;
        floorArrayPos ++;
        if(floorArrayPos > 3) floorArrayPos = 0;
        absTarget2 = floorArray[floorArrayPos];
        target2 = absTarget2+round((position+velocity*100)/4)*4;
        velInit = velocity;
        distanceTo = target2-position;
        framesInit = (2*distanceTo)/velInit;
        easeCounter2 = 0;
        cout << " distanceTo " << distanceTo << " target2 " << target2 << " framesInit " << framesInit;
        soundFloor.stop();
        cout << absTarget2;
        if(absTarget2 == -1) {
            soundFloor = soundFloorA;
            soundFloor.play();
        } else if(absTarget2 == 0) {
            soundFloor = soundFloorB;
            soundFloor.play();
        } else if(absTarget2 == 1) {
            soundFloor = soundFloorC;
            soundFloor.play();
        } else if(absTarget2 == 2) {
            soundFloor = soundFloorD;
            soundFloor.play();
        }
        soundFloor.play();
    }
    
//    if(absTarget2 == 2) {
//        dMovie.loadMovie("movies/3ktestcompD.mov");
//        dMovie.play();
//        dPerspective = FALSE;
//    } else {
//        dMovie.loadMovie("movies/3ktestcompD2.mov");
//        dMovie.play();
//        dPerspective = TRUE;
//    }

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


