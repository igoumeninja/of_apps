//  Copyright 2019
#pragma once

#include "ofMain.h"
#include "ofxOscSubscriber.h"
#include "ofSketch.h"
#include <vector>

#define PORT 12345
#define NUM_MSG_STRINGS 20

class ofApp : public ofBaseApp{
 public:
  // the voids
    void setup();
    void update();
    void draw();
  // OSC
    ofxOscReceiver receiver;
    int currentMsgString;
    string msgStrings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];
  // FFT
    float *fft;
    int bands;
  // Booleans
    bool fillBackground, autoSketch, autoSketchOld,
      hideTypo, hideTypoOld, fftView, fftPolyline;
    bool cutMotion, mirrorMode, onsetOn;
    bool soundSketch, soundSketchOld;
  // Soundsketch
    float xSoundSketch, ySoundSketch;
  // Textures
    ofTexture  fftTexture;
    ofTexture textureScreen;
  // sketch
    ofSketch sketch[2048];
    float elasticityMin;
    float elasticityMax;
    float dampingMin;
    float dampingMax;
    float xSoundSketchMin, xSoundSketchMax, ySoundSketchMin, ySoundSketchMax;
    ofNode baseNode;
    ofNode childNode;
    ofNode grandChildNode;
    ofPolyline line;
    ofEasyCam cam;
  // typo particles
    int maxParticles;
    int drawMode;
    ofTrueTypeFont ttf;
  // Colors
    ofColor bg_color;
    ofColor fbo_color;
    ofColor color;
  // Particles
    bool bUpdateDrawMode;
    bool bResetParticles;
    ofFbo fbo;
    ofPixels pix;
  // Images
    ofImage image[200];
};
