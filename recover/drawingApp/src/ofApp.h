//  Copyright 2019
#pragma once

#include "ofxOscSubscriber.h"
#include "Particle.h"
#include "ofSketch.h"
#include <vector>
// listening port
#define PORT 12345

// max number of strings to display
#define NUM_MSG_STRINGS 20

class ofApp : public ofBaseApp{
 public:
  // the voids
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
    void updateDrawMode();
    void resetParticles();
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
  // Colors
    ofColor bg_color;
    ofColor fbo_color;
    ofColor color;
  // Particles
    bool bUpdateDrawMode;
    bool bResetParticles;
    ofFbo fbo;
    ofPixels pix;
    vector <Particle *> particles;
  // Images
    ofImage image[200];
 private:
  ofPoint p;

};
