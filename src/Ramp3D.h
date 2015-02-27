//
//  Ramp3D.h
//
//  Created by lars berg on 2/27/15.
//

#pragma once

#include "Ramp.h"

namespace Ramp
{
	template<class T>
	class RampItem3D
	{
	public:
		RampItem3D(shared_ptr< RampItem<T> > _uItem, shared_ptr< RampItem<T> > _vItem, shared_ptr< RampItem<T> > _wItem) :
		uItem( _uItem ),
		vItem( _vItem ),
		wItem( _wItem )
		{}
		
		void getUVW( float& u, float& v, float& w )
		{
			u = uItem->u;
			v = vItem->u;
			w = wItem->u;

			//return pair<float, float>( uItem != NULL ? uItem->u : 0, vItem != NULL ? vItem->u : 0 );
		}
		
		void setUVW(float u, float v, float w)
		{
			uItem->u = u;
			vItem->u = v;
			wItem->u = w;
		}
		
		shared_ptr< RampItem<T> > uItem, vItem, wItem;
	};
	
	template<class T>
	class Ramp3D
	{
	public:
		Ramp3D()
		{}
		~Ramp3D()
		{}
		
		shared_ptr< RampItem3D<T> > addValues(T uValue, T vValue, T wValue, float u, float v, float w, EaseFunc uEase=Ease::Linear, EaseFunc vEase=Ease::Linear, EaseFunc wEase=Ease::Linear )
		{
			auto uItem = uRamp.addValue( uValue, u, uEase );
			auto vItem = vRamp.addValue( vValue, v, vEase );
			auto wItem = wRamp.addValue( vValue, w, wEase );
			
			shared_ptr< RampItem3D<T> > uvwItem( new RampItem3D<T>(uItem, vItem, wItem) );
			
			rampItems.push_back( uvwItem );
			
			return uvwItem;
		}
		
		void getValues( float u, float v, float w, T& uTarget, T& vTarget, T& wTarget  )
		{
			uTarget = uRamp.getValue( u );
			vTarget = vRamp.getValue( v );
			wTarget = wRamp.getValue( w );
		}
		
		void setUVW( shared_ptr< RampItem3D<T> > uvwItem, float u, float v, float w)
		{
			uvwItem->setUVW( u, v, w );
			update();
		}
		
		void update()
		{
			uRamp.update();
			vRamp.update();
			wRamp.update();
		}
		
		Ramp<T> uRamp, vRamp, wRamp;
		
		vector< shared_ptr< RampItem3D<T> > > rampItems;
	};
	
}