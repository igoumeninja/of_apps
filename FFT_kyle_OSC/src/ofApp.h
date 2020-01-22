#pragma once

#include "ofMain.h"
#include "ofxFft.h"
#include "ofxOsc.h"

// send host (aka ip address)
#define HOST "localhost"

/// send port
#define PORT 12345

enum {SINE, MIC, NOISE};

class ofApp : public ofBaseApp {
 public:
  void setup();
  void plot(vector<float>& buffer, float scale, float offset);
  void audioReceived(float* input, int bufferSize, int nChannels);
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

  ofTrueTypeFont font;
  ofxOscSender sender;
  ofBuffer imgAsBuffer;
  ofImage img; 
  int plotHeight, bufferSize;

  ofxFft* fft;
	
  int spectrogramOffset;
  ofImage spectrogram;
  int mode;
	
  int appWidth, appHeight;
	
  ofMutex soundMutex;
  vector<float> drawBins, middleBins, audioBins;
  vector<float> drawBuffer, middleBuffer, audioBuffer;
};
