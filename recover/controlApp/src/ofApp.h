// Copyright
#pragma once

#include "ofMain.h"
#include "ofxOscPublisher.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
 public:
  void setup();
  void draw();

  ofParameter<bool> letterTask2, letterTask, imageTask, mirrorMode, onsetOn, sendOnsets,
    fftView, startFFT, sendAmpFreq, hideMouse, autoSketch, soundSketch,
    hideTypo;
  ofParameter<float> elasticityMin, elasticityMax, dampingMin, dampingMax,
    xSoundSketchMin, xSoundSketchMax, ySoundSketchMin, ySoundSketchMax;

  ofParameter<int> typoParticleMode;
  ofParameter<ofColor> color;

  ofxPanel gui;

 private:
  ofPoint p;
};
