//
//  ofxRamp.h
//
//  Created by lars berg on 2/23/15.
//

#pragma once

#include "Ramp.h"
#include "Ramp2D.h"
#include "Ramp3D.h"

template<class T>
using ofxRamp = Ramp::Ramp<T>;

template<class T>
using ofxRampItem = shared_ptr< Ramp::RampItem<T> >;

template<class T>
using ofxRamp2D = Ramp::Ramp2D<T>;

template<class T>
using ofxRampItem2D = shared_ptr< Ramp::RampItem2D<T> >;

template<class T>
using ofxRamp3D = Ramp::Ramp3D<T>;

template<class T>
using ofxRampItem3D = shared_ptr< Ramp::RampItem3D<T> >;