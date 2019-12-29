// Copyright 2019
#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup() {
  ofSetWindowPosition(100, 100);

  gui.setup("panel");
  gui.add(rectSize.set("rectSize", 10, 10, 990));
  gui.add(hideMouse.set("hideMouse", false));
  gui.add(elasticityMin.set("elasticityMin", 0.01, 0.01, 0.99));
  gui.add(elasticityMax.set("elasticityMax", 0.01, 0.01, 0.99));
  gui.add(dampingMin.set("dampingMin", 0.01, 0.01, 0.99));
  gui.add(dampingMax.set("dampingMax", 0.01, 0.01, 0.99));
  gui.add(filled.set("bFill", true));
  gui.add(radius.set("radius", 140, 10, 300));
  gui.add(center.set("center",
                     glm::vec2(ofGetWidth()*.5,
                               ofGetHeight()*.5),
                     glm::vec2(0, 0),
                     glm::vec2(ofGetWidth(), ofGetHeight())));
  gui.add(color.set("color", ofColor(100, 100, 140),
                    ofColor(0, 0), ofColor(255, 255)));
  gui.add(circleResolution.set("circleRes", 5, 3, 90));
  gui.add(ringButton.setup("ring"));
  gui.add(screenSize.set("screenSize", ""));

  gui.loadFromFile("settings.xml");
  bHide = false;
  
  ofxPublishOsc("localhost", 9005, "/rectSize", rectSize);
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
void ofApp::update() {
  rectX = ofGetMouseX();
  rectY = ofGetMouseY();
  rectW = 40;
  rectH = 40;
  if (hideMouse) {
    p.x = ofGetMouseX();
    p.y = ofGetMouseY();
  }
}

//--------------------------------------------------------------
void ofApp::draw(){

  ofBackground(255);

  if( !bHide ){
    gui.draw();
  }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (key == 'm'){
    hideMouse = !hideMouse;
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
