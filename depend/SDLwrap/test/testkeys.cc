
/* Print out all the keysyms we have, just to verify them */

#include <stdio.h>
#include <ctype.h>

#include "SDLwrap.hh"

//would be nice if we can put that in SDLwrap.hh
#ifdef __MINGW32__
#ifdef main
#undef main
#endif
#endif
int main(int argc, char *argv[])
{
	SDLKey key;

	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n",
							SDL_GetError());
		exit(1);
	}
	for ( key=SDLK_FIRST; key<SDLK_LAST; key=static_cast<SDLKey>(1+(int)key) ) {
		printf("Key #%d, \"%s\"\n", key, SDL_GetKeyName(key));
	}
	SDL_Quit();
	return(0);
}
