// Copyright 2019 by Aris Bezas
#include "ofApp.h"
void ofApp::setup() {
  // Global
    ofSetWindowPosition(1700, 0);
    ofEnableSmoothing();
  // GUI
    gui.setup("panel");
    gui.add(startFFT.set("startFFT", false));
    gui.add(fftView.set("fftView", false));
    gui.add(mirrorMode.set("MirrorMode", false));
    gui.add(hideTypo.set("Typo", false));
    gui.add(typoParticleMode.set("typoParticleMode", 1, 0, 4));
    gui.add(letterTask.set("letterTask", false));
    gui.add(letterTask2.set("letterTask2", false));
    gui.add(imageTask.set("imageTask", false));
    gui.add(sendOnsets.set("sendOnsets", false));
    gui.add(onsetOn.set("onsetOn", false));
    gui.add(autoSketch.set("autoSketch", false));
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
    gui.add(color.set("color", ofColor(100, 100, 140), ofColor(0, 0),
                    ofColor(255, 255)));
    gui.loadFromFile("settings.xml");
  // OSC
    ofxPublishOsc("localhost", 46100, "/letterTask", letterTask);
    ofxPublishOsc("localhost", 46100, "/letterTask2", letterTask2);
    ofxPublishOsc("localhost", 46100, "/imageTask", imageTask);
    ofxPublishOsc("localhost", 46100, "/sendOnsets", sendOnsets);
    ofxPublishOsc("localhost", 46100, "/sendAmpFreq", sendAmpFreq);
    ofxPublishOsc("localhost", 46100, "/startFFT", startFFT);
    ofxPublishOsc("localhost", 9005, "/fftView", fftView);
    ofxPublishOsc("localhost", 9005, "/onsetOn", onsetOn);
    ofxPublishOsc("localhost", 9005, "/mirrorMode", mirrorMode);
    ofxPublishOsc("localhost", 9005, "/soundSketch", soundSketch);
    ofxPublishOsc("localhost", 9005, "/autoSketch", autoSketch);
    ofxPublishOsc("localhost", 9005, "/hideTypo", hideTypo);
    ofxPublishOsc("localhost", 12345, "/typoParticleMode", typoParticleMode);
    ofxPublishOsc("localhost", 9005, "/elasticityMin", elasticityMin);
    ofxPublishOsc("localhost", 9005, "/elasticityMax", elasticityMax);
    ofxPublishOsc("localhost", 9005, "/dampingMin", dampingMin);
    ofxPublishOsc("localhost", 9005, "/dampingMax", dampingMax);
    ofxPublishOsc("localhost", 9005, "/soundSketch/xMin", xSoundSketchMin);
    ofxPublishOsc("localhost", 9005, "/soundSketch/xMax", xSoundSketchMax);
    ofxPublishOsc("localhost", 9005, "/soundSketch/yMin", ySoundSketchMin);
    ofxPublishOsc("localhost", 9005, "/soundSketch/yMax", ySoundSketchMax);
    ofxPublishOsc("localhost", 9005, "/cursor", p);
    ofxPublishOsc("localhost", 9005, "/color", color);
    }
void ofApp::draw() {
  ofBackground(0);
  gui.draw();
  }

