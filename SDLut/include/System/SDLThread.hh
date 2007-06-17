#ifndef SDLTHREAD_HH
#define SDLTHREAD_HH

#include "Functor.hh"

#include <fstream>
#include <string>
#include <memory>
#include <stdexcept>
#include <map>

//forward declaration for late time binding...
struct SDL_Thread;

namespace RAGE
{
    namespace SDL
    {

        /**
        * \class Thread
        *
        * \ingroup System
        *
        * \brief This class is a wrapper for Thread
        *
        * \author Alex
        *
        * \date 2007/06/14
        *
        * Contact: asmodehn@gna.org
        *
        */

	unsigned long getCurrentThreadID();
	
	// these function are here to keep SDL function calls in implementation
	// the client should not use them, and instead rely on the Thread class
	unsigned long getThreadID(SDL_Thread *);
	void runThread(SDL_Thread *,int threadcall (void *), void *data);
	int waitThread(SDL_Thread *);
	void killThread(SDL_Thread *);

	//TODO : make a nicer Functor por delegate so I dont have to use a class template here just to store the called class instance...
	template < class TClass >
        class Thread
        {

			//Functor for Thread Call
	    		//the only constraint about the callback function is that it should return int
	    		//and the arguments should be void* to be able to pass anything...
			
			
			class ThreadCall : public TSpecificFunctor1<TClass,int>
			{
				public:
					ThreadCall(TClass* ptobj, int (TClass::*ptfunc) (void * args))
					: TSpecificFunctor1<TClass,int>(ptobj,ptfunc)
					{
					}
			};

			//structure for arguments
	    		typedef struct { int lookupindex; void* data;} tcdata;
		    
		    	//index of this ThreadCall instance in the static lookuptable
			unsigned int pvm_index;
			
			std::auto_ptr<tcdata> pvm_tcdata;

			//static table lookup that stores pointer to threadcall
			static std::map<unsigned int, ThreadCall* > pvm_tctable;
			//static std::map<unsigned int, SDL_ThreadID* > pvm_threadtable;
			
			public:

		    	//static callback function who calls the right functor from the table
			static int threadcall( void* args);
	
			
			SDL_Thread* pvm_thread;

		friend unsigned long runThread(Thread<TClass> *,int threadcall (void *), void *data);
		
		public:
			Thread();
			Thread(const Thread & thread) throw (std::logic_error);
			~Thread();

			void setThreadCall(TClass* instance,int (TClass::*func) ( void*), void* data);
					
			void run();
			
			int wait();
			void kill();

			unsigned long getID();
			
			inline SDL_Thread & get_rSDL() const
			{
				return *pvm_thread;
			}
        };

	
		template <class TClass>
				std::map<unsigned int,typename Thread<TClass>::ThreadCall* > Thread<TClass>::pvm_tctable;
		//template <class TClass>
		//		std::map<unsigned int,SDL_ThreadID* > Thread<TClass>::_threadtable;
		
		template <class TClass>
				int Thread<TClass>::threadcall(void* data)
		{
			tcdata* calldata= static_cast<tcdata*>(data);
				typename std::map<unsigned int,ThreadCall* >::iterator itcd=pvm_tctable.find(calldata->lookupindex);
			if ( itcd == pvm_tctable.end() ) return -1; // dont start the thread, the function to call doesnt exists

			//Do the actual client callback
			int res = itcd->second->call(calldata->data);

			return res;
		}
		
		template<class TClass>
				void Thread<TClass>::setThreadCall(TClass* instance,int (TClass::*func) ( void*), void* data)
		{
			typename std::map<unsigned int, ThreadCall*>::iterator it=pvm_tctable.find(pvm_index);
			if ( it != pvm_tctable.end() )
			{
				delete it->second;
			}
			pvm_tctable[pvm_index] = new ThreadCall(instance,func);
			
			//reinit _cbargs when needed
			//if (_cbargs.get() != 0)
			//{
			//	delete _cbargs, _cbargs = NULL;
			//}
			pvm_tcdata.reset( new tcdata() );
			pvm_tcdata->lookupindex = pvm_index;
			pvm_tcdata->data = data;
		}

		template<class TClass>
		Thread<TClass>::Thread() : pvm_tcdata(0), pvm_thread(0)
		{
			
			//setting the index for the current instance
			static unsigned int index=0;
			pvm_index = index;
			index++;
			//preparing callback
			//_cbtable.push_back(NULL);
			//useful ? really ??
		}

		template<class TClass>
		Thread<TClass>::~Thread()
		{
			kill();// destructor abort a running timer if needed
			//if (_cbargs != NULL)
			//	delete _cbargs, _cbargs = NULL;
			typename std::map<unsigned int, ThreadCall*>::iterator it=pvm_tctable.find(pvm_index);
			if (it != pvm_tctable.end())
			{
				delete it->second;
				pvm_tctable.erase(it);
			}
		}

		//returns true if the timer has been successfully launched. A timer can be launched only once. If this timer has already been launched this will return false.
		//returns false if the timer could not be launched.
		//NB : a timer cannot be launched from another timer's callback. Timer may behave strangely in multithreaded applications
		template<class TClass>
		void Thread<TClass>::run()
		{
			runThread(pvm_thread,threadcall,pvm_tcdata.get());
		}
		
		template<class TClass>
		unsigned long Thread<TClass>::getID()
		{
			if  (pvm_thread != 0 )
			{
				return getThreadID(pvm_thread);
			}
			return 0;
		}

		template<class TClass>
		int Thread<TClass>::wait()
		{
			if (pvm_thread != 0 )
			{
				return waitThread(pvm_thread);
			}
			else return 0;
		}
		
		template<class TClass>
		void Thread<TClass>::kill()
		{
			if ( pvm_thread != 0 )
			{
				killThread(pvm_thread);
			}
		}

		

    }

}



#endif
