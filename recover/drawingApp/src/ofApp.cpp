// Copyright 2019 Aris Bezas
#include "ofApp.h"
void ofApp::setup() {
  // Global Definition
    ofBackground(0, 0, 0);
    ofSetWindowPosition(0, 0);
    ofEnableSmoothing();
    ofSetBackgroundAuto(false);
    ofEnableAlphaBlending();
    ofSetFrameRate(60);  // if vertical sync is off, we can go faster
    ofSetVerticalSync(false);
    glPointSize(1);
    ofEnableAntiAliasing();
    ofSetFrameRate(60);
    ofSetBackgroundAuto(false);
    // ofEnableDepthTest();
  // Typography - Particles
    //string fontpath = "arial.ttf";
    ofTrueTypeFontSettings settings("arial.ttf", 220);
    settings.antialiased = true;
    settings.addRanges(ofAlphabet::Greek);
    maxParticles = 600;  // the maximum number of active particles
    drawMode = 3;  // move through the drawing modes by clicking the mouse

    bg_color = ofColor(255);
    fbo_color = ofColor(0);

    bUpdateDrawMode = false;
    bResetParticles = true;

    ofBackground(bg_color);
    ttf.loadFont("arial.ttf", 12);
    ttf.load(settings);
    string s = "επιθυμίες";
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    pix.allocate(ofGetWidth(), ofGetHeight(), OF_PIXELS_RGBA);
    fbo.begin();
    ofClear(0, 0, 0, 0);
    ofRectangle r = ttf.getStringBoundingBox(s, 0, 0);
    ofVec2f offset = ofVec2f(floor(-r.x - r.width * 0.5f),
                             floor(-r.y - r.height * 0.5f));
    ofSetColor(fbo_color);
    ttf.drawString(s, fbo.getWidth() / 2 + offset.x,
                   fbo.getHeight() / 2 + offset.y);
    fbo.end();

    fbo.readToPixels(pix);  //  the ofPixels class
  // OSC communication
    receiver.setup(PORT);
    ofxSubscribeOsc(9005, "/fftView", fftView);
    ofxSubscribeOsc(9005, "/mirrorMode", mirrorMode);
    ofxSubscribeOsc(9005, "/soundSketch", soundSketch);
    ofxSubscribeOsc(9005, "/soundSketch/x", xSoundSketch);
    ofxSubscribeOsc(9005, "/soundSketch/y", ySoundSketch);
    ofxSubscribeOsc(9005, "/soundSketch/xMin", xSoundSketchMin);
    ofxSubscribeOsc(9005, "/soundSketch/xMax", xSoundSketchMax);
    ofxSubscribeOsc(9005, "/soundSketch/yMin", ySoundSketchMin);
    ofxSubscribeOsc(9005, "/soundSketch/yMax", ySoundSketchMax);
    ofxSubscribeOsc(9005, "/autoSketch", autoSketch);
    ofxSubscribeOsc(9005, "/hideTypo", hideTypo);
    ofxSubscribeOsc(9005, "/color", color);
    ofxSubscribeOsc(9005, "/elasticityMin", elasticityMin);
    ofxSubscribeOsc(9005, "/elasticityMax", elasticityMax);
    ofxSubscribeOsc(9005, "/dampingMin", dampingMin);
    ofxSubscribeOsc(9005, "/dampingMax", dampingMax);
    ofxSubscribeOsc(9005, "/color", color);
    ofxSubscribeOsc(9005, "/cursor", p);
    ofxSubscribeOsc(9005, "/onsetOn", onsetOn);
    ofxSubscribeOsc(9005, "/drawImage",
                    [&images = image]
                    (vector<int> nums){
                      ofSetColor(255, 255, 255);
                      images[nums[0]].draw(nums[1], nums[2], nums[3], nums[4]);
                    });

    ofxSubscribeOsc(9005, "/onset",
                    [&condition = onsetOn, &images = image](){
                      if (condition) {
                        // ofBackground(255, 0, 0);
                        images[static_cast<int>(ofRandom(60))].draw(
                            static_cast<int>(ofRandom(ofGetScreenWidth())),
                            static_cast<int>(ofRandom(ofGetScreenHeight())),
                            static_cast<int>(ofRandom(500)),
                            static_cast<int>(ofRandom(500)));
                      }});
    // NOT WORKING
    /*
    ofxSubscribeOsc(9005, "/writeString", [&font = ttf](vector<int> nums){
                      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                      // GL_SRC_ALPHA_SATURATE,GL_ONE     GL_SRC_ALPHA, GL_ONE
                      ofFill();
                      ofSetColor(255, 255, 255, 255);
                      ofPushMatrix();
                      ofTranslate(100, 100);
                      //ttf.drawString("καλησπέρα", 0, 0);
                      ofPopMatrix();
                    });
    ofxSubscribeOsc(9005, "/fftData2",
                    [&]
                    (vector<int> nums){
                      for (int i=0; i < 512; i++) {
                        //fft[i] = nums[i];
                      }
                    });
    */
  // FFT
    fftTexture.allocate(ofGetScreenWidth(), ofGetScreenHeight(), GL_RGB);
    fft = new float[512];
    for (int i = 0; i < 512; ++i) {
      fft[i] = 0;
    }
    bands = 512;
  // Mirror Effects
    textureScreen.allocate(ofGetScreenWidth(), ofGetScreenHeight(), GL_RGB);
  // Start Values
    bg_color = ofColor(255, 255, 255, 25);
    xSoundSketchMin = 0; xSoundSketchMax = 1;
    ySoundSketchMin = 40; ySoundSketchMax = 800;
    fillBackground = true;
    fftView = false;
    fftPolyline = false;
    onsetOn = false;
    mirrorMode = false;
    soundSketch = false;
    autoSketch = false;
    hideTypo = true;

    color = ofColor(0, 0, 0, 0);
    ofBackground(bg_color);
  // Auto Sketch
    baseNode.setPosition(0, 0, 0);
    childNode.setParent(baseNode);
    childNode.setPosition(0, 0, 200);
    grandChildNode.setParent(childNode);
    grandChildNode.setPosition(0, 50, 0);
  // Load Images
    string imageDir = "/home/aris/Pictures/lyon/";
    for (int i = 0; i < 61; i++) {
      string number;
      std::string s;
      std::stringstream out;
      out << i;
      s = out.str();
      imageDir += s;
      imageDir += ".jpg";
      // cout << imageDir << endl;
      image[i].loadImage(imageDir);
      imageDir = "/home/aris/Pictures/lyon/";
    }
    }
