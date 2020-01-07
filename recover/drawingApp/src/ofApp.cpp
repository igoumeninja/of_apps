// Copyright
#include "ofApp.h"
void ofApp::setup() {
  ofSetWindowPosition(300, 100);
  ofxSubscribeOsc(9005, "/color", color);
  ofxSubscribeOsc(9005, "/rectSize", rectSize);
  ofxSubscribeOsc(9005, "/cursor", p);
  ofxSubscribeOsc(9005, "/fps", fps);
  ofxSubscribeOsc(9005, "/rect/x", rectX);
  ofxSubscribeOsc(9005, "/rect/y", rectY);
  ofxSubscribeOsc(9005, "/rect/w", rectW);
  ofxSubscribeOsc(9005, "/rect/h", rectH);
  ofEnableSmoothing();
  glPointSize(3);
}
void ofApp::update() {}
void ofApp::draw() {
  of
  ofBackground(color);
  ofSetColor(255);
  ofDrawBitmapString("Publisher fps: " + ofToString(fps), 10, 30);
  ofDrawBitmapString(C
      "Subscriber fps: " + ofToString(ofGetFrameRate()), 10, 50);
  ofCircle(p, 3);
  ofDrawRectangle(p.x, p.y, rectSize, rectSize);
}
void ofApp::keyPressed(int key) {

}
void ofApp::keyReleased(int key) {

}
void ofApp::mouseMoved(int x, int y ) {

}
void ofApp::mouseDragged(int x, int y, int button) {

}
void ofApp::mousePressed(int x, int y, int button) {

}
void ofApp::mouseReleased(int x, int y, int button) {

}
void ofApp::mouseEntered(int x, int y) {

}
void ofApp::mouseExited(int x, int y) {

}
void ofApp::windowResized(int w, int h) {

}
void ofApp::gotMessage(ofMessage msg) {

}
void ofApp::dragEvent(ofDragInfo dragInfo) { }
