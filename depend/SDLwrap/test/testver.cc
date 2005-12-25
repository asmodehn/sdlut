
/* Test program to compare the compile-time version of SDL with the linked
   version of SDL
*/

#include <stdio.h>

#include "SDLwrap.hh"

int main(int argc, char *argv[])
{
    SDL::version.debug();
}
