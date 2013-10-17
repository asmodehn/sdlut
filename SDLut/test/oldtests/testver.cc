
/* Test program to compare the compile-time version of SDL with the linked
   version of SDL
*/

#include <stdio.h>

#include "SDL.hh"
using namespace RAGE;

int main(int argc, char *argv[])
{
    Logger testlog("testver");

    testlog <<SDL::App::getInstance().getVersion()<< std::endl;

	return 0;
}
