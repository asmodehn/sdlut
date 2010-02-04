#ifndef TESTCOMMON_HH
#define TESTCOMMON_HH

#include <cstdlib>
#include <cassert>

#include <cstdio>

/// Common macros used in all tests
//TODO : use cppunit
//TODO : mix with ctest framework...
//TODO : get inspiration from boost/detail/lightweight test
#define TEST(x) assert( (x) );
#define TEST_FVAL(val, comp) assert( abs((val) - (comp)) < SMALL_NUMBER )

///Common classes used in all tests

///Common functions used in all tests
inline int& testErr()
{
    static int err = 0;
    return err;
}

inline int reportErrors()
{
    int errors = testErr();

    if( errors == 0 )
    {
        fprintf(stderr,"No errors detected.\n");
        return 0;
    }
    else
    {
        fprintf(stderr, "%d error(s) detected.\n", errors);
        return 1;
    }
}

#endif