void ofApp::update() {
  for (int i = 0; i < NUM_MSG_STRINGS; i++) {
    if (timers[i] < ofGetElapsedTimef()) {
      msgStrings[i] = "";
    }}
  while (receiver.hasWaitingMessages()) {
    ofxOscMessage m;
    receiver.getNextMessage(m);
    if (m.getAddress() == "/fftData") {
      for (int i=0; i < 512; i++) {
        fft[i] = m.getArgAsFloat(i);
      }
    } else if (m.getAddress() == "/writeString") {
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      // GL_SRC_ALPHA_SATURATE,GL_ONE     GL_SRC_ALPHA, GL_ONE
      ofFill();
      ofSetColor(m.getArgAsInt32(3), m.getArgAsInt32(4),
                 m.getArgAsInt32(5), m.getArgAsInt32(6));
      ofPushMatrix();
      ofTranslate(m.getArgAsInt32(1), m.getArgAsInt32(2), 0);
      //string fontpath = "arial.ttf";
      //ofTrueTypeFontSettings settings(fontpath, 12);
      ttf.drawString(m.getArgAsString(0), 0, 0);
      ofPopMatrix();
    } else if (m.getAddress() == "/drawRect") {
      ofSetColor(m.getArgAsInt32(4), m.getArgAsInt32(5), m.getArgAsInt32(6));
      ofDrawRectangle(m.getArgAsInt32(0), m.getArgAsInt32(1),
                      m.getArgAsInt32(2), m.getArgAsInt32(3));
    } else if (m.getAddress() == "/typoParticleMode") {
      drawMode = m.getArgAsInt32(0);
      bUpdateDrawMode = true;
      }
    }
  if (soundSketch != soundSketchOld) {
    color = ofColor(0, 0, 0, 5);
    soundSketchOld = soundSketch;}
  if (soundSketch) {
    for (int i = 0; i < 100; i++) {
      sketch[i].init(1, ofRandom(elasticityMin, elasticityMax),
                     ofRandom(dampingMin, dampingMax));}}
  if (autoSketch != autoSketchOld) {
    color = ofColor(0, 0, 0, 5);
    autoSketchOld = autoSketch;}
  if (autoSketch) {
    for (int i = 100; i < 200; i++) {
      sketch[i].init(1, ofRandom(elasticityMin, elasticityMax),
                     ofRandom(dampingMin, dampingMax));
    }

    baseNode.pan(1);
    childNode.tilt(5);
    line.addVertex(grandChildNode.getGlobalPosition());
    if (line.size() > 100) {
      line.getVertices().erase(line.getVertices().begin());}}
  if (hideTypo) {
    if (bUpdateDrawMode) {
      updateDrawMode();
    }
    if (bResetParticles) {
      resetParticles();
    }
    for (int i = 0; i < particles.size(); i++) {
      particles[i]->update();}}}
