#include "Adapter.hh"

#include "TestCommon.hh"

#include "TestCallback.hh"

#include <iostream>

using namespace Core;

//assumed legacy invoker always have a ending void* parameter, to be able to pass any argument number to the callback
int legacy0invoker( int (*func) (void *),void *v)
{
    return func ( v);
}
int legacy1invoker( int (*func) (int, void*), int a, void* v)
{
    return  func ( a, v ) ;
}
int legacy2invoker( int (*func) (int, int, void*) , int a, int b, void*v)
{
    return func ( a, b, v);
}
int legacy3invoker( int (*func) (int, int, int, void*), int a, int b, int c, void* v)
{
    return func ( a ,b ,c, v) ;
}


int main( int argc, char * argv [] )
{

    Called cobj;

    //building  usual callback
    cbtest0.reset( new Callback0<Called,int>(cobj,&Called::func0) );

    //building the adapter around it
    Adapter0<int> ad0(cbtest0.get());
    //test
    TEST(legacy0invoker(Adapter0<int>::adapt,&ad0) == 1 );

    //the const version
    cbtest0c.reset( new Callback0const<Called,int>(cobj,&Called::func0) );
    Adapter0const<int> ad0c(cbtest0c.get());
    TEST(legacy0invoker(Adapter0const<int>::adapt,&ad0c) == 1 );

///1 argument
    cbtest1.reset(new Callback1<Called,int, int>(cobj,&Called::func1) );
    Adapter1<int,int> ad1(cbtest1.get());
    TEST(legacy1invoker(Adapter1<int,int>::adapt,1,&ad1) == 2 );

    //the const verion
    cbtest1c.reset(new Callback1const<Called,int, int>(cobj,&Called::func1) );
    Adapter1const<int,int> ad1c(cbtest1c.get());
    TEST(legacy1invoker(Adapter1const<int,int>::adapt,1,&ad1c) == 2 );

///2 arguments
    cbtest2.reset(new Callback2<Called,int,int,int>(cobj,&Called::func2) );
    Adapter2<int,int,int> ad2(cbtest2.get());
    TEST(legacy2invoker(Adapter2<int,int,int>::adapt,1,2,&ad2) == 4 );

    //the const verion
    cbtest2c.reset(new Callback2const<Called,int,int,int>(cobj,&Called::func2) );
    Adapter2const<int,int,int> ad2c(cbtest2c.get());
    TEST(legacy2invoker(Adapter2const<int,int,int>::adapt,1,2,&ad2c) == 4 );


///3 arguments
    cbtest3.reset(new Callback3<Called,int,int,int,int>(cobj,&Called::func3) );
    Adapter3<int,int,int,int> ad3(cbtest3.get());
    TEST(legacy3invoker(Adapter3<int,int,int,int>::adapt,1,2,3,&ad3) == 7 );

    //the const verion
    cbtest3c.reset(new Callback3const<Called,int,int,int,int>(cobj,&Called::func3) );
    Adapter3const<int,int,int,int> ad3c(cbtest3c.get());
    TEST(legacy3invoker(Adapter3const<int,int,int,int>::adapt,1,2,3,&ad3c) == 7 );


    return 0;
}

