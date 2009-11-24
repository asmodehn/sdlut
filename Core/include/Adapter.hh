#ifndef ADAPTER_HH
#define ADAPTER_HH

/**
 * Set of classes going along with callback to be able to pass them to legacy C libraries expecting static fonction pointers
 */

#include "Callback.hh"

#include <stdexcept>
#include <iostream>

namespace Core
{

template<class Result=void>
class Adapter0
{
    Callback0Base<Result> * m_cb;

public:
    Adapter0( Callback0Base<Result> * cb )
            : m_cb(cb)
    {}

    static Result adapt( void * v )
    {
        Result r;
        try
        {
            Adapter0<Result>* pad = reinterpret_cast<Adapter0<Result>*>(v);
            r=pad->m_cb->call();
        }
        catch ( std::exception & e)
        {
            //TODO : manage exceptions here
            std::cerr << e.what();
        }
        return r;
    }
};


template<class Result=void>
class Adapter0const
{
    Callback0constBase<Result> * m_cb;

public:
    Adapter0const( Callback0constBase<Result> * cb )
            : m_cb(cb)
    {}

    static Result adapt( void * v )
    {
        Result r;
        try
        {
            Adapter0const<Result>* pad = reinterpret_cast<Adapter0const<Result>*>(v);
            r=pad->m_cb->call();
        }
        catch ( std::exception & e)
        {
            //TODO : manage exceptions here
            std::cerr << e.what();
        }
        return r;
    }
};


/// 1 argument
template<class Arg1, class Result=void>
class Adapter1
{
    Callback1Base<Arg1,Result> * m_cb;

public:
    Adapter1( Callback1Base<Arg1,Result> * cb )
            : m_cb(cb)
    {}

    static Result adapt(Arg1 a,void * v )
    {
        Result r;
        try
        {
            Adapter1<Arg1,Result>* pad = reinterpret_cast<Adapter1<Arg1,Result>*>(v);
            r=pad->m_cb->call(a);
        }
        catch ( std::exception & e)
        {
            //TODO : manage exceptions here
            std::cerr << e.what();
        }
        return r;
    }
};


template<class Arg1,class Result=void>
class Adapter1const
{
    Callback1constBase<Arg1,Result> * m_cb;

public:
    Adapter1const( Callback1constBase<Arg1,Result> * cb )
            : m_cb(cb)
    {}

    static Result adapt( Arg1 a, void * v )
    {
        Result r;
        try
        {
            Adapter1const<Arg1,Result>* pad = reinterpret_cast<Adapter1const<Arg1,Result>*>(v);
            r=pad->m_cb->call(a);
        }
        catch ( std::exception & e)
        {
            //TODO : manage exceptions here
            std::cerr << e.what();
        }
        return r;
    }
};



/// 2 arguments
template<class Arg1, class Arg2, class Result=void>
class Adapter2
{
    Callback2Base<Arg1,Arg2,Result> * m_cb;

public:
    Adapter2( Callback2Base<Arg1,Arg2,Result> * cb )
            : m_cb (cb)
    {}

    static Result adapt(Arg1 a,Arg2 b,void * v )
    {
        Result r;
        try
        {
            Adapter2<Arg1,Arg2,Result>* pad = reinterpret_cast<Adapter2<Arg1,Arg2,Result>*>(v);
            r=pad->m_cb->call(a,b);
        }
        catch ( std::exception & e)
        {
            //TODO : manage exceptions here
            std::cerr << e.what();
        }
        return r;
    }
};


template<class Arg1,class Arg2,class Result=void>
class Adapter2const
{
    Callback2constBase<Arg1,Arg2,Result> * m_cb;

public:
    Adapter2const( Callback2constBase<Arg1,Arg2,Result> * cb )
            : m_cb(cb)
    {}

    static Result adapt( Arg1 a, Arg2 b, void * v )
    {
        Result r;
        try
        {
            Adapter2const<Arg1,Arg2,Result>* pad = reinterpret_cast<Adapter2const<Arg1,Arg2,Result>*>(v);
            r=pad->m_cb->call(a,b);
        }
        catch ( std::exception & e)
        {
            //TODO : manage exceptions here
            std::cerr << e.what();
        }
        return r;
    }
};


/// 3 arguments
template<class Arg1, class Arg2, class Arg3, class Result=void>
class Adapter3
{
    Callback3Base<Arg1,Arg2,Arg3,Result> * m_cb;

public:
    Adapter3( Callback3Base<Arg1,Arg2,Arg3,Result> * cb )
            : m_cb (cb)
    {}

    static Result adapt(Arg1 a,Arg2 b,Arg3 c,void * v )
    {
        Result r;
        try
        {
            Adapter3<Arg1,Arg2,Arg3,Result>* pad = reinterpret_cast<Adapter3<Arg1,Arg2,Arg3,Result>*>(v);
            r=pad->m_cb->call(a,b,c);
        }
        catch ( std::exception & e)
        {
            //TODO : manage exceptions here
            std::cerr << e.what();
        }
        return r;
    }
};


template<class Arg1,class Arg2, class Arg3,class Result=void>
class Adapter3const
{
    Callback3constBase<Arg1,Arg2,Arg3,Result> * m_cb;

public:
    Adapter3const( Callback3constBase<Arg1,Arg2,Arg3,Result> * cb )
            : m_cb(cb)
    {}

    static Result adapt( Arg1 a, Arg2 b, Arg3 c,void * v )
    {
        Result r;
        try
        {
            Adapter3const<Arg1,Arg2,Arg3,Result>* pad = reinterpret_cast<Adapter3const<Arg1,Arg2,Arg3,Result>*>(v);
            r=pad->m_cb->call(a,b,c);
        }
        catch ( std::exception & e)
        {
            //TODO : manage exceptions here
            std::cerr << e.what();
        }
        return r;
    }
};


} // Core

#endif

