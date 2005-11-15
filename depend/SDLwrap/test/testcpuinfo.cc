
/* Test program to check SDL's CPU feature detection */

#include <stdio.h>

//TODO : MINIMUM VERSION TO BUILD THIS TEST...


#include "SDLwrap.hh"

#if SDL_VERSION_ATLEAST(1, 2, 7)
#include "SDL_cpuinfo.h"
#endif


//would be nice if we can put that in SDLwrap.hh
#ifdef __MINGW32__
#ifdef main
#undef main
#endif
#endif

int main(int argc, char *argv[])
{

#if SDL_VERSION_ATLEAST(1, 2, 7)
	printf("RDTSC %s\n", SDL_HasRDTSC() ? "detected" : "not detected");
	printf("MMX %s\n", SDL_HasMMX() ? "detected" : "not detected");
	printf("MMX Ext %s\n", SDL_HasMMXExt() ? "detected" : "not detected");
	printf("3DNow %s\n", SDL_Has3DNow() ? "detected" : "not detected");
	printf("3DNow Ext %s\n", SDL_Has3DNowExt() ? "detected" : "not detected");
	printf("SSE %s\n", SDL_HasSSE() ? "detected" : "not detected");
	printf("SSE2 %s\n", SDL_HasSSE2() ? "detected" : "not detected");
	printf("AltiVec %s\n", SDL_HasAltiVec() ? "detected" : "not detected");

#else

SDL_version compiled;
  SDL_VERSION(&compiled);
	printf("You SDL compiled version: %d.%d.%d doesnt support the cpuInfo feature\n",
			compiled.major, compiled.minor, compiled.patch);
#endif
	return(0);
}
