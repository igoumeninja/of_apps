/*
 *  Sketch.cpp
 *  sketch091221
 *
 *  Created by Aris Bezas on 091223
 *  Copyright 2009 igoumeninja. All rights reserved.
 *
 */
 
#include "ofApp.h"
#include "ofSketch.h"
//----------------------------------------------------------------------------------------------------//

// Initialize the Sketch Lines Characteristics
void ofSketch::init(float elast, float aposv) {
  for (int i=0; i<stoixeia; i++){
    elastikotitaMouse[i] = (elast)*(.05*(i+1));// 0.05  kai 0.005
    aposbesiMouse[i] = aposv-(0.02 *i);
  }
}
void ofSketch::draw(int xL, int yL, int zL, int redL, int greenL, int blueL, int alphaL, float lines) {
  ofNoFill();
  ofSetColor(redL, greenL, blueL, alphaL);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_LINE_SMOOTH);    
  if	(lines)	{
    glBegin(GL_LINES); //https://en.wikibooks.org/wiki/OpenGL_Programming/GLStart/Tut3
  }	else	{
    glBegin(GL_POINTS); //GL_LINE_LOOP
  }
  for (int i=0; i<stoixeia; i++){
    if (i==0){
      deltaXMouse[i] = (xL - xiMouse[i]);
      deltaYMouse[i] = (yL - yiMouse[i]);
      deltaZMouse[i] = (zL - ziMouse[i]);
    }
    else {
      deltaXMouse[i] = (xiMouse[i-1]-xiMouse[i]);
      deltaYMouse[i] = (yiMouse[i-1]-yiMouse[i]);
      deltaZMouse[i] = (ziMouse[i-1]-ziMouse[i]);
    }		
    deltaXMouse[i] *= elastikotitaMouse[i];    // create elastikotita effect
    deltaYMouse[i] *= elastikotitaMouse[i];
    deltaZMouse[i] *= elastikotitaMouse[i];
    epitaxinsiXMouse[i] += deltaXMouse[i];
    epitaxinsiYMouse[i] += deltaYMouse[i];
    epitaxinsiZMouse[i] += deltaZMouse[i];
    xiMouse[i] += epitaxinsiXMouse[i]; // move it
    yiMouse[i] += epitaxinsiYMouse[i];
    ziMouse[i] += epitaxinsiZMouse[i];
    // cout << xiMouse[i] << endl;
    my3d.x = xiMouse[i];
    my3d.y = yiMouse[i];
    my3d.z = ziMouse[i];		//my3d.z = ofRandom(100,500); maybe it 'll be interasting to put a midi controller for this to prevent chaotic-sand results
    glVertex3f(my3d.x, my3d.y, my3d.z);	
    epitaxinsiXMouse[i] *= aposbesiMouse[i];    // slow down elastikotita
    epitaxinsiYMouse[i] *= aposbesiMouse[i];
    epitaxinsiZMouse[i] *= aposbesiMouse[i];
  }
  glEnd();	
}

void ofSketch::update(float xL, float yL, float zL, int redL, int greenL, int blueL, int alphaL) {
	ofFill();
	ofSetColor(redL, greenL, blueL, alphaL);
	glEdgeFlag(GL_TRUE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);       
	glBegin(GL_POINTS);	//GL_POINTS,GL_LINE_LOOP, GL_LINE_STRIP  (http://pyopengl.sourceforge.net/documentation/manual/glBegin.3G.xml)

	for (int i=0; i<stoixeia; i++){
		if (i==0){
			deltaX[i] = (xL - xi[i]);
			deltaY[i] = (yL - yi[i]);
		}
		else {
			deltaX[i] = (xi[i-1]-xi[i]);
			deltaY[i] = (yi[i-1]-yi[i]);
		}		
		deltaX[i] *= elastikotita[i];    // create elastikotita effect
		deltaY[i] *= elastikotita[i];
		epitaxinsiX[i] += deltaX[i];
		epitaxinsiY[i] += deltaY[i];
		xi[i] += epitaxinsiX[i];// move it
		yi[i] += epitaxinsiY[i];
		my3d.x = xi[i];
		my3d.y = yi[i];
		my3d.z = zL;
		glVertex3f(my3d.x, my3d.y, my3d.z);		
		epitaxinsiX[i] *= aposbesi[i];    // slow down elastikotita
		epitaxinsiY[i] *= aposbesi[i];
	}
	glEnd();	
}
void ofSketch::updateClassic(float xL, float yL, float zL, int redL, int greenL, int blueL, int alphaL) {	
	ofFill();
	ofSetColor(redL, greenL, blueL, alphaL);
	ofBeginShape();
	for (int i=0; i<stoixeia; i++){
		if (i==0){
			deltaX[i] = (xL - xi[i]);
			deltaY[i] = (yL - yi[i]);
		}
		else {
			deltaX[i] = (xi[i-1]-xi[i]);
			deltaY[i] = (yi[i-1]-yi[i]);
		}		
		deltaX[i] *= elastikotita[i];    // create elastikotita effect
		deltaY[i] *= elastikotita[i];
		epitaxinsiX[i] += deltaX[i];
		epitaxinsiY[i] += deltaY[i];
		xi[i] += epitaxinsiX[i];// move it
		yi[i] += epitaxinsiY[i];
		ofCurveVertex(xi[i], yi[i]);
		epitaxinsiX[i] *= aposbesi[i];    // slow down elastikotita
		epitaxinsiY[i] *= aposbesi[i];
	}
	ofEndShape();
	
}
void ofSketch::stoping(float xL, float yL) {
}
void ofSketch::sound(float xL, float yL) {

}














































