// Copyright 2019 Aris Bezas
#include "ofApp.h"
void ofApp::setup() {
  ofBackground(0, 0, 0);
  ofSetWindowPosition(0, 0);
  ofEnableSmoothing();
  ofSetBackgroundAuto(true);
  ofEnableAlphaBlending();
  ofSetFrameRate(60);  // if vertical sync is off, we can go faster
  ofSetVerticalSync(false);
  glPointSize(1);
  //  ofEnableDepthTest();
  ofxSubscribeOsc(9005, "/hideSketch", hideSketch);
  ofxSubscribeOsc(9005, "/hideTypo", hideTypo);
  ofxSubscribeOsc(9005, "/color", color);
  ofxSubscribeOsc(9005, "/elasticityMin", elasticityMin);
  ofxSubscribeOsc(9005, "/elasticityMax", elasticityMax);
  ofxSubscribeOsc(9005, "/dampingMin", dampingMin);
  ofxSubscribeOsc(9005, "/dampingMax", dampingMax);
  ofxSubscribeOsc(9005, "/color", color);
  ofxSubscribeOsc(9005, "/cursor", p);
  ofxSubscribeOsc(9005, "/onset", [](){ofBackground(0,0,0);});
  string fontpath = "arial.ttf";
  ofTrueTypeFontSettings settings(fontpath, 250);

  settings.antialiased = true;
  settings.addRanges(ofAlphabet::Greek);

  maxParticles = 200;  // the maximum number of active particles
  drawMode = 1;  // move through the drawing modes by clicking the mouse

  bg_color = ofColor(255);
  fbo_color = ofColor(0);

  hideSketch = false;
  bUpdateDrawMode = false;
  bResetParticles = true;

  ofBackground(bg_color);
  ofSetBackgroundAuto(false);
  ofEnableAntiAliasing();
  ofSetFrameRate(60);

  ofTrueTypeFont ttf;
  ttf.loadFont("arial.ttf", 250);
  ttf.load(settings);
  string s = "επιθυμίες";

  fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
  pix.allocate(ofGetWidth(), ofGetHeight(), OF_PIXELS_RGBA);
  fbo.begin();
  ofClear(0, 0, 0, 0);
  // Center string code from:
  // https://github.com/armadillu/ofxCenteredTrueTypeFont/blob/master/src/ofxCenteredTrueTypeFont.h
  ofRectangle r = ttf.getStringBoundingBox(s, 0, 0);
  ofVec2f offset = ofVec2f(floor(-r.x - r.width * 0.5f), floor(-r.y - r.height * 0.5f));
  ofSetColor(fbo_color);
  ttf.drawString(s, fbo.getWidth() / 2 + offset.x, fbo.getHeight() / 2 + offset.y);
  fbo.end();

  fbo.readToPixels(pix); // the ofPixels class has a convenient getColor() method

  baseNode.setPosition(0, 0, 0);
  childNode.setParent(baseNode);
  childNode.setPosition(0, 0, 200);
  grandChildNode.setParent(childNode);
  grandChildNode.setPosition(0, 50, 0);
}
void ofApp::update() {
  if (hideSketch != hideSketchOld) {
    color = ofColor(0, 0, 0, 5);
    hideSketchOld = hideSketch;
  }
  if (hideSketch) {
    for (int i = 0; i < 100; i++) {
      sketch[i].init(1, ofRandom(elasticityMin, elasticityMax), ofRandom (dampingMin, dampingMax));
    }

    baseNode.pan(1);
    childNode.tilt(5);
    line.addVertex(grandChildNode.getGlobalPosition());
    if (line.size() > 100) {
      line.getVertices().erase( line.getVertices().begin());
    }
  }  // sketch
  if (hideTypo != hideTypoOld) {
    color = ofColor(255, 255, 255, 5);
    hideTypoOld = hideTypo;
  }
  if (hideTypo) {
    if(bUpdateDrawMode){
      updateDrawMode();
    }
    if(bResetParticles){
      resetParticles();
    }
    for(int i = 0; i < particles.size(); i++){
      particles[i]->update();
    }
  }
}
void ofApp::draw() {
  ofSetColor(color);
  ofFill();
  ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
  if (hideSketch) {
    cam.begin();
    //  uncomment these 3 lines to understand how nodes are moving
    //  baseNode.draw();
    //  childNode.draw();
    //  grandChildNode.draw();
    //  line.draw();
    for (int i=0; i < 100; i++) {
      sketch[i].drawMouse3D(grandChildNode.getGlobalPosition().x,grandChildNode.getGlobalPosition().y,grandChildNode.getGlobalPosition().z, 255,255,255,155,1);
    }
    cam.end();
  }  // sketch
  if (hideTypo) {
    ofSetColor(255);
    for (int i = 0; i < particles.size(); i++) {
    particles[i]->display();
    }
  }
}
void ofApp::updateDrawMode() {
  drawMode = ++drawMode % 4; // move through 4 drawing modes (0, 1, 2, 3)
  //ofBackground(color); // clear the screen when changing drawing mode
  if(drawMode == 2){
    ofSetColor(255);
    //fbo.draw(0, 0); // draw text to the screen for drawMode 2
  }
  bResetParticles = true;
  bUpdateDrawMode = false;
}
void ofApp::resetParticles() {
  // clear existing particles
  for(int i = 0; i < particles.size(); i++){
    delete particles[i];
    particles[i] = NULL;
  }
  particles.clear();
  // create new particles
  if(particles.size() < maxParticles){
    int difference = maxParticles - particles.size();
    for(int i = 0; i < difference; i++){
      Particle * p = new Particle();
      p->setup(&pix, fbo_color, drawMode);
      particles.push_back(p);
    }
  }
  bResetParticles = false;
}
void ofApp::keyPressed(int key) {

}
void ofApp::keyReleased(int key) {

}
void ofApp::mouseMoved(int x, int y ) {

}
void ofApp::mouseDragged(int x, int y, int button) {

}
void ofApp::mousePressed(int x, int y, int button) {

}
void ofApp::mouseReleased(int x, int y, int button) {

}
void ofApp::mouseEntered(int x, int y) {

}
void ofApp::mouseExited(int x, int y) {

}
void ofApp::windowResized(int w, int h) {

}
void ofApp::gotMessage(ofMessage msg) {

}
void ofApp::dragEvent(ofDragInfo dragInfo) { }
