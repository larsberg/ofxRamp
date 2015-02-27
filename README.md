# ofxRamp  v 0.0.0
## a templated ramp addon for openframeworks

Features:
--------
* easily create ramps for any data type that has +, -, * operators
* create ramps from both const variables and pointers 

usage:
-----
	ofxRamp<float> exampleRamp;
	
	exampleRamp.addValue( -1000, 0, Ramp::Ease::Linear );
	exampleRamp.addValue(  100, .5, Ramp::Ease::Quintic::In );
	exampleRamp.addValue( 12345, 1, Ramp::Ease::Sinusoidal::InOut );
	
	float sample = exampleRamp.getValue( .3 );
	cout << "sample: " << sample << endl;
	//sample: -340


