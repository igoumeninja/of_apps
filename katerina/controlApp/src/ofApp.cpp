#include "ofMain.h"
#include "ofxOscPublisher.h"

/* launch this and ofxOscSubscriberExample */

class ofApp : public ofBaseApp {
public:
    void setup() {

        ofSetWindowPosition(100, 100);
        ofxPublishOsc("localhost", 9005, "/cursor", p);
        ofxPublishOsc("localhost", 9005, "/fps", &ofGetFrameRate);
        ofxPublishOsc("localhost", 9005, "/rect/x", rectX);
        ofxPublishOsc("localhost", 9005, "/rect/y", rectY);
        ofxPublishOsc("localhost", 9005, "/rect/w", rectW);
        ofxPublishOsc("localhost", 9005, "/rect/h", rectH);
        ofEnableSmoothing();
        glPointSize(3);
    }
    
    void update() {
      rectX = ofGetMouseX();
      rectY = ofGetMouseY();
      rectW = 400;
      rectH = 400;
      
      p.x = ofGetMouseX();
        p.y = ofGetMouseY();
    }
    void draw() {
        ofBackground(255);
        ofSetColor(0);
        ofDrawBitmapString("move mouse here!", 10, 30);

    }
    
private:
  ofPoint p;
  int rectX,rectY,rectW,rectH;
};

int main() {
    ofSetupOpenGL(200, 200, OF_WINDOW);
    ofRunApp(new ofApp());
}
