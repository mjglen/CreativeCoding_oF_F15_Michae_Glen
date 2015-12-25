#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofBackground(0, 0);
    forceOne = false;
    forceTwo = false;
    forceThree = false;
    forceFour = false;
    forceFive = false;
    forceSix = false;
    oVec.zero();
    oVec.z = 180;
    oVec.y = 0;
    vid.loadMovie("RENDERCOMP.mov");
    vid.setLoopState(OF_LOOP_PALINDROME);
    vid.play();
    ofDisableArbTex(); // we need GL_TEXTURE_2D for our models coords.
    
    //frame.allocate(1280,960,GL_RGB);
    vidTexture.allocate(1280,960,GL_RGB);
    vidPlane.setResolution(32,16);
    vidPlane.set(1280,960);
    vidPlane.setPosition(500,300,0);
    
    

    bAnimate = false;
    bAnimateMouse = false;
    animationPosition = 0;
    nullVec.zero();
    attractScalar = 0.01;
    sphereScalar = 0.1;
    
    model.loadModel("cora/cora.dae", true);
    model.setPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75 , 0);
    
    model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    model.playAllAnimations();
    if(!bAnimate) {
        model.setPausedForAllAnimations(true);
    }
    model.setScale(1,1,1);
    model.setPosition(500,300,-100);
    sfear.setRadius(50);
    mesh = model.getCurrentAnimatedMesh(0);
    planeMesh = vidPlane.getMesh();
    
    for(int i=0; i<mesh.getNumVertices(); i++) {
        ofVec3f tempVec;
        tempVec = mesh.getVertex(i);
        meshPos.push_back(tempVec);

        tempVec = tempVec/100;
        meshVel.push_back(tempVec);
        meshAcc.push_back(nullVec);
        }
    
    for(int i=0; i<planeMesh.getNumVertices(); i++) {
        ofVec3f tempVec;
        tempVec = planeMesh.getVertex(i);
        //tempVec.x += tempVec.x/(tempVec.x-i);
        tempVec.x += 500;
        tempVec.y += 300;
        tempVec.z -= 300;
        planeMeshPos.push_back(tempVec);
        
        tempVec = tempVec/100;
        planeMeshVel.push_back(tempVec);
        planeMeshAcc.push_back(nullVec);
    }
    

    attractMesh = meshPos;
    planeAttractMesh = planeMeshPos;
    particles = meshPos;
    pVel = meshVel;
    pAcc = meshAcc;
    spherePos.zero();
    spherePos2.zero();
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
        vidPlane.setPosition(-500,300,0);
    vid.update();
    
        
        ofVec3f tempVec2;
        tempVec2 = spherePos-spherePos2;
        tempVec2 = tempVec2.normalize();
        tempVec2.x += ofRandom(0,0.1);
        tempVec2.y += ofRandom(0,0.1);
        tempVec2.z += ofRandom(0,0.1);
        spherePos2 += tempVec2*sphereScalar*5;


//    model.update();
//    model.setRotation(1, 270 + ofGetElapsedTimef() * 6, 0, .1, 0);
    //mesh = model.getCurrentAnimatedMesh(3);

    
