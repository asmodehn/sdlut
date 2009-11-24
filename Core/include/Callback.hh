#ifndef CALLBACK_HH
#define CALLBACK_HH

///Callbacks using STL functor.
///here we keep the object we need to callback

#include "Functor.hh"

namespace Core
{

/// 0 Arguments
template <class Result = void >
class Callback0Base
{
public:
    virtual Result operator()() = 0 ;
    virtual Result call() = 0;
};

template <class TClass,class Result = void >
class Callback0 : public Callback0Base<Result>
{
    TClass & m_c;
    std::mem_fun_ref_t<Result,TClass> m_f;
public:
    Callback0 ( TClass & c, Result (TClass::*f) () )
            : m_c(c),m_f(std::mem_fun_ref(f))
    {

    }
    virtual Result operator()()
    {
        return m_f(m_c);
    }
    virtual Result call()
    {
        return m_f(m_c);
    }

};

/// 0 Arguments const
template <class Result = void >
class Callback0constBase
{
public:
    virtual Result operator()() const = 0 ;
    virtual Result call() const = 0;
};


template <class TClass,class Result = void >
class Callback0const : public Callback0constBase<Result>
{
    TClass & m_c;
    std::const_mem_fun_ref_t<Result,TClass> m_f;
public:
    Callback0const ( TClass & c, Result (TClass::*f) () const )
            : m_c(c), m_f(std::mem_fun_ref(f))
    {
        m_f = std::mem_fun_ref(f);
    }
    virtual Result operator()() const
    {
        return m_f(m_c);
    }
    virtual Result call() const
    {
        return m_f(m_c);
    }
};


/// 1 Arguments

template <class Arg1,class Result = void >
class Callback1Base
{
public:
    virtual Result operator()( Arg1 ) = 0 ;
    virtual Result call( Arg1 ) = 0;
};


template <class TClass,class Arg1,class Result = void >
class Callback1 : public Callback1Base<Arg1,Result>
{
    TClass & m_c;
    std::mem_fun1_ref_t<Result,TClass,Arg1> m_f;
public:
    Callback1 ( TClass & c, Result (TClass::*f) (Arg1) )
            : m_c(c),m_f(std::mem_fun_ref(f))
    {

    }
    virtual Result operator()(Arg1 a1)
    {
        return m_f(m_c,a1);
    }
    virtual Result call(Arg1 a1)
    {
        return m_f(m_c,a1);
    }
};

/// 1 Arguments const

template <class Arg1,class Result = void >
class Callback1constBase
{
public:
    virtual Result operator()( Arg1 ) const = 0 ;
    virtual Result call( Arg1 ) const = 0;
};


template <class TClass,class Arg1,class Result = void >
class Callback1const : public Callback1constBase<Arg1,Result>
{
    const TClass & m_c;
    std::const_mem_fun1_ref_t<Result,TClass,Arg1> m_f;
public:
    Callback1const (const TClass & c, Result (TClass::*f) (Arg1) const )
            : m_c(c),m_f(std::mem_fun_ref(f))
    {}
    virtual Result operator()(Arg1 a1) const
    {
        return m_f(m_c,a1);
    }
    virtual Result call(Arg1 a1) const
    {
        return m_f(m_c,a1);
    }
};

/// 2 Arguments

template <class Arg1, class Arg2, class Result = void>
class Callback2Base
{
public:
    virtual Result operator()( Arg1, Arg2 ) = 0 ;
    virtual Result call( Arg1, Arg2 ) = 0;
};


template <class TClass,class Arg1, class Arg2, class Result = void >
class Callback2 : public Callback2Base<Arg1,Arg2,Result>
{
    TClass & m_c;
    Core::stdext::mem_fun2_ref_t<Result,TClass,Arg1,Arg2> m_f;
public:
    Callback2 ( TClass & c, Result (TClass::*f) (Arg1,Arg2) )
            : m_c(c),m_f(Core::stdext::mem_fun_ref(f))
    {}
    virtual Result operator()(Arg1 a1,Arg2 a2)
    {
        return m_f(m_c,a1,a2);
    }
    virtual Result call(Arg1 a1,Arg2 a2)
    {
        return m_f(m_c,a1,a2);
    }
};

/// 2 Arguments const

template <class Arg1,class Arg2,class Result = void >
class Callback2constBase
{
public:
    virtual Result operator()( Arg1, Arg2 ) const = 0 ;
    virtual Result call( Arg1, Arg2 ) const = 0;
};


template <class TClass,class Arg1,class Arg2,class Result = void >
class Callback2const : public Callback2constBase<Arg1,Arg2,Result>
{
    const TClass & m_c;
    Core::stdext::const_mem_fun2_ref_t<Result,TClass,Arg1,Arg2> m_f;
public:
    Callback2const (const TClass & c, Result (TClass::*f) (Arg1,Arg2) const )
            : m_c(c),m_f(Core::stdext::mem_fun_ref(f))
    {}
    virtual Result operator()(Arg1 a1, Arg2 a2) const
    {
        return m_f(m_c,a1,a2);
    }
    virtual Result call(Arg1 a1,Arg2 a2) const
    {
        return m_f(m_c,a1,a2);
    }
};

/// 3 Arguments

template <class Arg1, class Arg2, class Arg3, class Result = void>
class Callback3Base
{
public:
    virtual Result operator()(Arg1, Arg2, Arg3) = 0 ;
    virtual Result call(Arg1, Arg2, Arg3) = 0;
};

template <class TClass,class Arg1, class Arg2, class Arg3, class Result = void >
class Callback3 : public Callback3Base<Arg1,Arg2,Arg3,Result>
{
    TClass & m_c;
    Core::stdext::mem_fun3_ref_t<Result,TClass,Arg1,Arg2,Arg3> m_f;
public:
    Callback3 ( TClass & c, Result (TClass::*f) (Arg1,Arg2,Arg3) )
            : m_c(c),m_f(Core::stdext::mem_fun_ref(f))
    {}
    virtual Result operator()(Arg1 a1,Arg2 a2,Arg3 a3)
    {
        return m_f(m_c,a1,a2,a3);
    }
    virtual Result call(Arg1 a1,Arg2 a2,Arg3 a3)
    {
        return m_f(m_c,a1,a2,a3);
    }
};

/// 3 Arguments const

template <class Arg1,class Arg2,class Arg3,class Result = void >
class Callback3constBase
{
public:
    virtual Result operator()( Arg1, Arg2, Arg3 ) const = 0 ;
    virtual Result call( Arg1, Arg2, Arg3 ) const = 0;
};


template <class TClass,class Arg1,class Arg2,class Arg3,class Result = void >
class Callback3const : public Callback3constBase<Arg1,Arg2,Arg3,Result>
{
    const TClass & m_c;
    Core::stdext::const_mem_fun3_ref_t<Result,TClass,Arg1,Arg2,Arg3> m_f;
public:
    Callback3const (const TClass & c, Result (TClass::*f) (Arg1,Arg2,Arg3) const )
            : m_c(c),m_f(Core::stdext::mem_fun_ref(f))
    {}
    virtual Result operator()(Arg1 a1, Arg2 a2, Arg3 a3) const
    {
        return m_f(m_c,a1,a2,a3);
    }
    virtual Result call(Arg1 a1,Arg2 a2, Arg3 a3) const
    {
        return m_f(m_c,a1,a2,a3);
    }
};

} // Core

#endif
