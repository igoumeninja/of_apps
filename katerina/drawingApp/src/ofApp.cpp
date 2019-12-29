// Copyright
#include "ofMain.h"
#include "ofxOscSubscriber.h"


/* launch this and ofxOscPublisherExample */

class ofApp : public ofBaseApp {
 public:
  void setup() {
    ofSetWindowPosition(300, 100);
    ofxSubscribeOsc(9005, "/cursor", p);
    ofxSubscribeOsc(9005, "/fps", fps);
    ofxSubscribeOsc(9005, "/rect/x", rectX);
    ofxSubscribeOsc(9005, "/rect/y", rectY);
    ofxSubscribeOsc(9005, "/rect/w", rectW);
    ofxSubscribeOsc(9005, "/rect/h", rectH);
    ofEnableSmoothing();
    glPointSize(3);
  }
  void update() {
  }
  void draw() {
    ofBackground(0);
    ofSetColor(255);
    ofDrawBitmapString("Publisher fps: " + ofToString(fps), 10, 30);
    ofDrawBitmapString(
        "Subscriber fps: " + ofToString(ofGetFrameRate()), 10, 50);
    ofCircle(p, 3);
    ofDrawRectangle(rectX, rectY, rectW, rectH);
  }

 private:
  ofPoint p;
  float fps;
  int rectX, rectY, rectW, rectH;
  ofRectangle myRect;
};

int main() {
  ofSetupOpenGL(400, 400, OF_WINDOW);
  ofRunApp(new ofApp());
}
