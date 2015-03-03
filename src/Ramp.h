//
//  Ramp.h
//
//  Created by lars berg on 2/24/15.
//

#pragma once

#include "Easings.h"

namespace Ramp
{
	typedef float (*EaseFunc)(float);
	
	template<class T>
	static T lerp(T a, T b, float k)
	{
		return a * (1. - k) + b * k; //	a + k * (b - a) was giving an error for ofColor...
	}
	
	
	//container for our individual values, u position and easings.
	template<class T>
	class RampItem
	{
	public:
		RampItem(T itemValue, float u, EaseFunc ease ) :
		value( itemValue ),
		value_ptr( &value ),
		u( u ),
		ease( ease )
		{}
		
		RampItem(T* value_ptr, float u, EaseFunc ease ) :
		value( *value_ptr ),
		value_ptr( value_ptr ),
		u( u ),
		ease( ease )
		{}
		
		void setU(float uPosition)
		{
			u = uPosition;
		}
		
		void setValue(T val)
		{
			*value_ptr = val;
		}
		
		void setPtr(T* val)
		{
			value_ptr = val;
		}
		
		T value, *value_ptr;
		float u;
		EaseFunc ease;
	};
	
	
	
	template<class T>
	class Ramp
	{
	public:
		Ramp()
		{}
		~Ramp()
		{}
		
		//create, add and return a shared_ptr< RampItem<T> >
		shared_ptr< RampItem<T> > addValue(T value, float u, EaseFunc ease = Ease::Linear)
		{
			return addValue( shared_ptr< RampItem<T> >( new RampItem<T>( value, u, ease) ) );
		}
		
		//create, add and return a shared_ptr< RampItem<T> >
		shared_ptr< RampItem<T> > addValuePtr(T* value, float u, EaseFunc ease = Ease::Linear)
		{
			return addValue( shared_ptr< RampItem<T> >( new RampItem<T>( value, u, ease) ) );
		}
		
		//add and return a shared_ptr< RampItem<T> >
		shared_ptr< RampItem<T> > addValue( shared_ptr< RampItem<T> > rampItem)
		{
			values.push_back( rampItem );
			
			sortValues();
			
			return rampItem;
		}
		
		void remove( shared_ptr< RampItem<T> > rampItem)
		{
			auto it = find( values.begin(), values.end(), rampItem );
			if(it != values.end())
			{
				values.erase( it );
			}
		}
		
		//set the u position of a ramp item
		shared_ptr< RampItem<T> > setU( shared_ptr< RampItem<T> > item, float u )
		{
			if(item == NULL)	return item;
			
			item->setU( u );
			
			update();
			
			return item;
		}
		
		//returns the minimum u value
		float getMinU()
		{
			return values.front()->u;
		}
		
		//returns the maximum u value
		float getMaxU()
		{
			return values.back()->u;
		}
		
		//sample our curve at u and return an interpolated value
		T getValue(float u)
		{
			switch( values.size() )
			{
				case 0:
					//return something
					return T();
					
				case 1:
					//not much to do here
					return *values.front()->value_ptr;
					
				default:
					//clamp the u to our curve
					u = max( values.front()->u, min( u, values.back()->u ) );
					
					//return the interpolated value
					return getInterpolated( u );
			}
		}
		
		//this only really needs to be called when we add or move items
		void update()
		{
			sortValues();
		}
		
		//sort the values by their u value
		void sortValues()
		{
			sort( values.begin(), values.end(), compareItems );
		}
		
		//campare two RampItems using their u values
		static bool compareItems ( shared_ptr< RampItem<T> > v0, shared_ptr< RampItem<T> > v1)
		{
			return v0->u < v1->u;
		}
		
		//compare the RampItems with a u value
		static bool compareLowerBound ( shared_ptr< RampItem<T> > v, float u)
		{
			return v->u < u;
		}
		
		//samples our ramp at u and returns the value
		T getInterpolated( float u )
		{
			//our upper iterator
			auto hiIt = lower_bound( values.begin(), values.end(), u, compareLowerBound );
			
			if( hiIt == values.begin() )
			{
				//if it's first return the first
				return *(*hiIt)->value_ptr;
			}
			else
			{
				//get a out lower iterator
				auto lowIt = hiIt;
				lowIt--;
				
				//the distance between our iterators for normalizing the lerp
				float dist = (*hiIt)->u - (*lowIt)->u;
				
				if(dist == 0)
				{
					//don't divide by 0
					return *(*hiIt)->value_ptr;
				}
				else
				{
					//interpolate between our two iterators
					u -= (*lowIt)->u;
					auto amount = u / dist;
					return lerp( *(*lowIt)->value_ptr, *(*hiIt)->value_ptr, (*lowIt)->ease( amount ) );
				}
			}
		}
		
		//vars
		vector< shared_ptr< RampItem<T> > > values;
	};
}
