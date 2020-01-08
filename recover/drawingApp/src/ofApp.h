#pragma once

#include "ofMain.h"
#include "ofxOscSubscriber.h"
#include "Particle.h"

class ofApp : public ofBaseApp{

 public:
  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y );
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

  int maxParticles;
  int drawMode;
  
  ofColor bg_color;
  ofColor fbo_color;

  bool bUpdateDrawMode;
  bool bResetParticles;

  ofFbo fbo;
  ofPixels pix;

  vector <Particle *> particles;
		
 private:
  ofColor color;
  float rectSize;
  ofPoint p;
  float fps;
  int rectX, rectY, rectW, rectH;
  ofRectangle myRect;
};
