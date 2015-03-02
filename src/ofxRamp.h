//
//  ofxRamp.h
//
//  Created by lars berg on 2/23/15.
//

#pragma once

#include "Ramp.h"

template<class T>
using ofxRamp = Ramp::Ramp<T>;

template<class T>
using ofxRampItem = shared_ptr< Ramp::RampItem<T> >;
