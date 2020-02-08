#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

  ofSetWindowShape(1920, 1080);

  string fontpath = "arial.ttf";
  ofTrueTypeFontSettings settings(fontpath, 250);
  settings.antialiased = true;
  settings.addRanges(ofAlphabet::Greek);
  sender.setup(HOST, PORT_SEND);
  receiver.setup(PORT_RECEIVE);
  maxParticles = 200; // the maximum number of active particles
  drawMode = 1; // move through the drawing modes by clicking the mouse
  bg_color = ofColor(255);
  fbo_color = ofColor(0);
  
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
}

//--------------------------------------------------------------
void ofApp::update(){
  // hide old messages
  for(int i = 0; i < NUM_MSG_STRINGS; i++){
    if(timers[i] < ofGetElapsedTimef()){
			msgStrings[i] = "";
    }
  }
  
  // check for waiting messages
  while(receiver.hasWaitingMessages()){
    
    // get the next message
    ofxOscMessage m;
    receiver.getNextMessage(m);
    
    // check for mouse moved message
    if(m.getAddress() == "/background"){
      ofBackground(0);
    }
    // check for mouse button message
    else if(m.getAddress() == "/mouse/button"){
      
      // first argument is int32, second is a string
    }
    // check for an image being sent
    // note: the size of the image depends greatly on your network buffer
    // sizes, if an image is too big the message won't come through
    else if(m.getAddress() == "/image"){

    }
    else{
      
      // unrecognized message: display on the bottom of the screen
      string msgString;
      msgString = m.getAddress();
      msgString += ":";
      for(size_t i = 0; i < m.getNumArgs(); i++){
        
        // get the argument type
        msgString += " ";
        msgString += m.getArgTypeName(i);
        msgString += ":";
        
        // display the argument - make sure we get the right type
        if(m.getArgType(i) == OFXOSC_TYPE_INT32){
          msgString += ofToString(m.getArgAsInt32(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
          msgString += ofToString(m.getArgAsFloat(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
          msgString += m.getArgAsString(i);
        }
        else{
          msgString += "unhandled argument type " + m.getArgTypeName(i);
        }
      }
      
      // add to the list of strings to display
      msgStrings[currentMsgString] = msgString;
      timers[currentMsgString] = ofGetElapsedTimef() + 5.0f;
      currentMsgString = (currentMsgString + 1) % NUM_MSG_STRINGS;
      
      // clear the next line
      msgStrings[currentMsgString] = "";
    }
  }
  ////////////////////////////////////////////////////////
    if(bUpdateDrawMode){
      updateDrawMode();
    }
  if(bResetParticles){
    resetParticles();
  }
  for(int i = 0; i < particles.size(); i++){
    particles[i]->update();
  }
  ofSetWindowTitle("drawMode: " + ofToString(drawMode) + " | numParticles: " + ofToString(particles.size()) + " | fps: " + ofToString(ofGetFrameRate(), 0));
}

//--------------------------------------------------------------
void ofApp::draw(){
  for(int i = 0; i < particles.size(); i++){
    particles[i]->display();
  }
}

void ofApp::updateDrawMode(){
  ofxOscMessage m;
  m.setAddress("/mouse/position");
  m.addFloatArg(ofMap(ofGetMouseX(), 0, ofGetWidth(), 0.f, 1.f, true));
  m.addFloatArg(ofMap(ofGetMouseY(), 0, ofGetHeight(), 0.f, 1.f, true));
  sender.sendMessage(m, false);
  //////////////////////////////////////////////////////////////////////////
  drawMode = ++drawMode % 4; // move through 4 drawing modes (0, 1, 2, 3)
  //ofBackground(bg_color); // clear the screen when changing drawing mode
  if(drawMode == 2){
    ofSetColor(255);
    //fbo.draw(0, 0); // draw text to the screen for drawMode 2
  }
  bResetParticles = true;
  bUpdateDrawMode = false;
}

//--------------------------------------------------------------
void ofApp::resetParticles(){
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

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  bUpdateDrawMode = true;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

  // send a test message
  if(key == 'a' || key == 'A'){
    ofxOscMessage m;
    m.setAddress("/test");
    m.addIntArg(1);
    m.addFloatArg(3.5f);
    m.addStringArg("hello");
    m.addFloatArg(ofGetElapsedTimef());
    sender.sendMessage(m, false);
  }
}
