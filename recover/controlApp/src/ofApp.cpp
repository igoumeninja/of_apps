// Copyright 2019 by Aris Bezas
#include "ofApp.h"
void ofApp::setup() {
  ofSetWindowPosition(1700, 0);
  ofEnableSmoothing();
  //  glPointSize(3);

  gui.setup("panel");
  gui.add(sendOnsets.set("sendOnsets", false));
  gui.add(sendAmpFreq.set("sendAmpFreq", false));
  gui.add(startFFT.set("startFFT", false));
  gui.add(fftView.set("fftView", false));
  gui.add(mirrorMode.set("MirrorMode", false));
  gui.add(imageTask.set("imageTask", false));
  gui.add(autoSketch.set("autoSketch", false));
  gui.add(soundSketch.set("soundSketch", false));
  gui.add(onsetOn.set("onsetOn", false));
  gui.add(hideTypo.set("Typo", false));
  gui.add(elasticityMin.set("elasticityMin", 0.01, 0.01, 0.99));
  gui.add(elasticityMax.set("elasticityMax", 0.01, 0.01, 0.99));
  gui.add(dampingMin.set("dampingMin", 0.01, 0.01, 0.99));
  gui.add(dampingMax.set("dampingMax", 0.01, 0.01, 0.99));
  gui.add(xSoundSketchMin.set("xSoundSketchMin", 0.01, 0.01, 0.99));
  gui.add(xSoundSketchMax.set("xSoundSketchMax", 0.01, 0.01, 0.99));
  gui.add(ySoundSketchMin.set("ySoundSketchMin", 0.01, 0.01, 1000.99));
  gui.add(ySoundSketchMax.set("ySoundSketchMax", 0.01, 0.01, 100000.99));
  gui.add(color.set("color", ofColor(100, 100, 140), ofColor(0, 0),
                    ofColor(255, 255)));

  gui.loadFromFile("settings.xml");

  ofxPublishOsc("localhost", 57120, "/imageTask", imageTask);
  ofxPublishOsc("localhost", 57120, "/sendOnsets", sendOnsets);
  ofxPublishOsc("localhost", 57120, "/sendAmpFreq", sendAmpFreq);
  ofxPublishOsc("localhost", 57120, "/startFFT", startFFT);
  ofxPublishOsc("localhost", 9005, "/fftView", fftView);
  ofxPublishOsc("localhost", 9005, "/onsetOn", onsetOn);
  ofxPublishOsc("localhost", 9005, "/mirrorMode", mirrorMode);
  ofxPublishOsc("localhost", 9005, "/soundSketch", soundSketch);
  ofxPublishOsc("localhost", 9005, "/autoSketch", autoSketch);
  ofxPublishOsc("localhost", 9005, "/hideTypo", hideTypo);
  ofxPublishOsc("localhost", 9005, "/elasticityMin", elasticityMin);
  ofxPublishOsc("localhost", 9005, "/elasticityMax", elasticityMax);
  ofxPublishOsc("localhost", 9005, "/dampingMin", dampingMin);
  ofxPublishOsc("localhost", 9005, "/dampingMax", dampingMax);
  ofxPublishOsc("localhost", 9005, "/soundSketch/xMin", xSoundSketchMin);
  ofxPublishOsc("localhost", 9005, "/soundSketch/xMax", xSoundSketchMax);
  ofxPublishOsc("localhost", 9005, "/soundSketch/yMin", ySoundSketchMin);
  ofxPublishOsc("localhost", 9005, "/soundSketch/yMax", ySoundSketchMax);
  ofxPublishOsc("localhost", 9005, "/cursor", p);
  ofxPublishOsc("localhost", 9005, "/color", color);
}
void ofApp::update() {}
void ofApp::draw() {
  ofBackground(color);
  gui.draw();
}
void ofApp::keyPressed(int key) {}
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
