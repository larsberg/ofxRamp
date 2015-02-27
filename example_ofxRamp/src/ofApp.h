#pragma once

#include "ofMain.h"
#include "ofxRamp.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
	
	//templated ramps
	ofxRamp<ofColor> colorRamp;
	
	ofxRamp<ofFloatColor> greyRamp;
	
	ofxRampItem<ofFloatColor> greyRampItem;// a shared_ptr to a Ramp::Item
	
	ofxRamp<float> polylineRamp;
	
	
	//stuff we're drawing
	ofColor c0, c1, c2;
	ofImage colorImg, greyImg;
	ofPixels colorPixels, greyPixels;
	ofPolyline polyline;
	
	ofVec3f origin;
	float lifeSpan;
	vector<ofVec3f> pos;
	vector<float> ages;
	ofxRamp<float> radiusRamp;
	
	//multidimensional ramps are kind of weird
	ofxRamp2D<float> ramp2D;
	ofxRamp3D<float> ramp3D;
	ofxRampItem3D<float> ramp3DItem;
	
	ofEasyCam easyCam;
};
