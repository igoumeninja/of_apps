//  Copyright 2019
#pragma once

#include "ofxOscSubscriber.h"
#include "Particle.h"
#include "ofSketch.h"
#include <vector>

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

  void updateDrawMode();
  void resetParticles();

  void audioIn(ofSoundBuffer & input);
  vector <float> left;
  vector <float> right;
  vector <float> volHistory;
  int bufferCounter;
  int drawCounter;
  float smoothedVol;
  float scaledVol;
  ofSoundStream soundStream;

  ofSoundPlayer sound;
  float *fft;
  float *soundSpectrum;
  int bands;
  ofTexture  fftTexture;

  bool fillBackground, autoSketch, autoSketchOld,
    hideTypo, hideTypoOld, fftView, fftPolyline;
  bool cutMotion, mirrorMode, onsetOn;
  bool soundSketch, soundSketchOld;
  float xSoundSketch, ySoundSketch;

  ofTexture textureScreen;
  // sketch
  ofSketch sketch[2048];
  float elasticityMin;
  float elasticityMax;
  float dampingMin;
  float dampingMax;

  ofNode baseNode;
  ofNode childNode;
  ofNode grandChildNode;
  ofPolyline line;
  ofEasyCam cam;

  // typo particles
  int maxParticles;
  int drawMode;

  ofColor bg_color;
  ofColor fbo_color;

  bool bUpdateDrawMode;
  bool bResetParticles;

  ofFbo fbo;
  ofPixels pix;

  vector <Particle *> particles;

  // Images
  ofImage image[200];

 private:
  ofColor color;
  float rectSize;
  ofPoint p;
  float fps;
  int rectX, rectY, rectW, rectH;
  ofRectangle myRect;
};