//    for(int i=0; i<mesh.getNumVertices(); i++) {
//        meshAcc[i].zero();
//        pAcc[i].zero();
// 
//            ofVec3f tempVec;
//            tempVec = (meshPos[i]-attractMesh[i])*-1;
//            //tempVec = (meshPos[i]-nullVec)*-1;
//            tempVec = tempVec.normalize();
//            meshAcc[i] = tempVec*attractScalar;
//            tempVec = (particles[i]-meshPos[i])*-1;
//            tempVec = tempVec.normalize();
//            pAcc[i] = tempVec*attractScalar;
//       
//        
//        if(meshPos[i].squareDistance(spherePos)<100) {
//            //cout << spherePos << "  ";
//            
//            ofVec3f tempVec;
//            tempVec = meshPos[i]-spherePos;
//            tempVec = tempVec.normalize();
//            meshAcc[i] += tempVec*sphereScalar;
//            //pAcc[i] += tempVec*sphereScalar;
//        }
//        
//    }
//    
//    for(int i=0; i<mesh.getNumVertices(); i++) {
//        meshVel[i] = meshVel[i]*0.8;
//        pVel[i] = pVel[i]*0.95;
//
//        meshVel[i] += meshAcc[i];
//        pVel[i] += pAcc[i];
//        if((meshPos[i].squareDistance(attractMesh[i])<0.0001)&&(meshAcc[i].x == 0)) {
//        meshVel[i].x = 0;
//        meshVel[i].y = 0;
//        meshVel[i].z = 0;
//        }
//        meshPos[i] += meshVel[i];
//        particles[i] += pVel[i];
//    }
//    for(int i=0; i<mesh.getNumVertices(); i++) {
//        mesh.setVertex(i,meshPos[i]);
//    }
    
    for(int i=0; i<planeMesh.getNumVertices(); i++) {
        planeMeshAcc[i].zero();
        
        ofVec3f tempVec;
        tempVec = (planeMeshPos[i]-planeAttractMesh[i])*-1;
        //tempVec = (meshPos[i]-nullVec)*-1;
        tempVec = tempVec.normalize();
        planeMeshAcc[i] = tempVec*attractScalar*10;
        
        
        if(planeMeshPos[i].squareDistance(spherePos2)<100000) {
            //cout << spherePos << "  ";
            
            ofVec3f tempVec;
            tempVec = planeMeshPos[i]-spherePos2;
            tempVec = tempVec.normalize();
            tempVec.x += ofRandom(0,0.1);
            tempVec.y += ofRandom(0,0.1);
            tempVec.z += ofRandom(0,0.1);
            planeMeshAcc[i] += tempVec*sphereScalar*5;
        }
        
        if(forceOne==TRUE && (i<32*2)) {
            planeMeshAcc[i].z += 0.5;
            spherePos2.x++;
        }
        
        if(forceTwo==TRUE && ((i>32*2)&&(i<32*4))) {
            //planeMeshAcc[i].z += 0.5;
            planeMeshAcc[i] += (planeMeshPos[i]-planeMeshPos[i+1])*-0.0115;
            planeMeshAcc[i] += (planeMeshPos[i]-planeMeshPos[i-1])*-0.0115;
            if(i>32) planeMeshAcc[i] += (planeMeshPos[i]-planeMeshPos[i-32])*-0.0115;
            if(i<32*15) planeMeshAcc[i] += (planeMeshPos[i]-planeMeshPos[i+32])*-0.0115;
        }
        
        if(forceThree==TRUE && ((i>32*4)&&(i<32*6))) {
            planeMeshAcc[i].z += 0.5;
            spherePos2.y ++;
        }
        
        if(forceFour==TRUE && ((i>32*6)&&(i<32*8))) {
            planeMeshAcc[i].z += 0.5;
            spherePos2.x--;
        }
        
        if(forceFive==TRUE && ((i>32*8)&&(i<32*10))) {
            planeMeshAcc[i].z += 0.5;
            spherePos2.y --;
        }
        
        if(forceSix==TRUE && ((i>32*10)&&(i<32*12))) {
            planeMeshAcc[i].z += 0.5;
        }
        
       planeMeshAcc[i] += (planeMeshPos[i]-planeMeshPos[i+1])*-0.0015;
       planeMeshAcc[i] += (planeMeshPos[i]-planeMeshPos[i-1])*-0.0015;
        if(i>32) planeMeshAcc[i] += (planeMeshPos[i]-planeMeshPos[i-32])*-0.0015;
        if(i<32*15) planeMeshAcc[i] += (planeMeshPos[i]-planeMeshPos[i+32])*-0.0015;
        
    }
    
    for(int i=0; i<planeMesh.getNumVertices(); i++) {
        planeMeshVel[i] = planeMeshVel[i]*0.8;
        //planeMeshAcc[i] += planeMeshAcc[i]+1;
        planeMeshVel[i] += planeMeshAcc[i];
//        if((planeMeshPos[i].squareDistance(planeAttractMesh[i])<0.0001)&&(planeMeshAcc[i].x == 0)) {
//            planeMeshVel[i].x = 0;
//            planeMeshVel[i].y = 0;
//            planeMeshVel[i].z = 0;
//        }
        planeMeshPos[i] += planeMeshVel[i];
    }
    for(int i=0; i<planeMesh.getNumVertices(); i++) {
        planeMesh.setVertex(i,planeMeshPos[i]);
    }
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    //unsigned char * pixels = frame.getPixels();
    //frame = vid.getPixels();
    vidTexture.loadData(vid.getPixels(),1280,960,GL_RGB);
    
    //vid.draw(0,0);
    ofSetColor(255);
    cam2.setPosition(400, 500, 500);
    cam2.setOrientation(oVec);

    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnableDepthTest();
    
    glShadeModel(GL_SMOOTH); //some model / light stuff
    light.enable(); // lighting
    ofEnableSeparateSpecularLight(); //lighting

