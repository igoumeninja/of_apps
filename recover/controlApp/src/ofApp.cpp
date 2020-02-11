// Copyright 2019 by Aris Bezas
#include "ofApp.h"
void ofApp::setup() {
  //- Global
    ofSetWindowPosition(1700, 0);
    ofEnableSmoothing();
    gui.setup("panel");
  // --GUI--
  //- FFT
    gui.add(startFFT.set("startFFT", false));
    gui.add(fftView.set("fftView", false));
  //- Particles
    gui.add(particleView.set("Particles", false));
  //- Mirror Modes
    gui.add(mirrorMode.set("MirrorMode", false));
  //- Typography
    gui.add(hideTypo.set("Typo", false));
    gui.add(typoParticleMode.set("typoParticleMode", 1, 0, 4));
    // Typo Tasks
      gui.add(letterTask.set("letterTask", false));
      gui.add(letterTask2.set("letterTask2", false));
  //- Images
    gui.add(imageTask.set("imageTask", false));
  //- Sound
    // Onset
      gui.add(sendOnsets.set("sendOnsets", false));
      gui.add(onsetOn.set("onsetOn", false));
    // Sound Sketches
      gui.add(sendAmpFreq.set("sendAmpFreq", false));
      gui.add(soundSketch.set("soundSketch", false));
      gui.add(elasticityMin.set("elasticityMin", 0.01, 0.01, 0.99));
      gui.add(elasticityMax.set("elasticityMax", 0.01, 0.01, 0.99));
      gui.add(dampingMin.set("dampingMin", 0.01, 0.01, 0.99));
      gui.add(dampingMax.set("dampingMax", 0.01, 0.01, 0.99));
      gui.add(xSoundSketchMin.set("xSoundSketchMin", 0.01, 0.01, 0.99));
      gui.add(xSoundSketchMax.set("xSoundSketchMax", 0.01, 0.01, 0.99));
      gui.add(ySoundSketchMin.set("ySoundSketchMin", 0.01, 0.01, 1000.99));
      gui.add(ySoundSketchMax.set("ySoundSketchMax", 0.01, 0.01, 100000.99));
  //- Auto Sketch
      gui.add(autoSketch.set("autoSketch", false));
  //- Background Color
      gui.add(color.set("color", ofColor(100, 100, 140), ofColor(0, 0),
                        ofColor(255, 255)));
  //- Load Settings
      gui.loadFromFile("settings.xml");
  // --OSC--
  //- FFT
    ofxPublishOsc("localhost", 46100, "/startFFT", startFFT);
    ofxPublishOsc("localhost", 9005, "/fftView", fftView);
  //- Particles
  //- Mirror Mode
    ofxPublishOsc("localhost", 9005, "/mirrorMode", mirrorMode);
  //- Typography
    ofxPublishOsc("localhost", 9005, "/hideTypo", hideTypo);
    ofxPublishOsc("localhost", 12345, "/typoParticleMode", typoParticleMode);
    ofxPublishOsc("localhost", 46100, "/letterTask", letterTask);
    ofxPublishOsc("localhost", 46100, "/letterTask2", letterTask2);
  //- Images
    ofxPublishOsc("localhost", 46100, "/imageTask", imageTask);
  //- Sound
    ofxPublishOsc("localhost", 9005, "/onsetOn", onsetOn);
    ofxPublishOsc("localhost", 46100, "/sendOnsets", sendOnsets);

    ofxPublishOsc("localhost", 46100, "/sendAmpFreq", sendAmpFreq);
    ofxPublishOsc("localhost", 9005, "/soundSketch", soundSketch);
    ofxPublishOsc("localhost", 9005, "/elasticityMin", elasticityMin);
    ofxPublishOsc("localhost", 9005, "/elasticityMax", elasticityMax);
    ofxPublishOsc("localhost", 9005, "/dampingMin", dampingMin);
    ofxPublishOsc("localhost", 9005, "/dampingMax", dampingMax);
    ofxPublishOsc("localhost", 9005, "/soundSketch/xMin", xSoundSketchMin);
    ofxPublishOsc("localhost", 9005, "/soundSketch/xMax", xSoundSketchMax);
    ofxPublishOsc("localhost", 9005, "/soundSketch/yMin", ySoundSketchMin);
    ofxPublishOsc("localhost", 9005, "/soundSketch/yMax", ySoundSketchMax);
  //- Auto Sketch
    ofxPublishOsc("localhost", 9005, "/autoSketch", autoSketch);
  //- Background Color
    ofxPublishOsc("localhost", 9005, "/color", color);
  //- END
    }
void ofApp::draw() {
  //- GUI Draw
    ofBackground(0);
    gui.draw();
    }

