#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // this number describes how many bins are used
    // on my machine, 2 is the ideal number (2^2 = 4x4 pixel bins)
    // if this number is too high, binning is not effective
    // because the screen is not subdivided enough. if
    // it's too low, the bins take up so much memory as to
    // become inefficient.
    int binPower = 4;

    particleSystem.setup(ofGetWidth(), ofGetHeight(), binPower);
    
      kParticles = 2;  // change that to 5 for MacBook Pro
      float padding = 0;
      float maxVelocity = .5;
      for(int i = 0; i < kParticles * 1024; i++) {
      float x = ofRandom(padding, ofGetWidth() - padding);
      float y = ofRandom(padding, ofGetHeight() - padding);
      float xv = ofRandom(-maxVelocity, maxVelocity);
      float yv = ofRandom(-maxVelocity, maxVelocity);
      Particle particle(x, y, xv, yv);
      particleSystem.add(particle);
      }
    
    rConColor=gConColor=bConColor=rDotColor=gDotColor=bDotColor=255;
    ofBackground(0, 0, 0);

    timeStep = 1;
    lineOpacity = 0;
    pointOpacity = 255;
    isMousePressed = false;
    slowMotion = false;
    particleNeighborhood = 15;
    particleRepulsion = 1;
    centerAttraction = .01;
    forceRadius = 100;
    forceScale = 10;
    bounceXstart = 0; 
    bounceYstart = 0;
    bounceXend = ofGetWidth(); 
    bounceYend = ofGetHeight();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  particleSystem.setTimeStep(timeStep);
  ofSetColor(rConColor, gConColor, bConColor, aConColor);	
  particleSystem.setupForces();
  glBegin(GL_LINES);
  for(int i = 0; i < particleSystem.size(); i++) {
    Particle& cur = particleSystem[i];
    particleSystem.addRepulsionForce(cur, particleNeighborhood, particleRepulsion);
    //cur.bounceOffWalls(0, 0, ofGetWidth(), ofGetHeight());				
    cur.bounceOffWalls(bounceXstart, bounceYstart, bounceXend, bounceYend);				
    cur.addDampingForce();
  }
  glEnd();
  particleSystem.update();
  ofSetColor(255,255,255,255);
  particleSystem.draw();
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
