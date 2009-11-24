#ifndef TESTCOMMON_HH
#define TESTCOMMON_HH

#include <cstdlib>
#include <cassert>

/// Common macros used in all tests
//TODO : use cppunit
//TODO : mix with ctest framework...
#define TEST(x) assert(x);
#define TEST_FVAL(val, comp) assert( abs((val) - (comp)) < SMALL_NUMBER )

///Common classes used in all tests

///Common functions used in all tests


#endif
