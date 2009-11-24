#ifndef SDL_NEWTIMER_HH
#define SDL_NEWTIMER_HH

#include "Core.hh"

#include <memory>
#include <iostream>

#include "System/SDLTimer.hh"

namespace RAGE
{
namespace SDL
{

extern void TimerLog(const std::string& text);


//New Timer class if there is no arguments
class NewTimer
{

    template <class TClass>
    class NewTimerCallback : public Core::Callback1Base<unsigned int, unsigned int>
    {
    protected:
        friend class NewTimer; //to be able to set m_tid

        TClass & m_c;
        std::mem_fun1_ref_t<unsigned int,TClass,unsigned int> m_f;
        SDL_TimerID* m_tid;

    public:

        NewTimerCallback ( TClass & c, unsigned int (TClass::*f) (unsigned int) )
                : m_c(c),m_f(std::mem_fun_ref(f))
        {}
        virtual unsigned int operator()(unsigned int a1)
        {
            int res = m_f(m_c,a1);
            if (res == 0) *m_tid = 0;//marking the Timer as finished
            return res;
        }
        virtual unsigned int call(unsigned int a1)
        {

            int res = m_f(m_c,a1);
            if (res == 0) *m_tid = 0;//marking the Timer as finished
            return res;
        }

    };

protected: //needed in any timer
    SDL_TimerID m_timerid;

private : //these are needed only when there is no arguments

    //structure in case of no callback arguments, we still need an adapter to provide SDL with a C static function to call
    std::auto_ptr< Core::Callback1Base<unsigned int, unsigned int> > m_cb ;
    std::auto_ptr< Core::Adapter1<unsigned int, unsigned int> > m_args;

    //for safety on timer creation / deletion
    //doesnt seem the fix hte problem
    //static Mutex mtx;

protected:
    //to prevent empty timer
    NewTimer();

    //to prevent copy
    NewTimer( const NewTimer &) ;

    //return true on success ( m_timerID != 0 )
    bool start(SDL_TimerID *& tid,unsigned int interval, unsigned int callback(unsigned int,void*) , void *param);


public:

    ///NewTimer Constructor without argument
    template < class TClass>
    NewTimer(TClass& instance, unsigned int (TClass::*func) (unsigned int) , unsigned int interval = 0 ) throw (std::logic_error);

    ~NewTimer();

    inline bool running()
    {
        return m_timerid != 0 ;
    }

    bool abort();

};


template<class TClass>
NewTimer::NewTimer(TClass& instance,unsigned int (TClass::*func) (unsigned int), unsigned int interval) throw (std::logic_error)
try :
    m_timerid(0),m_cb(0),m_args(0)
{
    NewTimerCallback<TClass>* ntc = new NewTimerCallback<TClass>(instance,func);
    m_cb.reset(ntc);
    m_args.reset (new Core::Adapter1<unsigned int, unsigned int>( m_cb.get()) );

    if (! start(ntc->m_tid,interval,Core::Adapter1<unsigned int, unsigned int>::adapt,m_args.get()))
        throw std::logic_error(" Creation of SDL Timer failed !" );
}
catch (std::exception &e )
{
    //Cannot use log here... find a way to be more consistent with the other classes' constructor behavior
    TimerLog( "Exception catched in Timer Constructor !!!");
    TimerLog(e.what());
    //TODO : much more explicit error message...
}



///New Timer class when there is arguments to the timer callback
template <class TArgs>
class ArgNewTimer : protected NewTimer
{


    template< class TClass>
    class NewTimerCallback : public Core::Callback2Base<unsigned int, TArgs, unsigned int>
    {
    protected:
        friend class NewTimer; //to be able to set m_tid

        TClass & m_c;
        Core::stdext::mem_fun2_ref_t<unsigned int,TClass,unsigned int,TArgs> m_f;
        SDL_TimerID* m_tid;