//    ofPushMatrix(); //push in to model transorm context
//    ofTranslate(model.getPosition().x+100, model.getPosition().y, 0); //center model
//    ofRotate(-mouseX, 0, 1, 0);
//    ofTranslate(-model.getPosition().x, -model.getPosition().y, 0);
//    model.drawFaces(); // draw the faces of the model
//    ofPopMatrix();

   if(ofGetGLProgrammableRenderer()){
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
    }
    glEnable(GL_NORMALIZE); //normalizes normals?
    cam2.begin();
    vidTexture.bind();
        //vidPlane.draw();
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetColor(255,200,200,255);
    glPointSize(5);
    glLineWidth(2);
    ofPushMatrix();
    ofScale(0.5,0.5);
    ofTranslate(500,500,1);
    //planeMesh.drawVertices();
    ofScale(1,-1);
    ofTranslate(0,100,1);
    //planeMesh.drawVertices();
    ofRotateZ(90);
    ofTranslate(-500,-400,1);
    //planeMesh.drawVertices();
    ofScale(1,-1);
//    ofRotateZ(90);
//    planeMesh.drawVertices();
    planeMesh.drawWireframe();
    for(int i=0; i<15; i++) {
    ofRotateZ(360/16);
    ofTranslate(0,0,2);
    planeMesh.drawWireframe();
    }
    ofPopMatrix();
    ofPopStyle();
    
    ofPushMatrix();
    
    ofxAssimpMeshHelper & meshHelper = model.getMeshHelper(0);
    
    ofMultMatrix(model.getModelMatrix());
    ofMultMatrix(meshHelper.matrix);
    
    ofMaterial & material = meshHelper.material;
    if(meshHelper.hasTexture()){
        meshHelper.getTextureRef().bind();
    }
    material.setSpecularColor(0.3);
    material.begin();
    
    //mesh.drawWireframe();
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetColor(255,120,120,255);
    //mesh.drawFaces();
    material.setDiffuseColor(1);
//    for(int i=0; i<mesh.getNumVertices(); i++) {
//        ofCircle(particles[i],(particles[i].squareDistance(meshPos[i])/10));
//    }
//    for(int i=0; i<planeMesh.getNumVertices(); i++) {
//        ofCircle(planeMesh.getVertex(i),2);
//    }
    ofPopStyle();
    material.end();
    if(meshHelper.hasTexture()){
        meshHelper.getTextureRef().unbind();
    }
    ofPopMatrix(); //push out of wireframe

    if(ofGetGLProgrammableRenderer()){
    	glPopAttrib();
    }
    
    //sfear.draw();
    
    ofDisableDepthTest();
    light.disable();
    ofDisableLighting();
    ofDisableSeparateSpecularLight();
    cam2.end();
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    ofPoint modelPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75);

	mesh = model.getMesh(0);
    if(key == 'a') {
        forceOne = TRUE;
        spherePos2.x = (-200+1000);
        spherePos2.y = 0;
    }
    if(key == 's') {
        forceTwo = TRUE;
        spherePos2.x = (-720+1000);
        spherePos2.y = -300;
    }
    if(key == 'd') {
        forceThree = TRUE;
        spherePos2.x = (-300+1000);
        spherePos2.y = -500;
    }
    if(key == 'f') {
        forceFour = TRUE;
        spherePos2.x = (-500+1000);
        spherePos2.y = -500;
    }
    if(key == 'g') {
        forceFive = TRUE;
        spherePos2.x = (-1000+1000);
        spherePos2.y = 0;
    }
    
    if(key == 'w') {
        forceSix = TRUE;
    }
    
    if(key == '7') {
        forceSeven = TRUE;
    }
    
    if(key == '8') {
        forceEight = TRUE;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    //
    if(key == 'a') {
        forceOne = false;
        
    }
    if(key == 's') {
        forceTwo = false;
    }
    if(key == 'd') {
        forceThree = false;
    }
    if(key == 'f') {
        forceFour = false;
    }
    if(key == 'g') {
        forceFive = false;
    }
    
    if(key == 'w') {
        forceSix = false;
    }
    
    if(key == '7') {
        forceSeven = false;
    }
    
    if(key == '8') {
        forceEight = false;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    sfear.setPosition(-x+1000,y,0);
    spherePos.z = -300;
    spherePos.x = 500;
    spherePos.y = -500;
    spherePos2.z = -300;
    spherePos2.x = (-x+1000);
    spherePos2.y = (y);
    //cout << spherePos << "  ";

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    // scrub through aninations manually.
	animationPosition = y / (float)ofGetHeight();
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

