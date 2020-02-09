#include "Particle.h"

Particle::Particle(){
	pixPtr = NULL;
}

//--------------------------------------------------------------
void Particle::setup(ofPixels * _pix, ofColor _c, int _drawMode){
	pixPtr = _pix;
	c = _c;
	drawMode = _drawMode;

	radius = 1; // base radius of the ellipse default value: 10
	life = 1; // start with a full life
	lifeRate = 0.001; // decrease rate of life default value: 0.01

	getPosition();

	vel.set(0.51, 0);
	vel.rotate(ofRandom(360));
}

//--------------------------------------------------------------
void Particle::update(){
	vel.rotate(ofRandom(-5, 5)); // rotate velocity (direction of movement)
	loc += vel; // add velocity to position (aka move!)
	switch(drawMode){
	 case 0:
		 // once the particle is outside the text, randomly place it somewhere inside the text
		 if(!isInText()){
                   vel = -vel;
			 getPosition();
		 }
		 break;

	 case 1:
	 case 2:
           // life -= lifeRate;
		 break;

	 case 3:
		 // combine the behaviors of case 0 (keep particle inside text) and 1 (decrease life)
		 if(!isInText()){
                   vel = -vel;
			 getPosition();
		 }
                 //	 life -= lifeRate;
		 break;
	}
	if(life < 0){
		life = 1;
		getPosition();
	}
}

//--------------------------------------------------------------
void Particle::display(){
	float r = radius; // radius of the ellipse
	switch(drawMode){
	 case 0:
		 break; // don't change radius

	 case 1: // go to 3
	 case 2: // go to 3
	 case 3:
		 r *= life;
		 break; // base the radius of the ellipse on the life (which decreases from 1 to 0)
	}
	ofFill();
	ofSetColor(255);
	ofEllipse(loc.x, loc.y, r, r); // draw ellipse
	ofNoFill();
	ofSetColor(0, 255); //default trasparency value: 135
	ofEllipse(loc.x, loc.y, r, r); // draw ellipse
}

//--------------------------------------------------------------
void Particle::getPosition(){
	// get a random position inside the text
	while(!isInText()){
		loc.set(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
	}
}

//--------------------------------------------------------------
bool Particle::isInText(){
	if(pixPtr){
		return (pixPtr->getColor(loc.x, loc.y) == c);
	}
	else{
		return true;
	}
}
