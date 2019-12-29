#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetWindowPosition(100, 100);
  ofxPublishOsc("localhost", 9005, "/cursor", p);
  ofxPublishOsc("localhost", 9005, "/fps", &ofGetFrameRate);
  ofxPublishOsc("localhost", 9005, "/rect/x", rectX);
  ofxPublishOsc("localhost", 9005, "/rect/y", rectY);
  ofxPublishOsc("localhost", 9005, "/rect/w", rectW);
  ofxPublishOsc("localhost", 9005, "/rect/h", rectH);
  ofEnableSmoothing();
  glPointSize(3);
}

//--------------------------------------------------------------
void ofApp::update(){
  rectX = ofGetMouseX();
  rectY = ofGetMouseY();
  rectW = 40;
  rectH = 40;
      
  p.x = ofGetMouseX();
  p.y = ofGetMouseY();

}

//--------------------------------------------------------------
void ofApp::draw(){
  ofBackground(255);
  ofSetColor(0);
  ofDrawBitmapString("move mouse here!", 10, 30);

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