    public:
        NewTimerCallback ( TClass & c, unsigned int (TClass::*f) (unsigned int, TArgs) )
                : m_c(c),m_f(Core::stdext::mem_fun_ref(f))
        {}
        virtual unsigned int operator()(unsigned int a1, TArgs a2)
        {
            int res = m_f(m_c,a1,a2);
            if (res == 0) *m_tid = 0;//marking the Timer as finished
            return res;
        }
        virtual unsigned int call(unsigned int a1, TArgs a2)
        {

            int res = m_f(m_c,a1,a2);
            if (res == 0) *m_tid = 0;//marking the Timer as finished
            return res;
        }

    };

    //class to hold arguments needed for callback
//extension of adaptor where adaptorhas different numbers of parameter than the callback..
//passing other arguments into a structure through the void* parameter
    template <class Args>
    class NewTimerArgs
    {
        Core::Callback2Base<unsigned int, Args, unsigned int> * m_cb;
        Args m_args;

    public :
        NewTimerArgs(Core::Callback2Base<unsigned int, Args,unsigned int>* cb, const Args & args )
                : m_cb(cb),m_args(args)
        {}

        static unsigned int adapt( unsigned int a, void * v )
        {
            unsigned int r;
            try
            {
                NewTimerArgs<Args>* pta = reinterpret_cast<NewTimerArgs<Args>*>(v);
                r=pta->m_cb->call(a,pta->m_args);
            }
            catch ( std::exception & e)
            {
                //TODO : manage exceptions here
                std::cerr << e.what();
            }
            return r;
        }
    };



    //stucture for callback arguments if present
    std::auto_ptr< Core::Callback2Base<unsigned int, TArgs, unsigned int> > m_cb ;
    std::auto_ptr< NewTimerArgs<TArgs> > m_args;


    //for safety on timer creation / deletion
    //doesnt seem the fix hte problem
    //static Mutex mtx;

protected:

    //to prevent empty timer
    ArgNewTimer();

    //to prevent copy
    ArgNewTimer( const ArgNewTimer &) ;

    using NewTimer::start;

public:

    ///NewTimer Constructor with argument, copied in the NewTimer until destruction.
    ///Warning : the class instance is not copied into the timer.
    template < class TClass>
    ArgNewTimer(TClass& instance, unsigned int (TClass::*func) (unsigned int, TArgs &) , TArgs & args, unsigned int interval = 0 ) throw (std::logic_error);

    ~ArgNewTimer();


    using NewTimer::running;
    using NewTimer::abort;


};

//template<class TClass>
//Mutex NewTimer<TClass>::mtx;

template<class TArgs>
ArgNewTimer<TArgs>::ArgNewTimer()
        : NewTimer(), m_cb(0), m_args(0)
{
}


template<class TArgs>
ArgNewTimer<TArgs>::ArgNewTimer(const ArgNewTimer<TArgs> & ant)
        : NewTimer(), m_cb(0), m_args(0)
{
}


template<class TArgs>
template<class TClass>
ArgNewTimer<TArgs>::ArgNewTimer(TClass& instance,unsigned int (TClass::*func) (unsigned int, TArgs &), TArgs & args, unsigned int interval) throw (std::logic_error)
try :
    NewTimer(0),m_cb(0),m_args(0)
{

    m_cb.reset(new Core::Callback2<TClass,unsigned int,TArgs&, unsigned int>(instance,func));
    m_args.reset(new NewTimerArgs<TArgs&>(m_cb,m_args));

    if ( ! start(m_cb->m_tid,interval,NewTimerArgs<TArgs&>::adapt,m_args.get()))
        throw std::logic_error(" Creation of SDL Timer failed !" );
}
catch (std::exception &e )
{
    //Cannot use log here... find a way to be more consistent with the other classes' constructor behavior
    TimerLog( "Exception catched in Timer Constructor !!!");
    TimerLog(e.what());
    //TODO : much more explicit error message...
}

template < class TArgs>
ArgNewTimer<TArgs>::~ArgNewTimer()
{
    //ALWAYS BE SURE THE TIMER IS HALTED BEFORE TRYING TO DESTRUCT IT !!
    abort();
    //TODO : think of a way to "detach" it. Destruct the Timer object, but keep the timer running... have a look at boost threads...

    //Callback and argument delete should be handled by auto_ptr...


}



}//SDL
}//RAGE



#endif
