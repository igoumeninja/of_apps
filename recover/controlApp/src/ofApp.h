//- Copyright and #include
  #pragma once

  #include "ofMain.h"
  #include "ofxOscPublisher.h"
  #include "ofxGui.h"
class ofApp : public ofBaseApp{
 public:
  void setup();
  void draw();
  //- Booleans
    ofParameter<bool> letterTask2, letterTask, imageTask, mirrorMode, onsetOn,
      sendOnsets, fftView, startFFT, sendAmpFreq, hideMouse, autoSketch,
      soundSketch, hideTypo, particleView;
  //- Floats
    ofParameter<float> elasticityMin, elasticityMax, dampingMin, dampingMax,
      xSoundSketchMin, xSoundSketchMax, ySoundSketchMin, ySoundSketchMax;
  //- Integers
    ofParameter<int> typoParticleMode;
  //- Colors
    ofParameter<ofColor> color;
  ofxPanel gui;
};
