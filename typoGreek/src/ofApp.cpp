#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

  ofSetWindowShape(600, 600);
  string fontpath = "arial.ttf";
  ofTrueTypeFontSettings settings(fontpath, 40);

  settings.antialiased = true;
  settings.addRange(ofUnicode::CJKUnified);
  settings.addRanges(ofAlphabet::Latin);
  //settings.addRanges(ofAlphabet::Emoji); //This one makes my soft crash
  settings.addRanges(ofAlphabet::Japanese);
  settings.addRanges(ofAlphabet::Chinese);
  //settings.addRanges(ofAlphabet::Korean); //This one makes my soft crash
  settings.addRanges(ofAlphabet::Arabic); //This one makes my soft crash
  settings.addRanges(ofAlphabet::Devanagari);
  settings.addRanges(ofAlphabet::Greek);
  settings.addRanges(ofAlphabet::Cyrillic);
  P.load(settings);
  ofSetBackgroundColor(0);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  ofSetColor(255, 255, 255);

  float sepy = 80;
  float y = 30;
  P.drawString("Όλα είναι ένα", 10, y += sepy);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
