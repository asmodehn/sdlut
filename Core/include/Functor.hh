#ifndef CORE_FUNCTOREXT_HH
#define CORE_FUNCTOREXT_HH


#include <functional>

/** Implements extension to functional objects already existing in STL
 *
 */

namespace Core
{

//need to extend std:: to support mem_fun, ptr_fun for more arguments
namespace stdext
{

template <class Result>
struct nullary_function
{
    typedef Result result_type;
};

///Extension for 3 arguments

template <class Arg1, class Arg2, class Arg3, class Result>
struct ternary_function
{
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Arg3 third_argument_type;
    typedef Result result_type;
};

template <class Predicate> class ternary_negate
        : public ternary_function <typename Predicate::first_argument_type,
        typename Predicate::second_argument_type,
        typename Predicate::third_argument_type, bool>
{
protected:
    Predicate fn;
public:
    explicit ternary_negate ( const Predicate& pred ) : fn (pred) {}
    bool operator() (const typename Predicate::first_argument_type& x,
                     const typename Predicate::second_argument_type& y,
                     const typename Predicate::third_argument_type& z) const
    {
        return !fn(x,y,z);
    }
};


template <class Arg1, class Arg2, class Arg3, class Result>
class pointer_to_ternary_function : public ternary_function <Arg1,Arg2,Arg3,Result>
{
protected:
    Result(*pfunc)(Arg1,Arg2,Arg3);
public:
    explicit pointer_to_ternary_function ( Result (*f)(Arg1,Arg2,Arg3) ) : pfunc (f) {}
    Result operator() (Arg1 x, Arg2 y, Arg3 z) const
    {
        return pfunc(x,y,z);
    }
};

template <class S, class T, class A, class B>
class mem_fun2_t : public ternary_function <T*,A,B,S>
{
    S (T::*pmem)(A,B);
public:
    explicit mem_fun2_t ( S (T::*p)(A,B) ) : pmem (p) {}
    S operator() (T* p, A x, B y) const
    {
        return (p->*pmem)(x,y);
    }
};



template <class S, class T, class A, class B>
class const_mem_fun2_t : public ternary_function <T*,A,B,S>
{
    S (T::*pmem)(A,B) const;
public:
    explicit const_mem_fun2_t ( S (T::*p)(A,B) const ) : pmem (p) {}
    S operator() (T* p, A x, B y) const
    {
        return (p->*pmem)(x,y);
    }
};

template <class S, class T, class A, class B> mem_fun2_t<S,T,A,B> mem_fun (S (T::*f)(A,B))
{
    return mem_fun2_t<S,T,A,B>(f);
}


template <class S, class T, class A, class B> const_mem_fun2_t<S,T,A,B> mem_fun (S (T::*f)(A,B) const)
{
    return const_mem_fun2_t<S,T,A,B>(f);
}

template <class S, class T, class A, class B>
class mem_fun2_ref_t : public ternary_function <T,A,B,S>
{
    S (T::*pmem)(A,B);
public:
    explicit mem_fun2_ref_t ( S (T::*p)(A,B) ) : pmem (p) {}
    S operator() (T& p, A x, B y) const
    {
        return (p.*pmem)(x,y);
    }
};



template <class S, class T, class A, class B>
class const_mem_fun2_ref_t : public ternary_function <T,A,B,S>
{
    S (T::*pmem)(A,B) const;
public:
    explicit const_mem_fun2_ref_t ( S (T::*p)(A,B) const ) : pmem (p) {}
    S operator() (const T& p, A x, B y) const
    {
        return (p.*pmem)(x,y);
    }
};

template <class S, class T, class A, class B> mem_fun2_ref_t<S,T,A,B> mem_fun_ref (S (T::*f)(A,B))
{
    return mem_fun2_ref_t<S,T,A,B>(f);
}


template <class S, class T, class A, class B> const_mem_fun2_ref_t<S,T,A,B> mem_fun_ref (S (T::*f)(A,B) const)
{
    return const_mem_fun2_ref_t<S,T,A,B>(f);
}

/*
template <class Operation> class binder1st
            : public binary_function <typename Operation::second_argument_type,
            typename Operation::third_argument_type,
            typename Operation::result_type>
{
protected:
    Operation op;
    typename Operation::first_argument_type value;
public:
    binder1st ( const Operation& x,
                const typename Operation::first_argument_type& y) : op (x), value(y) {}
    typename Operation::result_type
    operator() (const typename Operation::second_argument_type& x,
                const typename Operation::thirdargument_type & y) const
    {
        return op(value,x,y);
    }
};
*/

///Extension for 4 arguments

template <class Arg1, class Arg2, class Arg3, class Arg4, class Result>
struct quaternary_function
{
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Arg3 third_argument_type;
    typedef Arg4 forth_argument_type;
    typedef Result result_type;
};


template <class Predicate> class quaternary_negate
        : public quaternary_function <typename Predicate::first_argument_type,
        typename Predicate::second_argument_type,
        typename Predicate::third_argument_type,
        typename Predicate::forth_argument_type, bool>
{
protected:
    Predicate fn;
public:
    explicit quaternary_negate ( const Predicate& pred ) : fn (pred) {}
    bool operator() (const typename Predicate::first_argument_type& x,
                     const typename Predicate::second_argument_type& y,
                     const typename Predicate::third_argument_type& z,
                     const typename Predicate::forth_argument_type& t) const
    {
        return !fn(x,y,z,t);
    }
};


template <class Arg1, class Arg2, class Arg3, class Arg4, class Result>
class pointer_to_quaternary_function : public quaternary_function <Arg1,Arg2,Arg3,Arg4,Result>
{
protected:
    Result(*pfunc)(Arg1,Arg2,Arg3,Arg4);
public:
    explicit pointer_to_quaternary_function ( Result (*f)(Arg1,Arg2,Arg3,Arg4) ) : pfunc (f) {}
    Result operator() (Arg1 x, Arg2 y, Arg3 z, Arg4 t) const
    {
        return pfunc(x,y,z,t);
    }
};


template <class S, class T, class A, class B, class C>
class mem_fun3_t : public quaternary_function <T*,A,B,C,S>
{
    S (T::*pmem)(A,B,C);
public:
    explicit mem_fun3_t ( S (T::*p)(A,B,C) ) : pmem (p) {}
    S operator() (T* p, A x, B y, C z) const
    {
        return (p->*pmem)(x,y,z);
    }
};


template <class S, class T, class A, class B, class C>
class const_mem_fun3_t : public quaternary_function <T*,A,B,C,S>
{
    S (T::*pmem)(A,B,C)const;
public:
    explicit const_mem_fun3_t ( S (T::*p)(A,B,C) const ) : pmem (p) {}
    S operator() (const T* p, A x, B y, C z) const
    {
        return (p->*pmem)(x,y,z);
    }
};

template <class S, class T, class A, class B, class C> const_mem_fun3_t<S,T,A,B,C> mem_fun (S (T::*f)(A,B,C)const)
{
    return const_mem_fun3_t<S,T,A,B,C>(f);
}

template <class S, class T, class A, class B, class C> mem_fun3_t<S,T,A,B,C> mem_fun (S (T::*f)(A,B,C))
{
    return mem_fun3_t<S,T,A,B,C>(f);
}



template <class S, class T, class A, class B, class C>
class mem_fun3_ref_t : public quaternary_function <T,A,B,C,S>
{
    S (T::*pmem)(A,B,C);
public:
    explicit mem_fun3_ref_t ( S (T::*p)(A,B,C) ) : pmem (p) {}
    S operator() (T& p, A x, B y, C z) const
    {
        return (p.*pmem)(x,y,z);
    }
};


template <class S, class T, class A, class B, class C>
class const_mem_fun3_ref_t : public quaternary_function <T,A,B,C,S>
{
    S (T::*pmem)(A,B,C)const;
public:
    explicit const_mem_fun3_ref_t ( S (T::*p)(A,B,C) const ) : pmem (p) {}
    S operator() (const T& p, A x, B y, C z) const
    {
        return (p.*pmem)(x,y,z);
    }
};

template <class S, class T, class A, class B, class C> const_mem_fun3_ref_t<S,T,A,B,C> mem_fun_ref (S (T::*f)(A,B,C)const)
{
    return const_mem_fun3_ref_t<S,T,A,B,C>(f);
}

template <class S, class T, class A, class B, class C> mem_fun3_ref_t<S,T,A,B,C> mem_fun_ref (S (T::*f)(A,B,C))
{
    return mem_fun3_ref_t<S,T,A,B,C>(f);
}

/*
template <class Operation> class binder1st
            : public binary_function <typename Operation::second_argument_type,
            typename Operation::third_argument_type,
            typename Operation::forth_argument_type,
            typename Operation::result_type>
{
protected:
    Operation op;
    typename Operation::first_argument_type value;
public:
    binder1st ( const Operation& x,
                const typename Operation::first_argument_type& y) : op (x), value(y) {}
    typename Operation::result_type
    operator() (const typename Operation::second_argument_type& x,
                const typename Operation::third_argument_type & y,
                const typename Operation::forth_argument_type & z) const
    {
        return op(value,x,y,z);
    }
};
*/

///Extension for 5 arguments

template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Result>
struct quinary_function
{
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Arg3 third_argument_type;
    typedef Arg4 forth_argument_type;
    typedef Arg5 fifth_argument_type;
    typedef Result result_type;
};


template <class Predicate> class quinary_negate
        : public quinary_function <typename Predicate::first_argument_type,
        typename Predicate::second_argument_type,
        typename Predicate::third_argument_type,
        typename Predicate::forth_argument_type,
        typename Predicate::fifth_argument_type, bool>
{
protected:
    Predicate fn;
public:
    explicit quinary_negate ( const Predicate& pred ) : fn (pred) {}
    bool operator() (const typename Predicate::first_argument_type& x,
                     const typename Predicate::second_argument_type& y,
                     const typename Predicate::third_argument_type& z,
                     const typename Predicate::forth_argument_type & t,
                     const typename Predicate::fifth_argument_type & u) const
    {
        return !fn(x,y,z,t,u);
    }
};



template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Result>
class pointer_to_quinary_function : public quinary_function <Arg1,Arg2,Arg3,Arg4,Arg5,Result>
{
protected:
    Result(*pfunc)(Arg1,Arg2,Arg3,Arg4,Arg5);
public:
    explicit pointer_to_quinary_function ( Result (*f)(Arg1,Arg2,Arg3,Arg4,Arg5) ) : pfunc (f) {}
    Result operator() (Arg1 x, Arg2 y, Arg3 z, Arg4 t, Arg5 u) const
    {
        return pfunc(x,y,z,t,u);
    }
};



template <class S, class T, class A, class B, class C, class D>
class mem_fun4_t : public quinary_function <T*,A,B,C,D,S>
{
    S (T::*pmem)(A,B,C,D);
public:
    explicit mem_fun4_t ( S (T::*p)(A,B,C,D) ) : pmem (p) {}
    S operator() (T* p, A x, B y, C z, D t) const
    {
        return (p->*pmem)(x,y,z,t);
    }
};
template <class S, class T, class A, class B, class C, class D>
class const_mem_fun4_t : public quinary_function <T*,A,B,C,D,S>
{
    S (T::*pmem)(A,B,C,D)const;
public:
    explicit const_mem_fun4_t ( S (T::*p)(A,B,C,D) const ) : pmem (p) {}
    S operator() (const T* p, A x, B y, C z, D t) const
    {
        return (p->*pmem)(x,y,z,t);
    }
};

template <class S, class T, class A, class B, class C, class D> const_mem_fun4_t<S,T,A,B,C,D> mem_fun (S (T::*f)(A,B,C,D)const )
{
    return const_mem_fun4_t<S,T,A,B,C,D>(f);
}

template <class S, class T, class A, class B, class C, class D> mem_fun4_t<S,T,A,B,C,D> mem_fun (S (T::*f)(A,B,C,D))
{
    return mem_fun4_t<S,T,A,B,C,D>(f);
}


template <class S, class T, class A, class B, class C, class D>
class mem_fun4_ref_t : public quinary_function <T,A,B,C,D,S>
{
    S (T::*pmem)(A,B,C,D);
public:
    explicit mem_fun4_ref_t ( S (T::*p)(A,B,C,D) ) : pmem (p) {}
    S operator() (T& p, A x, B y, C z, D t) const
    {
        return (p.*pmem)(x,y,z,t);
    }
};
template <class S, class T, class A, class B, class C, class D>
class const_mem_fun4_ref_t : public quinary_function <T,A,B,C,D,S>
{
    S (T::*pmem)(A,B,C,D)const;
public:
    explicit const_mem_fun4_ref_t ( S (T::*p)(A,B,C,D) const ) : pmem (p) {}
    S operator() (const T& p, A x, B y, C z, D t) const
    {
        return (p.*pmem)(x,y,z,t);
    }
};

template <class S, class T, class A, class B, class C, class D> const_mem_fun4_t<S,T,A,B,C,D> mem_fun_ref (S (T::*f)(A,B,C,D)const )
{
    return const_mem_fun4_ref_t<S,T,A,B,C,D>(f);
}

template <class S, class T, class A, class B, class C, class D> mem_fun4_t<S,T,A,B,C,D> mem_fun_ref (S (T::*f)(A,B,C,D))
{
    return mem_fun4_ref_t<S,T,A,B,C,D>(f);
}

/*
template <class Operation> class binder1st
            : public quaternary_function <typename Operation::second_argument_type,
            typename Operation::third_argument_type,
            typename Operation::forth_argument_type,
            typename Operation::fifth_argument_type,
            typename Operation::result_type>
{
protected:
    Operation op;
    typename Operation::first_argument_type value;
public:
    binder1st ( const Operation& x,
                const typename Operation::first_argument_type& y) : op (x), value(y) {}
    typename Operation::result_type
    operator() (const typename Operation::second_argument_type& x,
                const typename Operation::third_argument_type & y,
                const typename Operation::forth_argument_type & z
                const typename Operation::fifth_argument_type & t) const
    {
        return op(value,x,y,z,t);
    }
};
*/

} // stdext

} //Core

#endif

