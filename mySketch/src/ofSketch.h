/*
 *  Sketch.h
 *  sketch091221
 *
 *  Created by fou fou on 12/23/09.
 *  Copyright 2009 Aris Bezas. All rights reserved.
 *
 */

#pragma once

#include "ofxOsc.h"
//#include "ofxVectorMath.h"

#define stoixeia		100
#define stoixeiaMouse		100		// power to the people: 400 loop working fine
#define MAX_N_PTS		100

#define HOST				"localhost"
#define PORT				57120

class ofSketch {
public:	
  int				sketchID;
  
  float			xi[stoixeia];
  float			yi[stoixeia];
  float			epitaxinsiX[stoixeia];
  float			epitaxinsiY[stoixeia];
  float			elastikotita[stoixeia];
  float			aposbesi[stoixeia];
  float			deltaX[stoixeia];
  float			deltaY[stoixeia];
  
  float			xiMouse[stoixeiaMouse];
  float			yiMouse[stoixeiaMouse];
  float			ziMouse[stoixeiaMouse];
  float			epitaxinsiXMouse[stoixeiaMouse];
  float			epitaxinsiYMouse[stoixeiaMouse];
  float			epitaxinsiZMouse[stoixeiaMouse];
  float			elastikotitaMouse[stoixeiaMouse];
  float			aposbesiMouse[stoixeiaMouse];	
  float			deltaXMouse[stoixeiaMouse];
  float			deltaYMouse[stoixeiaMouse];
  float			deltaZMouse[stoixeiaMouse];
  
  float			elast, aposv;
  int				xL, yL, zL;
  float			value, xC, yC;		
  int				redL, greenL, blueL, alphaL;
  float			delta;
  float			xp,yp;
  
  float				on_off, lines, slines;
  
  ofVec3f		my3d;
  
  void			init(int sketchID, float elast, float aposv);
  void			draw(int x, int y, int z, int r, int g, int b, int a);
  void			drawMouse(int xL, int yL, int zL, int redL, int greenL, int blueL, int alphaL, float lines);
  void			draw(int xL, int yL, int zL, int redL, int greenL, int blueL, int alphaL, float lines);
  void			drawSound(float xL, float yL, float zL, int redL, int greenL, int blueL, int alphaL, float slines);	
  void			update(float xL, float yL, float zL, int redL, int greenL, int blueL, int alphaL);
  void			updateClassic(float xL, float yL, float zL, int redL, int greenL, int blueL, int alphaL);
  void			sound(float xL, float yL);
  void			stoping(float xL, float yL);
  
private:
	ofxOscSender	sender;
};








































