
/* Test program to compare the compile-time version of SDL with the linked
   version of SDL
*/

#include <stdio.h>

#include "SDLwrap.hh"

//would be nice if we can put that in SDLwrap.hh
#ifdef __MINGW32__
#ifdef main
#undef main
#endif
#endif
int main(int argc, char *argv[])
{
    SDL::version.debug();
}
