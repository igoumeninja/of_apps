#pragma once

#include "ofMain.h"

#include "Particle.h"

#define PORT 12345
#define NUM_MSG_STRINGS 20

class ofApp : public ofBaseApp{
  
public:
  void setup();
  void update();
  void draw();
  void updateDrawMode();
  void resetParticles();
  
  void mousePressed(int x, int y, int button);

  int maxParticles;
  int drawMode;
  
  ofColor bg_color;
  ofColor fbo_color;

  bool bUpdateDrawMode;
  bool bResetParticles;

  ofFbo fbo;
  ofPixels pix;

  vector <Particle *> particles;
};
