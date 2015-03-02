#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{	
	//COLOR RAMP
	c0.set(255,255,0);
	c1.set(255,0,255);
	c2.set(0,255,255);
	
	colorRamp.addValuePtr( &c0, 0, Ramp::Ease::Smoother );
	colorRamp.addValuePtr( &c1, .5, Ramp::Ease::Smoother );
	colorRamp.addValuePtr( &c2, 1, Ramp::Ease::Smoother );
	
	colorImg.allocate(100, 12, OF_IMAGE_COLOR_ALPHA );
	
	colorPixels = colorImg.getPixels();
	
	for(int i=0; i<colorPixels.getWidth(); i++)
	{
		auto c = colorRamp.getValue( ofMap(i, 0, colorPixels.getWidth()-1, 0, 1) );
		for(int j=0; j<colorPixels.getHeight(); j++)
		{
			colorPixels.setColor( i, j, c );
		}
	}
	colorImg.setFromPixels( colorPixels );
	
	//GREY RAMP
	greyRamp.addValue( ofFloatColor(0,0,0,1), .2 );
	greyRamp.addValue( ofFloatColor(0,0,0,1), .8 );
	greyRampItem = greyRamp.addValue( ofFloatColor(1,1,1,1), .5);
	
	greyImg.allocate(100, 2, OF_IMAGE_COLOR_ALPHA);
	
	greyPixels = greyImg.getPixels();
	for(int i=0; i<greyPixels.getWidth(); i++)
	{
		auto c = greyRamp.getValue( i / (greyPixels.getWidth() - 1) );
		for(int j=0; j<greyPixels.getHeight(); j++)
		{
			greyPixels.setColor( i, j, c );
		}
	}
	
	
	//polyline
	polylineRamp.addValue( -100, 0, Ramp::Ease::Bounce::Out );
	polylineRamp.addValue(  100, 100, Ramp::Ease::Exponential::InOut );
	polylineRamp.addValue( -100, 200, Ramp::Ease::Bounce::Out );
	polylineRamp.addValue(  100, 300, Ramp::Ease::Exponential::InOut );
	polylineRamp.addValue( -100, 400, Ramp::Ease::Bounce::Out );
	polylineRamp.addValue(  100, 500, Ramp::Ease::Exponential::InOut );
	polylineRamp.addValue( -100, 600, Ramp::Ease::Bounce::Out );
	polylineRamp.addValue(  100, 700, Ramp::Ease::Exponential::InOut );
	
	for(int i=polylineRamp.getMinU(); i<polylineRamp.getMaxU(); i++)
	{
		polyline.addVertex( i, polylineRamp.getValue( i ) );
	}
	
		
	//circles
	radiusRamp.addValue(0, 0, Ramp::Ease::Sinusoidal::Out );
	radiusRamp.addValue(30, .5, Ramp::Ease::Sinusoidal::In );
	radiusRamp.addValue(0, 1 );
	
	int numParticles = 200;
	float rad = 300;
	ages.resize( numParticles );
	pos.resize( numParticles );
	lifeSpan = 200;
	origin.set(800, 300);
	
	ofSetCircleResolution( 33 );
	
	for(int i=0; i<pos.size(); i++)
	{
		pos[i] = origin + ofVec3f(ofRandom(-rad, rad),ofRandom(-rad, rad),ofRandom(-rad, rad) );
		ages[i] = ofRandom( -lifeSpan, lifeSpan );
	}
	
}

//--------------------------------------------------------------
void ofApp::update()
{
	float t = ofGetElapsedTimef();
	
	//update the color ramp texture
	//	we passed in pointers so all we have to do to change the colors is change the colors themseleves
	c0.setHsb( sin(ofGetElapsedTimef() * .1) * 125 + 125, 200, 255);
	c1.setHsb( sin(ofGetElapsedTimef() * .1 + 2) * 125 + 125, 200, 255);
	c2.setHsb( sin(ofGetElapsedTimef() * .1 + 4) * 125 + 125, 200, 255);
	
	//	update the texture
	for(int i=0; i<colorPixels.getWidth(); i++)
	{
		ofColor c = colorRamp.getValue( ofMap(i, 0, colorPixels.getWidth()-1, 0, 1) );
		
		for(int j=0; j<colorPixels.getHeight(); j++)
		{
			colorPixels.setColor( i, j, c );
		}
	}
	colorImg.setFromPixels( colorPixels );
	
	
	//update the grey ramp texture
	//	we stored a pointer( "ofxRampItem" ) that we can use to change the u position of a value
	greyRamp.setU( greyRampItem, sin(ofGetElapsedTimef()) * .5 + .5 );
	
	//	update the texture
	for(int i=0; i<greyPixels.getWidth(); i++)
	{
		ofFloatColor c = greyRamp.getValue( ofMap(i, 0, greyPixels.getWidth()-1, 0, 1) );
		
		for(int j=0; j<greyPixels.getHeight(); j++)
		{
			greyPixels.setColor( i, j, c );
		}
	}
	greyImg.setFromPixels( greyPixels );
	
	
	//update the particle ages
	for(int i=0; i<ages.size(); i++)
	{
		ages[i]++;
		if(ages[i] > lifeSpan)	ages[i] = 0;
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackgroundGradient( ofColor(120,128,144), ofColor(0,0,0));

	ofPushStyle();
	
	ofDisableDepthTest();
	
	//texture ramps
	colorImg.draw(100, 100, 400, 100);
	greyImg.draw(100, 300, 400, 100);
	
	//polyline
	ofEnableDepthTest();
	
	ofPushMatrix();
	ofTranslate( 100, 600 );
	
	float sample = fmod( ofGetElapsedTimef() * 100, polylineRamp.getMaxU() );
	float yPos = polylineRamp.getValue( sample );
	
	ofSetColor( colorRamp.getValue( ofMap(yPos, -100, 100, 0, 1) ) );
	ofDrawSphere( sample, yPos, 10 );
	
	ofSetColor(255);
	ofSetLineWidth( 2 );
	polyline.draw();
	
	ofPopMatrix();
	
	//circles
	for(int i=0; i<pos.size(); i++)
	{
		//a mixing value between 0 and 1
		float mixAmount = ofMap( ages[i], 0, lifeSpan, 0, 1, true );
		
		//sample a color
		ofSetColor( colorRamp.getValue( mixAmount ) );
		
		//sample a radius
		float radius = radiusRamp.getValue( mixAmount );
		
		//get the position
		ofVec3f position = Ramp::lerp( origin, pos[i], mixAmount );
		
		ofDrawCircle( position, radius );
	}
	
	ofPopStyle();
}
