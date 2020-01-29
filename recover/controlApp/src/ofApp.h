// Copyright
#pragma once

#include "ofMain.h"
#include "ofxOscPublisher.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
 public:
  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);

  ofParameter<bool> imageTask, mirrorMode, onsetOn, sendOnsets,
    fftView, startFFT, sendAmpFreq, hideMouse, autoSketch, soundSketch,
    hideTypo;
  ofParameter<float> elasticityMin, elasticityMax, dampingMin, dampingMax,
    xSoundSketchMin, xSoundSketchMax, ySoundSketchMin, ySoundSketchMax;
  ofParameter<ofColor> color;

  ofxPanel gui;

 private:
  ofPoint p;
};