void ofApp::draw() {
  if (fillBackground) {
    ofSetColor(color);
    ofFill();
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());}
  if (fftView) {
    for (int i=0; i < 512; i++) {
      glColor3f(255*fft[i], 255*fft[i], 255*fft[i]);
      ofEllipse(ofGetWidth()/2, 512-i, 2, 2);
    }
    fftTexture.loadScreenData(0, 0, ofGetWidth()/2, ofGetHeight()/2);
    ofSetColor(255, 255, 255, 255);
    fftTexture.draw(-1, 0, ofGetWidth()/2, ofGetHeight()/2);
    fftTexture.loadScreenData(0, 0, ofGetWidth()/2, ofGetHeight()/2);

    glPushMatrix();
    ofSetHexColor(0xffffff);
    glTranslatef(ofGetWidth(), 0, 0);
    glRotatef(180, 0, 1.0f, 0);
    fftTexture.draw(0, 0,
                    ofGetWidth()/2, ofGetHeight()/2);
    glPopMatrix();

    fftTexture.loadScreenData(0, 0, ofGetWidth(), ofGetHeight()/2);

    glPushMatrix();
    glTranslatef(0, ofGetHeight(), 0);
    glRotatef(180, 1.0f, 0, 0);
    fftTexture.draw(0, 0,
                    ofGetWidth(), ofGetHeight()/2);
    glPopMatrix();}
  if (fftPolyline) {
    ofSetColor(255, 255, 255, 255);
    ofTranslate(256, 150);
    for (int i = 0; i < bands; i+=16) {
      ofPolyline polyline;
      for (int j = 0; j < bands; ++j) {
        polyline.addVertex(j, i-fft[j] * 1000.0);
      }
      polyline.draw();
    }}
  if (soundSketch) {
    for (int i=0; i < 100; i++) {
      sketch[i].drawMouse3D(
          ofMap(xSoundSketch, xSoundSketchMin, xSoundSketchMax,
                0, ofGetWidth(), true),
          ofGetHeight() - ofMap(ySoundSketch, ySoundSketchMin, ySoundSketchMax,
                0, ofGetHeight(), true), 0,
          255, 255, 255, 155, 1);
    }
    }
  if (autoSketch) {
    cam.begin();
    for (int i=100; i < 200; i++) {
      sketch[i].drawMouse3D(grandChildNode.getGlobalPosition().x,
                            grandChildNode.getGlobalPosition().y,
                            grandChildNode.getGlobalPosition().z,
                            255, 255, 255, 155, 1);
    }
    cam.end();}
  if (hideTypo) {
    ofSetColor(255);
    for (int i = 0; i < particles.size(); i++) {
      particles[i]->display();
    }}
  if (mirrorMode) {
    textureScreen.loadScreenData(0, 0, ofGetWidth(), ofGetHeight());
    glPushMatrix();
    ofSetHexColor(0xffffff);
    glTranslatef(ofGetWidth(), 0, 0);
    glRotatef(180, 0, 1.0f, 0);
    textureScreen.draw(0, 0, ofGetWidth(), ofGetHeight());
    glPopMatrix();}}
void ofApp::updateDrawMode() {
  cout << drawMode <<endl;
  drawMode = ++drawMode % 4;
  if (drawMode == 2) {
    ofSetColor(255);
    //fbo.draw(0, 0);
  }
  bResetParticles = true;
  bUpdateDrawMode = false;
  }
void ofApp::resetParticles() {
  // clear existing particles
  for (int i = 0; i < particles.size(); i++) {
    delete particles[i];
    particles[i] = NULL;
  }
  particles.clear();
  // create new particles
  if (particles.size() < maxParticles) {
    int difference = maxParticles - particles.size();
    for (int i = 0; i < difference; i++) {
      Particle * p = new Particle();
      p->setup(&pix, fbo_color, drawMode);
      particles.push_back(p);
    }
  }
  bResetParticles = false;}
void ofApp::keyPressed(int key) { }
void ofApp::keyReleased(int key) { }
void ofApp::mouseMoved(int x, int y ) { }
void ofApp::mouseDragged(int x, int y, int button) { }
void ofApp::mousePressed(int x, int y, int button) { }
void ofApp::mouseReleased(int x, int y, int button) { }
void ofApp::mouseEntered(int x, int y) { }
void ofApp::mouseExited(int x, int y) { }
void ofApp::windowResized(int w, int h) { }
void ofApp::gotMessage(ofMessage msg) { }
void ofApp::dragEvent(ofDragInfo dragInfo) { }
// Usefull code
  // if (ofGetFrameNum() % 60 == 0)
  // float sinOfTime2              = sin( ofGetElapsedTimef() + PI);
  // float sinOfTimeMapped2        = ofMap(sinOfTime2, -1, 1, 0, 255);
  // https://www.youtube.com/watch?v=J_FIWS5C2wc about ofxGui Group
  // static_cast<int>(ofRandom(ofGetScreenWidth()))
