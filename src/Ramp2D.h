//
//  Ramp2D.h
//
//  Created by lars berg on 2/27/15.
//

#pragma once

#include "Ramp.h"

namespace Ramp
{
	template<class T>
	class RampItem2D
	{
	public:
		RampItem2D(shared_ptr< RampItem<T> > _uItem, shared_ptr< RampItem<T> > _vItem) :
		uItem( _uItem ),
		vItem( _vItem )
		{}
		
		pair<float, float> getUV()
		{
			return pair<float, float>( uItem != NULL ? uItem->u : 0, vItem != NULL ? vItem->u : 0 );
		}
		
		void setUV(float u, float v)
		{
			uItem->u = u;
			uItem->v = v;
		}
		
		shared_ptr< RampItem<T> > uItem, vItem;
	};
	
	template<class T>
	class Ramp2D
	{
	public:
		Ramp2D()
		{}
		~Ramp2D()
		{}
		
		shared_ptr< RampItem2D<T> > addValues(T uValue, T vValue, float u, float v, EaseFunc uEase = Ease::Linear, EaseFunc vEase = Ease::Linear )
		{
			auto uItem = uRamp.addValue( uValue, u, uEase );
			auto vItem = vRamp.addValue( vValue, v, vEase );
			
			shared_ptr< RampItem2D<T> > uvItem( new RampItem2D<T>(uItem, vItem) );
			
			rampItems.push_back( uvItem );
			
			return uvItem;
		}
		
		pair< T, T > getValues( float u , float v )
		{
			return pair<T, T>( uRamp.getValue( u ), vRamp.getValue( v )  );
		}
		void getValues( float u , float v, T& uTarget, T& vTarget  )
		{
			uTarget = uRamp.getValue( u );
			vTarget = vRamp.getValue( v );
		}
		
		void setUV( shared_ptr< RampItem2D<T> > uvItem, float u, float v)
		{
			uvItem->setUV( u, v );
			update();
		}
		
		void update()
		{
			uRamp.update();
			vRamp.update();
		}
		
		Ramp<T> uRamp, vRamp;
		
		vector< shared_ptr< RampItem2D<T> > > rampItems;
	};
	
}