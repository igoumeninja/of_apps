/*
 
 Preapering AudioVisual Performance at Lyon-Grenoble
 
 Aris Bezas 
 Igoumeninja 28-10-2011
 
*/
 
#include "ofApp.h"

void ofApp::setup()	{

  gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
  gui.add(elasticityMin.set( "elasticityMin", 0.01, 0.01, 0.99 ));
  gui.add(elasticityMax.set( "elasticityMax", 0.01, 0.01, 0.99 ));
  gui.add(dampingMin.set( "dampingMin", 0.01, 0.01, 0.99 ));
  gui.add(dampingMax.set( "dampingMax", 0.01, 0.01, 0.99 ));
  gui.add(filled.set("bFill", true));
  gui.add(radius.set( "radius", 140, 10, 300 ));
  gui.add(center.set("center",glm::vec2(ofGetWidth()*.5,ofGetHeight()*.5),glm::vec2(0,0),glm::vec2(ofGetWidth(),ofGetHeight())));
  gui.add(color.set("color",ofColor(100,100,140),ofColor(0,0),ofColor(255,255)));
  gui.add(circleResolution.set("circleRes", 5, 3, 90));
  gui.add(twoCircles.setup("twoCircles"));
  gui.add(ringButton.setup("ring"));
  gui.add(screenSize.set("screenSize", ""));

  gui.loadFromFile("settings.xml");
  bHide = false;

  
  //ofEnableDepthTest();
  baseNode.setPosition(0, 0, 0);
  childNode.setParent(baseNode);
  childNode.setPosition(0, 0, 200);
  grandChildNode.setParent(childNode);
  grandChildNode.setPosition(0,50,0);

  ofBackground(0,0,0);
  ofSetBackgroundAuto(true);
  ofEnableSmoothing();
  ofEnableAlphaBlending(); 
  //glutSetCursor(GLUT_CURSOR_CYCLE);  // change cursor icon (http://pyopengl.sourceforge.net/documentation/manual/glutSetCursor.3GLUT.html)
  cout << "recieving OSC at port: 12345 " << PORTlisten << "\n";
  receiver.setup( PORTlisten );
  current_msg_string = 0;
    
  ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
  ofSetVerticalSync(false);
  
  //sketch
  rSketch = gSketch = bSketch = aSketch = 255;
    
  drawWithMouse = 1;
    minMouseElasticity = 0.5;
  maxMouseElasticity = 0.8;
  minMouseDamping = 0.1;
  maxMouseDamping = 0.69;
  
  mouseLines = 1;
  /*
  for (int i = 0; i < 100; i++){
    //sketch[i].init(1, ofRandom(minMouseElasticity, maxMouseElasticity), ofRandom(minMouseDamping, maxMouseDamping));	//id:1 => mouse init(int sketchID, float elast, float aposv)
    sketch[i].init(1, elasticity, ofRandom(minMouseDamping, maxMouseDamping));	//id:1 => mouse init(int sketchID, float elast, float aposv)
  }
  */

}
void ofApp::update()	{
  for (int i = 0; i < 100; i++){
    sketch[i].init(1, ofRandom(elasticityMin, elasticityMax), ofRandom(dampingMin, dampingMax));	//id:1 => mouse init(int sketchID, float elast, float aposv)
    //sketch[i].init(1, elasticity, ofRandom(minMouseDamping, maxMouseDamping));	//id:1 => mouse init(int sketchID, float elast, float aposv)
  }

  baseNode.pan(1);
  childNode.tilt(5);
  

  line.addVertex(grandChildNode.getGlobalPosition());
  if (line.size() > 100){
    line.getVertices().erase(
                             line.getVertices().begin()
                             );
  }

}

void ofApp::draw()	{

    cam.begin();
  
  //uncomment these 3 lines to understand how nodes are moving
  //baseNode.draw();
  //childNode.draw();
  grandChildNode.draw();
  //line.draw();
  

    for( int i=0; i<100; i++ ) {
      //sketch[i].drawMouse(ofGetMouseX(), ofGetMouseY(), 0, 255,255,255,155, 1);
      sketch[i].draw(grandChildNode.getGlobalPosition().x,grandChildNode.getGlobalPosition().y,grandChildNode.getGlobalPosition().z, 255,255,255,155,0);
    }
    
    cam.end();

    if( !bHide ){
      gui.draw();
    }
}

void ofApp::keyPressed(int key)	{
  if ( key == 'm')	ofHideCursor();
  if ( key == 'M')	ofShowCursor();
  if(key == 'b' or key == 'B'){
    ofBackground(0, 0, 0);
  }	
  if(key == 't' or key == 'T'){

  }

  if( key == 'h' ){
    bHide = !bHide;
  }
  if(key == 's') {
    gui.saveToFile("settings.xml");
  }
  if(key == 'l') {
    gui.loadFromFile("settings.xml");
  }
  if(key == ' '){
    color = ofColor(255);
  }
}
void ofApp::keyReleased(int key)	{
  
}
void ofApp::mouseMoved(int x, int y )	{
}
void ofApp::mouseDragged(int x, int y, int button)	{
  
}
void ofApp::mousePressed(int x, int y, int button)	{
  isMousePressed = true;
  drawNow = true;	
}
void ofApp::mouseReleased(int x, int y, int button)	{
  isMousePressed = false;
  drawNow = false;
}
void ofApp::resized(int w, int h)	{
  
}
