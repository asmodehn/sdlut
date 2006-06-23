#ifndef SDL_TIMER_HH
#define SDL_TIMER_HH

#include "SDLConfig.hh"
#include "Functor.hh"

namespace RAGE
{
    namespace SDL
    {
			//Simple SDL_delay implementation
	    static inline void Delay(long millisec) { SDL_Delay((millisec)); }
	    static inline long GetTicks(void) { return static_cast<long>(SDL_GetTicks()); }

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
			int _index;
		    
						bool running;
			long _interval;
			void* _args;


			//static table lookup that stores pointer to callback
			static std::vector< Callback* > _cbtable;

			public:

		    	//static callback function who calls the right functor from the table
			static unsigned int callback(unsigned int, void* args);
			
			
			
			
			

			SDL_TimerID _timerid; //set after timer is started



			Timer();
			~Timer();

			void setInterval(long interval);
			void setCallback(TClass* instance, unsigned int (TClass::*func) (unsigned int, void*) , void* args);
			
			void start();
			bool stop();
		};


		template <class TClass>
				std::vector<typename Timer<TClass>::Callback* > Timer<TClass>::_cbtable;
		
		template <class TClass>
		unsigned int Timer<TClass>::callback(unsigned int interval, void* args)
		{
			cbargs* callargs= static_cast<cbargs*>(args);
			return _cbtable[callargs->lookupindex]->call(interval,callargs->args);
					
		}
		
		template<class TClass>
    		void Timer<TClass>::setCallback(TClass* instance,unsigned int (TClass::*func) (unsigned int, void*), void* args)
		{
			
			_cbtable.push_back(new Callback(instance,func));
			_args = args;
		}

		template<class TClass>
		Timer<TClass>::Timer() : running(false), _interval(0), _args(NULL), _timerid()
		{
			
			//setting the index for the current instance
			static unsigned int index=0;
			index++;
			_index = index;
			//preparing callback
			_cbtable.push_back(NULL);
		}

		template<class TClass>
		Timer<TClass>::~Timer()
		{
			if (running)
				SDL_RemoveTimer(_timerid);
		}

		template<class TClass>
		void Timer<TClass>::start()
		{
			running = true;
			cbargs* _cbargs = new cbargs();
			_cbargs->lookupindex = _index;
			_cbargs->args = _args;
			_timerid = SDL_AddTimer(_interval,callback,_cbargs);
		}

		template<class TClass>
		bool Timer<TClass>::stop()
		{
			return ! (running = !SDL_RemoveTimer(_timerid));
		}
		
		template<class TClass>
		void Timer<TClass>::setInterval(long interval)
		{
			_interval = interval;
		}
	}
}



#endif
