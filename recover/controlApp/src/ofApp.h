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

  ofParameter<bool> cutMotion, mirrorMode, onsetOn, fftView, startFFT;;
  ofParameter<bool> hideMouse, autoSketch, soundSketch, hideTypo;
  ofParameter<float> elasticityMin, elasticityMax, dampingMin, dampingMax;
  ofParameter<float> xSoundSketchMin, xSoundSketchMax,
    ySoundSketchMin, ySoundSketchMax;
  ofParameter<ofColor> color;

  // Old ones
  ofParameter<float> radius;
  ofParameter<glm::vec2> center;
  ofxButton ringButton;
  ofxPanel gui;
  bool bHide;

 private:
  ofPoint p;
  int rectX, rectY, rectW, rectH;
};
