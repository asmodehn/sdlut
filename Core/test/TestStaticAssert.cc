#include "StaticAssert.hh"

int main(int argc, char* argv[])
{
    StaticAssert(true,YEAH);

    StaticAssert(0,BOUH);
     	
    return 0;
}
