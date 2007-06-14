#ifndef SDL_TIMER_HH
#define SDL_TIMER_HH

#include "Functor.hh"
#include <utility>
#include <map>
#include <memory>
#include <iostream>

typedef struct _SDL_TimerID *SDL_TimerID;

namespace RAGE
{
    namespace SDL
    {
	//Simple overloaded implementations
	    void Delay(long millisec);
	    long GetTicks();

	    
		//these should be used through the timer class, not directly
		//NB : AddGlobalTimer should not be called from an other thread thant the main one. Timers will behave strangely in multithreaded applications...
		SDL_TimerID AddGlobalTimer(unsigned int interval, unsigned int callback (unsigned int, void*) , void *param);
		bool RemoveGlobalTimer(SDL_TimerID t);

			
    		template <class TClass>
		class Timer
		{

			//Functor for Timer Callback
	    		//the only constraint about the callback function is that it should return int (next interval to apply)
	    		//and the arguments should be void* to be able to pass anything...
			
			
			class Callback : public TSpecificFunctor2<TClass,unsigned int,unsigned int>
			{
				public:
					Callback(TClass* ptobj, unsigned int (TClass::*ptfunc) (unsigned int interval,void * args))
					: TSpecificFunctor2<TClass,unsigned int,unsigned int>(ptobj,ptfunc)
					{
					}

			};


			//structure for arguments
	    		typedef struct { int lookupindex; void* args;} cbargs;
		    
		    	//index of this functor instance in the static lookuptable
			unsigned int _index;
			
			std::auto_ptr<cbargs> _cbargs;

			//static table lookup that stores pointer to callback
			static std::map<unsigned int, Callback* > _cbtable;
			static std::map<unsigned int, SDL_TimerID* > _timertable;
			
			public:

		    	//static callback function who calls the right functor from the table
			static unsigned int callback(unsigned int, void* args);
	
			SDL_TimerID _timerid; //set after timer is started
			//_timerid != 0  means the timer has been launched.

			Timer();
			~Timer();

			void setCallback(TClass* instance, unsigned int (TClass::*func) (unsigned int, void*) , void* args);
			
			bool launch(unsigned int interval);
			bool abort();
		};


		template <class TClass>
				std::map<unsigned int,typename Timer<TClass>::Callback* > Timer<TClass>::_cbtable;
		template <class TClass>
				std::map<unsigned int,SDL_TimerID* > Timer<TClass>::_timertable;
		
		template <class TClass>
				unsigned int Timer<TClass>::callback(unsigned int interval, void* args)
		{
			cbargs* callargs= static_cast<cbargs*>(args);
			typename std::map<unsigned int,Callback* >::iterator itcb=_cbtable.find(callargs->lookupindex);
			if ( itcb == _cbtable.end() ) return 0; //stop callback : function to call doesnt exists

			//Do the actual client callback
			int res = itcb->second->call(interval,callargs->args);

			if ( res == 0 ) // to set timer to 0 and erase it from the list, to flag termination of timer, so it can be launched again.
			{
				std::map<unsigned int,SDL_TimerID* >::iterator ittimer=_timertable.find(callargs->lookupindex);
				if ( ittimer != _timertable.end() )
				{
					*(ittimer->second) = 0;
					_timertable.erase(ittimer);
				}
				//else doesnt exists anymore ? should not happen, but it s fine...
			}
			return res;

			//This fix the problem when calling a timer from another timer, by handling return 0 to cancel next timer call.
			//however it seems to bug from time to time in P0.
			//
			//cbargs* callargs= static_cast<cbargs*>(args);
			//typename std::map<unsigned int,Callback* >::iterator itcb=_cbtable.find(callargs->lookupindex);
			//if ( itcb == _cbtable.end() ) return 0; //stop callback : function to call doesnt exists

			////find corresponding timer
			//std::map<unsigned int,SDL_TimerID* >::iterator ittimer=_timertable.find(callargs->lookupindex);

			////Do the actual client callback if timer still exist ( not aborted or terminated )
			//int res = 0;
			//if ( ittimer != _timertable.end() )
			//{
			//	res = itcb->second->call(interval,callargs->args);
			//	if ( res == 0)
			//	{
			//		 // to set timer to 0 and erase it from the list, to flag termination of timer, so it can be launched again.
			//		*(ittimer->second) = 0;
			//		_timertable.erase(ittimer);
			//	}
			//}

			//return res;
		}
		
		template<class TClass>
				void Timer<TClass>::setCallback(TClass* instance,unsigned int (TClass::*func) (unsigned int, void*), void* args)
		{
			typename std::map<unsigned int, Callback*>::iterator it=_cbtable.find(_index);
			if ( it != _cbtable.end() )
			{
				delete it->second;
			}
			_cbtable[_index] = new Callback(instance,func);
			
			//reinit _cbargs when needed
			//if (_cbargs.get() != 0)
			//{
			//	delete _cbargs, _cbargs = NULL;
			//}
			_cbargs.reset( new cbargs() );
			_cbargs->lookupindex = _index;
			_cbargs->args = args;
		}

		template<class TClass>
		Timer<TClass>::Timer() : _cbargs(0), _timerid()
		{
			
			//setting the index for the current instance
			static unsigned int index=0;
			_index = index;
			index++;
			//preparing callback
			//_cbtable.push_back(NULL);
			//useful ? really ??
		}

		template<class TClass>
		Timer<TClass>::~Timer()
		{
			abort();// destructor abort a running timer if needed
			//if (_cbargs != NULL)
			//	delete _cbargs, _cbargs = NULL;
			typename std::map<unsigned int, Callback*>::iterator it=_cbtable.find(_index);
			if (it != _cbtable.end())
			{
				delete it->second;
				_cbtable.erase(it);
			}
		}

		//returns true if the timer has been successfully launched. A timer can be launched only once. If this timer has already been launched this will return false.
		//returns false if the timer could not be launched.
		//NB : a timer cannot be launched from another timer's callback. Timer may behave strangely in multithreaded applications
		template<class TClass>
		bool Timer<TClass>::launch(unsigned int interval)
		{
			if ( interval > 0 && _timerid == 0 && _timertable.count(_index) == 0)
			{
				_timerid = AddGlobalTimer(interval,callback,_cbargs.get());
				std::pair<std::map<unsigned int,SDL_TimerID* >::iterator, bool > result = _timertable.insert(std::make_pair(_index,&_timerid));
				return result.second;
			}
			return false;
		}

		//return true if abort successful. return false if abortion failed ( the timer may already have stopped for example )
		template<class TClass>
		bool Timer<TClass>::abort()
		{
			if (_timerid != 0 && _timertable.count(_index) != 0 && RemoveGlobalTimer(_timerid) )
			{
				_timerid = 0;
				_timertable.erase(_index);
			}
			return (_timerid == 0 );
		}
		
	}
}



#endif
