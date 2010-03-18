#ifndef SDLTHREAD_HH
#define SDLTHREAD_HH

#include "Functor.hh"
#include "System/SDLScopedLock.hh"

#include <fstream>
#include <string>
#include <memory>
#include <stdexcept>
#include <map>

//forward declaration for late time binding...
struct SDL_Thread;

namespace SDLut
{
namespace system
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

//TODO : Think of redesigning, maybe using exception to handle Thread wrapper errors ( different than underlying thread errors)
//TODO : use a similar design for Timer
//TODO : think of a thread object representing the execution of a thread... creation -> run, kill -> stop / destruction.
//Refers to Boost thread... and maybe also C++09 upcoming standard...

unsigned long getCurrentThreadID();

// these function are here to keep SDL function calls in implementation
// the client should not use them, and instead rely on the Thread class
unsigned long getThreadID(SDL_Thread *);
void runThread(SDL_Thread *&,int threadcall (void *), void *data);
int waitThread(SDL_Thread *);
void killThread(SDL_Thread *);

/*
//TODO : make a nicer Functor or delegate so I dont have to use a class template here just to store the called class instance...
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
    typedef struct
    {
        int lookupindex;
        void* data;
    } tcdata;

    //index of this ThreadCall instance in the static lookuptable
    unsigned int pvm_index;

    std::auto_ptr<tcdata> pvm_tcdata;

    //static table lookup that stores pointer to threadcall
    //has to be monitored for concurrent access...
    static std::map<unsigned int, ThreadCall* > pvm_tctable;
    static std::map<unsigned int, SDL_Thread** > pvm_threadtable;
    static Mutex mtx; //to protect the process of tread creation / termination

public:

    //static callback function who calls the right functor from the table
    static int threadcall( void* args);

    //value set to 0 by constructor if not running
    SDL_Thread* pvm_thread;

    //friend unsigned long runThread(Thread<TClass> *,int threadcall (void *), void *data);

public:
    Thread();
    Thread(const Thread & thread) throw (std::logic_error);
    ~Thread();

    void setThreadCall(TClass* instance,int (TClass::*func) ( void*), void* data);

    bool run();
    inline bool running()
    {
        return pvm_thread !=0;
    }

    int wait();
    bool kill();

    unsigned long getID();

    inline SDL_Thread & get_rSDL() const
    {
        return *pvm_thread;
    }
};


template <class TClass>
std::map<unsigned int,typename Thread<TClass>::ThreadCall* > Thread<TClass>::pvm_tctable;
template <class TClass>
std::map<unsigned int,SDL_Thread** > Thread<TClass>::pvm_threadtable;
template <class TClass>
Mutex Thread<TClass>::mtx;

template <class TClass>
int Thread<TClass>::threadcall(void* data)
{
    tcdata* calldata= static_cast<tcdata*>(data);
    typename std::map<unsigned int,ThreadCall* >::iterator itcd=pvm_tctable.find(calldata->lookupindex);
    if ( itcd == pvm_tctable.end() ) return -1; // dont start the thread, the function to call doesnt exists

    //Do the actual client callback
    int res = itcd->second->call(calldata->data);

    //critical section
    ScopedLock lock(mtx);

    //remove SDL_Thread * on end...
    std::map<unsigned int,SDL_Thread** >::iterator itth=pvm_threadtable.find(calldata->lookupindex);
    if ( itth != pvm_threadtable.end() )
    {
        *(itth->second) = 0;
        pvm_threadtable.erase(itth);
    }
    //else doesnt exists anymore ? should not happen, but it s fine...

    return res;//mutex unlock at end of scope
}

template<class TClass>
void Thread<TClass>::setThreadCall(TClass* instance,int (TClass::*func) ( void*), void* data)
{
    //critical section
    ScopedLock lock(mtx);

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
    kill();// destructor abort a running thread if needed
    //if (_cbargs != NULL)
    //	delete _cbargs, _cbargs = NULL;

    //critical section
    ScopedLock lock(mtx);

    typename std::map<unsigned int, ThreadCall*>::iterator it=pvm_tctable.find(pvm_index);
    if (it != pvm_tctable.end())
    {
        delete it->second;
        pvm_tctable.erase(it);
    }
}

//returns true if the thread has been successfully launched. A thread can be launched only once. If this thread has already been launched this will return false.
//returns false if the timer could not be launched.
template<class TClass>
bool Thread<TClass>::run()
{
    //critical section
    ScopedLock lock(mtx);

    if ( pvm_thread == 0 && pvm_threadtable.count(pvm_index) == 0)
    {
        runThread(pvm_thread,threadcall,pvm_tcdata.get());
        std::pair<std::map<unsigned int,SDL_Thread** >::iterator, bool > result = pvm_threadtable.insert(std::make_pair(pvm_index,&pvm_thread));
        return result.second;
    }
    return false;
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

//return true if wait successful. return false if waiting failed ( the thread may already have stopped for example )
template<class TClass>
int Thread<TClass>::wait()
{

    int res=-1;

    //TODO : handle problems in pvm_threadtable with exceptions
    if (pvm_thread != 0 && pvm_threadtable.count(pvm_index) != 0 )
    {
        res=waitThread(pvm_thread);

        //critical section
        ScopedLock lock(mtx);

        pvm_thread = 0;
        pvm_threadtable.erase(pvm_index);
    }
    return (res);
}

//return true if kill successful. return false if abortion failed ( the thread may already have stopped for example )
template<class TClass>
bool Thread<TClass>::kill()
{

    if ( pvm_thread != 0 && pvm_threadtable.count(pvm_index) != 0 )
    {
        killThread(pvm_thread);

        //critical section
        ScopedLock lock(mtx);

        pvm_thread = 0;
        pvm_threadtable.erase(pvm_index);
    }

    return (pvm_thread == 0 );

}

*/

}

}



#endif
