#pragma once

#include "ofMain.h"

#include "Particle.h"
#include "ofxOsc.h"

// send host (aka ip address)
#define HOST "localhost"

/// send port
#define PORT_SEND 57120
#define PORT_RECEIVE 12345

// max number of strings to display
#define NUM_MSG_STRINGS 20


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
  ofxOscReceiver receiver;

  int currentMsgString;
  string msgStrings[NUM_MSG_STRINGS];
  float timers[NUM_MSG_STRINGS];
};
