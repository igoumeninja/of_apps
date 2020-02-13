// Copyright 2019 Aris Bezas
#include "ofApp.h"
void ofApp::setup() {
  //- Global Definition
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
  //- Typography
    //string fontpath = "arial.ttf";
    ofTrueTypeFontSettings settings("times.ttf", 14);
    settings.antialiased = true;
    settings.addRanges(ofAlphabet::Greek);

    bg_color = ofColor(255);
    fbo_color = ofColor(0);

    ofBackground(bg_color);
    ttf.loadFont("arial.ttf", 12);
    ttf.load(settings);
    string s = "Κατερίνα";
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
  //- OSC communication
    receiver.setup(PORT);
    ofxSubscribeOsc(9005, "/particleView", particleView);
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
  //- FFT
    fftTexture.allocate(ofGetScreenWidth(), ofGetScreenHeight(), GL_RGB);
    fft = new float[512];
    for (int i = 0; i < 512; ++i) {
      fft[i] = 0;
    }
    bands = 512;
  //- Mirror Effects
    textureScreen.allocate(ofGetScreenWidth(), ofGetScreenHeight(), GL_RGB);
  //- Start Values
    xSoundSketchMin = 0; xSoundSketchMax = 1;
    ySoundSketchMin = 40; ySoundSketchMax = 800;
    fillBackground = true;
    fftView = false;
    fftPolyline = false;
    onsetOn = false;
    mirrorMode = false;
    soundSketch = false;
    autoSketch = false;
    hideTypo = false;
    particleView = false;
    color = ofColor(0, 0, 0, 40);
    ofBackground(255);
  //- Auto Sketch
    baseNode.setPosition(0, 0, 0);
    childNode.setParent(baseNode);
    childNode.setPosition(0, 0, 200);
    grandChildNode.setParent(childNode);
    grandChildNode.setPosition(0, 50, 0);
  //- Particles
    // this number describes how many bins are used
    // on my machine, 2 is the ideal number (2^2 = 4x4 pixel bins)
    // if this number is too high, binning is not effective
    // because the screen is not subdivided enough. if
    // it's too low, the bins take up so much memory as to
    // become inefficient.
    int binPower = 4;

    particleSystem.setup(ofGetWidth(), ofGetHeight(), binPower);
    kParticles = 2;  // change that to 5 for MacBook Pro
    float padding = 0;
    float maxVelocity = .95;
    for (int i = 0; i < kParticles * 1024; i++) {
      float x = ofRandom(padding, ofGetWidth() - padding);
      float y = ofRandom(padding, ofGetHeight() - padding);
      float xv = ofRandom(-maxVelocity, maxVelocity);
      float yv = ofRandom(-maxVelocity, maxVelocity);
      Particle particle(x, y, xv, yv);
      particleSystem.add(particle);
    }
    rConColor = gConColor = bConColor = 255;
    rDotColor = gDotColor = bDotColor = 255;
    timeStep = 1;
    lineOpacity = 1;
    pointOpacity = 255;
    isMousePressed = false;
    slowMotion = false;
    particleNeighborhood = 25;
    particleRepulsion = 3;
    centerAttraction = .01;
    forceRadius = 100;
    forceScale = 10;
    bounceXstart = 0;
    bounceYstart = 0;
    bounceXend = ofGetScreenWidth();
    bounceYend = ofGetScreenHeight();
  //- Load Images
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
  //- OSC responders
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
        ttf.drawString(m.getArgAsString(0), 0, 0);
        ofPopMatrix();
      } else if (m.getAddress() == "/drawRect") {
        ofSetColor(m.getArgAsInt32(4), m.getArgAsInt32(5), m.getArgAsInt32(6));
        ofDrawRectangle(m.getArgAsInt32(0), m.getArgAsInt32(1),
                      m.getArgAsInt32(2), m.getArgAsInt32(3));
      } else if ( m.getAddress() == "/particle" ) {
        if (m.getArgAsString(0) == "activate") {
          if (m.getArgAsInt32(1) == 1) { viewParticles = true;
          } else if (m.getArgAsInt32(1) == 0) { viewParticles = false;
          }
        } else if (m.getArgAsString(0) == "lineOpacity") {
          lineOpacity = m.getArgAsInt32(1);
        } else if (m.getArgAsString(0) == "particleNeighborhood") {
          particleNeighborhood = m.getArgAsInt32(1);
        } else if (m.getArgAsString(0) == "forceRadius") {
          forceRadius = m.getArgAsInt32(1);
        } else if (m.getArgAsString(0) == "forceScale") {
          forceScale = m.getArgAsInt32(1);
        } else if (m.getArgAsString(0) == "pushParticles") {
          if (m.getArgAsInt32(1) == 1) {
            pushParticles = true;
          } else if (m.getArgAsInt32(1) == 0) {
            pushParticles = false;
          }
        } else if (m.getArgAsString(0) == "push") {
          pushX = m.getArgAsFloat(1);
          pushY = m.getArgAsFloat(2);
        } else if (m.getArgAsString(0) == "add") {
          Particle particle(m.getArgAsInt32(1),
                            m.getArgAsInt32(2),
                            m.getArgAsFloat(3),
                            m.getArgAsFloat(4));
          particleSystem.add(particle);
        } else if (m.getArgAsString(0) == "dotColor") {
          switch (m.getNumArgs()) {
            case 2:
              aDotColor = m.getArgAsInt32(1);
              cout << aDotColor;
              break;
            case 4:
              rDotColor = m.getArgAsInt32(1);
              gDotColor = m.getArgAsInt32(2);
              bDotColor = m.getArgAsInt32(3);
            break;
            case 5:
              rDotColor = m.getArgAsInt32(1);
              gDotColor = m.getArgAsInt32(2);
              bDotColor =  m.getArgAsInt32(3);
              aDotColor = m.getArgAsInt32(4);
              break;
          }
        } else if (m.getArgAsString(0) == "conColor") {
          switch (m.getNumArgs()) {
            case 2:
              aConColor = m.getArgAsInt32(1);
              break;
            case 4:
              rConColor = m.getArgAsInt32(1);
              gConColor = m.getArgAsInt32(2);
              bConColor = m.getArgAsInt32(3);
              break;
            case 5:
              rConColor = m.getArgAsInt32(1);
              gConColor = m.getArgAsInt32(2);
              bConColor = m.getArgAsInt32(3);
              aConColor = m.getArgAsInt32(4);
              break;
          }
        } else if  (m.getArgAsString(0) == "bounce") {
          bounceXstart = m.getArgAsInt32(1);
          bounceYstart = m.getArgAsInt32(2);
          bounceXend = m.getArgAsInt32(3);
          bounceYend = m.getArgAsInt32(4);
        }
      }
    }
  //- SoundSketch
    if (soundSketch != soundSketchOld) {
      color = ofColor(0, 0, 0, 5);
      soundSketchOld = soundSketch;}
    if (soundSketch) {
      for (int i = 0; i < 100; i++) {
        sketch[i].init(1, ofRandom(elasticityMin, elasticityMax),
                       ofRandom(dampingMin, dampingMax));}}
  //- AutoSketch
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
  //- THE END
      }
