// Copyright 2019 by Aris Bezas
#include "ofApp.h"
void ofApp::setup() {
  ofSetWindowPosition(1700, 0);
  ofEnableSmoothing();
  //  glPointSize(3);

  gui.setup("panel");
  gui.add(mirrorMode.set("MirrorMode", false));
  gui.add(cutMotion.set("CutMotion", false));
  gui.add(autoSketch.set("autoSketch", false));
  gui.add(soundSketch.set("soundSketch", false));
  gui.add(hideTypo.set("Typo", false));
  gui.add(elasticityMin.set("elasticityMin", 0.01, 0.01, 0.99));
  gui.add(elasticityMax.set("elasticityMax", 0.01, 0.01, 0.99));
  gui.add(dampingMin.set("dampingMin", 0.01, 0.01, 0.99));
  gui.add(dampingMax.set("dampingMax", 0.01, 0.01, 0.99));
  gui.add(color.set("color", ofColor(100, 100, 140), ofColor(0, 0),
                    ofColor(255, 255)));
  gui.loadFromFile("settings.xml");

  ofxPublishOsc("localhost", 9005, "/mirrorMode", mirrorMode);
  ofxPublishOsc("localhost", 9005, "/cutMotion", cutMotion);
  ofxPublishOsc("localhost", 9005, "/soundSketch", soundSketch);
  ofxPublishOsc("localhost", 9005, "/autoSketch", autoSketch);
  ofxPublishOsc("localhost", 9005, "/hideTypo", hideTypo);
  ofxPublishOsc("localhost", 9005, "/elasticityMin", elasticityMin);
  ofxPublishOsc("localhost", 9005, "/elasticityMax", elasticityMax);
  ofxPublishOsc("localhost", 9005, "/dampingMin", dampingMin);
  ofxPublishOsc("localhost", 9005, "/dampingMax", dampingMax);
  ofxPublishOsc("localhost", 9005, "/cursor", p);
  ofxPublishOsc("localhost", 9005, "/color", color);
  bHide = false;
}
void ofApp::update() {
  if (hideMouse) {
    p.x = ofGetMouseX();
    p.y = ofGetMouseY();
  }
}
void ofApp::draw() {
  ofBackground(color);

  if (!bHide) {
    gui.draw();
  }
}
void ofApp::keyPressed(int key) {
  if (key == 'm') {
    hideMouse = !hideMouse;
  }
}
void ofApp::keyReleased(int key) {}
void ofApp::mouseMoved(int x, int y ) {}
void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mousePressed(int x, int y, int button) {}
void ofApp::mouseReleased(int x, int y, int button) {}
void ofApp::mouseEntered(int x, int y) {}
void ofApp::mouseExited(int x, int y) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::gotMessage(ofMessage msg) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}
