#include "Callback.hh"

#include "TestCommon.hh"
#include "TestCallback.hh"

#include <iostream>

using namespace Core;

int main( int argc, char * argv [] )
{

    Called cobj;
    //NB : cobj still exist when all the callbacks are called
    // cobj is passed as a const reference in the following, and not copied.

    cbtest0.reset( new Callback0<Called,int>(cobj,&Called::func0) );
    TEST((*cbtest0)() == 1 );

    cbtest0c.reset( new Callback0const<Called,int>(cobj,&Called::func0) );
    TEST((*cbtest0)() == 1 );

    cbtest1.reset(new Callback1<Called,int, int>(cobj,&Called::func1) );
    TEST ( (*cbtest1)( 1) == 2 );

    cbtest1c.reset(new Callback1const<Called,int, int>(cobj,&Called::func1) );
    TEST ( (*cbtest1)( 1) == 2 );

    cbtest2.reset( new Callback2<Called,int,int, int>(cobj, &Called::func2) );
    TEST( (*cbtest2)(1,2) == 4);

    cbtest2c.reset( new Callback2const<Called,int,int, int>(cobj, &Called::func2) );
    TEST( (*cbtest2)(1,2) == 4);

    cbtest3.reset( new Callback3<Called,int,int,int,int>(cobj, &Called::func3) );
    TEST( (*cbtest3)(1,2,3) == 7) ;

    cbtest3c.reset( new Callback3const<Called,int,int,int,int>(cobj, &Called::func3) );
    TEST( (*cbtest3)(1,2,3) == 7) ;

    return 0;
}
