#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  gui.setup("my gui"); 
  
  //add a video to the panel   
  gui.addDrawableRect("video feed", &vid, 320, 240); 
    
  cvControls.setName("cv controls");
  cvControls.add(bInvert.set("invert", false));
  cvControls.add(threshold.set("threshold", 29.0, 1.0, 255.0));
        
  //now add the param group to the gui 
  gui.add( cvControls ); 
    
  gui.loadSettings("settings.xml"); 
}

//--------------------------------------------------------------
void ofApp::update(){
  gui.update(); 
}

//--------------------------------------------------------------
void ofApp::draw(){
  gui.draw(); 
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
