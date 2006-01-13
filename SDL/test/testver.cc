
/* Test program to compare the compile-time version of SDL with the linked
   version of SDL
*/

#include <stdio.h>

#include "SDLwrap.hh"

int main(int argc, char *argv[])
{
    Logger testlog("testver");

    testlog << SDL::version << std::endl;

	return 0;
}
