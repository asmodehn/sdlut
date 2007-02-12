#ifndef SDL_TIMER_HH
#define SDL_TIMER_HH

#include "Functor.hh"
#include <utility>
#include <map>

typedef struct _SDL_TimerID *SDL_TimerID;

namespace RAGE
{
    namespace SDL
    {
	//Simple overloaded implementations
	    void Delay(long millisec);
	    long GetTicks();

	    //these should be used through the timer class, not directly
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
		    
			bool running;
			unsigned int _interval;
			
			void* _args;


			//static table lookup that stores pointer to callback
			static std::map<unsigned int, Callback* > _cbtable;

			public:

		    	//static callback function who calls the right functor from the table
				static unsigned int callback(unsigned int, void* args);
			
			
			
			
			

			SDL_TimerID _timerid; //set after timer is started



			Timer();
			~Timer();

			void setInterval(unsigned int interval);
			void setCallback(TClass* instance, unsigned int (TClass::*func) (unsigned int, void*) , void* args);
			
			void start();
			bool stop();
		};


		template <class TClass>
				std::map<unsigned int,typename Timer<TClass>::Callback* > Timer<TClass>::_cbtable;
		
		template <class TClass>
				unsigned int Timer<TClass>::callback(unsigned int interval, void* args)
		{
			cbargs* callargs= static_cast<cbargs*>(args);
			return _cbtable[callargs->lookupindex]->call(interval,callargs->args);
					
		}
		
		template<class TClass>
				void Timer<TClass>::setCallback(TClass* instance,unsigned int (TClass::*func) (unsigned int, void*), void* args)
		{
			
			_cbtable.insert(std::make_pair(_index,new Callback(instance,func)));
			_args = args;
		}

		template<class TClass>
		Timer<TClass>::Timer() : running(false), _interval(0), _args(NULL), _timerid()
		{
			
			//setting the index for the current instance
			static unsigned int index=0;
			//TODO : change here : should start at 0
			index++;
			_index = index;
			//preparing callback
			//_cbtable.push_back(NULL);
			//useful ? really ??
		}

		template<class TClass>
		Timer<TClass>::~Timer()
		{
			if (running)
				RemoveGlobalTimer(_timerid);
		}

		template<class TClass>
		void Timer<TClass>::start()
		{
			running = true;
			cbargs* _cbargs = new cbargs();
			_cbargs->lookupindex = _index;
			_cbargs->args = _args;
			_timerid = AddGlobalTimer(_interval,callback,_cbargs);
		}

		template<class TClass>
		bool Timer<TClass>::stop()
		{
			return ! (running = !RemoveGlobalTimer(_timerid));
		}
		
		template<class TClass>
				void Timer<TClass>::setInterval(unsigned int interval)
		{
			_interval = interval;
		}
	}
}



#endif
