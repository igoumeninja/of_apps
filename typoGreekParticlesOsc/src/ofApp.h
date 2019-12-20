#pragma once

#include "ofMain.h"

#include "Particle.h"
#include "ofxOsc.h"

// send host (aka ip address)
#define HOST "localhost"

/// send port
#define PORT 57120


class ofApp : public ofBaseApp{
  
public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);
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

  ofxOscSender sender;
};
