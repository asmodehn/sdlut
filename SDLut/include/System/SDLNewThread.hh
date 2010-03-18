#ifndef SDLNEWTHREAD_HH
#define SDLNEWTHREAD_HH

#include "Functor.hh"


#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>


namespace SDLut
{
namespace system
{

/**
* \class NewThread
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

/*
//TODO : Make a NewThread without template to support callback on static and global functions. Same in newtimers.

//TODO : Think of redesigning, maybe using exception to handle Thread wrapper errors ( different than underlying thread errors)
//TODO : use a similar design for Timer

//TODO : make a nicer Functor or delegate so I dont have to use a class template here just to store the called class instance...
template < class TClass >
class NewThread
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
        ThreadCall* tc;
        void* data;
    } tcdata;

    std::auto_ptr<tcdata> m_tcdata;

public:

    //static callback function who calls the right functor from the table
    static int m_threadcall( void* args);

    //value set to 0 by constructor if not running
    SDL_Thread* m_thread;

    //to prevent copy
    NewThread(const NewThread & );

public:

    NewThread();
    NewThread(TClass* instance,int (TClass::*func) ( void*), void* data) throw (std::logic_error);
    ~NewThread();

    inline bool running()
    {
        return m_thread !=0;
    }

    int wait();

    //broken, not portable, and shouldnt be needed anyway...
    //bool kill();

    unsigned long getID();

    inline SDL_Thread & get_rSDL() const
    {
        return *m_thread;
    }
};


template <class TClass>
int NewThread<TClass>::m_threadcall(void* data)
{
    tcdata* calldata= static_cast<tcdata*>(data);

    //Do the actual client callback
    int res = calldata->tc->call(calldata->data);


    return res;
}


template<class TClass>
NewThread<TClass>::NewThread() : m_tcdata(0), m_thread(0)
{
}

template<class TClass>
NewThread<TClass>::NewThread(TClass* instance,int (TClass::*func) ( void*), void* data) throw(std::logic_error)
try :
    m_tcdata(0), m_thread(0)
{

    m_tcdata.reset( new tcdata() );
    m_tcdata->tc = new ThreadCall(instance,func);
    m_tcdata->data = data;

    runThread(m_thread,m_threadcall,m_tcdata.get());

    if (m_thread == NULL)
        throw std::logic_error(" Creation of SDL Thread failed !" );
}
catch (std::exception &e )
{
    //Cannot use log here... find a way to be more consistent with the other classes' constructor behavior
    std::cout << "Exception catched in Thread Constructor !!!"  << std::endl <<
              e.what() << std::endl;
    //TODO : much more explicit error message...
}

template<class TClass>
NewThread<TClass>::~NewThread()
{
    if (m_tcdata.get() != 0)
    {
        delete m_tcdata->tc, m_tcdata->tc = NULL;
        //m_tcdata->data managed by client
    }
}

template<class TClass>
unsigned long NewThread<TClass>::getID()
{
    if  (m_thread != 0 )
    {
        return getThreadID(m_thread);
    }
    return 0;
}

//return true if wait successful. return false if waiting failed ( the thread may already have stopped for example )
template<class TClass>
int NewThread<TClass>::wait()
{
    int res=-1;

    if (m_thread != 0 )
    {
        res=waitThread(m_thread);
    }
    return (res);
}

////return true if kill successful. return false if abortion failed ( the thread may already have stopped for example )
//template<class TClass>
//bool NewThread<TClass>::kill()
//{
//	if ( m_thread != 0 )
//	{
//		killThread(m_thread);
//	}
//	return (m_thread == 0 );
//}

*/

}

}



#endif
