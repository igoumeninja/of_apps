/*
 
 Preapering AudioVisual Performance at Lyon-Grenoble
 
 Aris Bezas 
 Igoumeninja 28-10-2011
 
*/
 
#include "liveApp.h"

void liveApp::setup()	{
    ofBackground(0,0,0);
    ofSetBackgroundAuto(false);
    ofEnableSmoothing();
    ofEnableAlphaBlending(); 
    //glutSetCursor(GLUT_CURSOR_CYCLE);  // change cursor icon (http://pyopengl.sourceforge.net/documentation/manual/glutSetCursor.3GLUT.html)
    cout << "recieving OSC at port: 12345 " << PORTlisten << "\n";
    receiver.setup( PORTlisten );
    current_msg_string = 0;
    
    ofSetWindowTitle("Rhythmanalysis");
    ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
    ofSetVerticalSync(false);
    
    //sketch
    aSound = 255;
    rSketch = gSketch = bSketch = aSketch = 255;
    rSound = gSound = bSound = aSound = 255;
    
    
    drawWithMouse = 1;
    numMouseSketches = 100;
    minMouseElasticity = 0.0;
    maxMouseElasticity = 0.99;
    minMouseDamping = 0.0;
    maxMouseDamping = 0.99;
    
    numSoundSketches = 1;
    minSoundElasticity = 0.0;
    maxSoundElasticity = 0.99;
    minSoundDamping = 0.0;
    maxSoundDamping = 0.99;
    
    mouseLines = 1;
    soundLines = 1;
    
    ampInLow =0.0;
    ampInHigh = 0.15;
    freqInLow = 20;
    freqInHigh = 4000;
    
    feedbackView = 0;
    feedbackSpeedX = 0;
    feedbackSpeedY = 0;
    timeLine = 0;
    viewRotate = 0;				
    
    for (int i = 0; i < MAX_SKETCHES; i++){
      sketch[i].init(0, ofRandom(minSoundElasticity, maxSoundElasticity), ofRandom(minSoundDamping, maxSoundDamping));	//to 1o stoixeio einai to id 0:
      sketch[i].init(1, ofRandom(minMouseElasticity, maxMouseElasticity), ofRandom(minMouseDamping, maxMouseDamping));	//id:1 => mouse init(int sketchID, float elast, float aposv)
      
      sketchPhrase = true;
      
    }
}
void liveApp::update()	{ 
}

void liveApp::draw()	{
  for( int i=0; i<numMouseSketches; i++ ) {
    sketch[i].drawMouse(ofGetMouseX(), ofGetMouseY(), 0, 255,255,255,255, 20);
  }
}

void liveApp::keyPressed(int key)	{
  if ( key == 'm')	ofHideCursor();
  if ( key == 'M')	ofShowCursor();
  if(key == 'b' or key == 'B'){
    ofBackground(0, 0, 0);
  }	
  if(key == 't' or key == 'T'){

  }	
}
void liveApp::keyReleased(int key)	{
  
}
void liveApp::mouseMoved(int x, int y )	{
}
void liveApp::mouseDragged(int x, int y, int button)	{
  
}
void liveApp::mousePressed(int x, int y, int button)	{
  isMousePressed = true;
  drawNow = true;	
}
void liveApp::mouseReleased(int x, int y, int button)	{
  isMousePressed = false;
  drawNow = false;
}
void liveApp::resized(int w, int h)	{
  
}
