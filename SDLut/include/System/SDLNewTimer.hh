#ifndef SDL_NEWTIMER_HH
#define SDL_NEWTIMER_HH

#include "Functor.hh"

#include <memory>
#include <iostream>

#include "System/SDLTimer.hh"

namespace RAGE
{
    namespace SDL
    {

    	template <class TClass>
		class NewTimer
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
	    	typedef struct { Callback* cb ; void* args;} cbargs;
		    		
			std::auto_ptr<cbargs> m_cbargs;

			//static callback function who calls the right functor from the table
			static unsigned int m_callback(unsigned int, void* args);

			SDL_TimerID m_timerid;
			
			//to prevent copy
			NewTimer( const NewTimer &) ;

		public:
		
			NewTimer();
			NewTimer(TClass* instance, unsigned int (TClass::*func) (unsigned int, void*) , void* args, unsigned int interval = 0 ) throw (std::logic_error);
			~NewTimer();

			inline bool runnning() { return m_timerid != 0 ; }

			bool abort();

		};

		template <class TClass>
				unsigned int NewTimer<TClass>::m_callback(unsigned int interval, void* args)
		{
			cbargs* callargs= static_cast<cbargs*>(args);

			//Do the actual client callback
			int res = callargs->cb->call(interval,callargs->args);

			return res;
		}

		template<class TClass>
		NewTimer<TClass>::NewTimer()
		 : m_cbargs(), m_timerid(0)
		{
		}

		template<class TClass>
		NewTimer<TClass>::NewTimer(TClass* instance,unsigned int (TClass::*func) (unsigned int, void*), void* args, unsigned int interval)
			try : m_cbargs(), m_timerid(0)
		{
			
			m_cbargs.reset(new cbargs());
			m_cbargs->cb=new Callback(instance,func);
			m_cbargs->args=args;

			m_timerid = AddGlobalTimer(interval,m_callback,m_cbargs.get());

			if (m_timerid == NULL)
				throw std::logic_error(" Creation of SDL Timer failed !" );
		}
		catch (std::exception &e )
		{
			//Cannot use log here... find a way to be more consistent with the other classes' constructor behavior
			std::cout << nl << "Exception catched in Timer Constructor !!!"  << nl <<
            e.what() << nl << GetError() << std::endl;
            //TODO : much more explicit error message...
		}

		template<class TClass>
		NewTimer<TClass>::~NewTimer()
		{
		}

		//return true if abort successful. return false if abortion failed ( the timer may already have stopped for example )
		template<class TClass>
		bool NewTimer<TClass>::abort()
		{
			//TODO, find the meaning of error / success if timer already finished ? or never existed ? 
			bool res = true;
			if ( m_timerid!= NULL )
				res = RemoveGlobalTimer(m_timerid);
			return res;
		}
		
	}//SDL
}//RAGE



#endif