void ofApp::draw() {
  //- fillBackgroumd
    if (fillBackground) {
      ofSetColor(color);
      ofFill();
      ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());}
  //- fft
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
  //- fft polyline
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
  //- SoundSketch
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
  //- AutoSketch
    if (autoSketch) {
      cam.begin();
      for (int i=100; i < 200; i++) {
        sketch[i].drawMouse3D(grandChildNode.getGlobalPosition().x,
                              grandChildNode.getGlobalPosition().y,
                              grandChildNode.getGlobalPosition().z,
                              255, 255, 255, 155, 1);
      }
      cam.end();}
  //- Particles
    if (particleView) {
      particleSystem.setTimeStep(timeStep);
      ofSetColor(rConColor, gConColor, bConColor, aConColor);
      particleSystem.setupForces();
      glBegin(GL_LINES);
      for (int i = 0; i < particleSystem.size(); i++) {
        Particle& cur = particleSystem[i];
        particleSystem.addRepulsionForce(
            cur, particleNeighborhood, particleRepulsion);
        cur.bounceOffWalls(bounceXstart, bounceYstart, bounceXend, bounceYend);
        //cur.bounceOffWalls((20*ofGetFrameNum())%1500, bounceYstart, bounceXend, bounceYend);
        cur.addDampingForce();
      }
      glEnd();
      particleSystem.update();
      ofSetColor(255,255,255,255);
      particleSystem.draw();
    }
  //- MirrowMode
    if (mirrorMode) {
      textureScreen.loadScreenData(0, 0, ofGetWidth(), ofGetHeight());
      glPushMatrix();
      ofSetHexColor(0xffffff);
      glTranslatef(ofGetWidth(), 0, 0);
      glRotatef(180, 0, 1.0f, 0);
      textureScreen.draw(0, 0, ofGetWidth(), ofGetHeight());
      glPopMatrix();}
  //- THE END
    }
//- Usefull code
  // if (ofGetFrameNum() % 60 == 0)
  // float sinOfTime2              = sin( ofGetElapsedTimef() + PI);
  // float sinOfTimeMapped2        = ofMap(sinOfTime2, -1, 1, 0, 255);
  // https://www.youtube.com/watch?v=J_FIWS5C2wc about ofxGui Group
  // static_cast<int>(ofRandom(ofGetScreenWidth()))
