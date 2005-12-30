
/* Print out all the keysyms we have, just to verify them */

#include <stdio.h>
#include <ctype.h>

#include "SDLwrap.hh"

int main(int argc, char *argv[])
{
	SDLKey key;

    //Call to SDL_Init needed to get the Key code....
    SDL::App::getInstance().initVideo();

	for ( key=SDLK_FIRST; key<SDLK_LAST; key=static_cast<SDLKey>(1+(int)key) ) {
		printf("Key #%d, \"%s\"\n", key, SDL_GetKeyName(key));
	}
	return(0);
}
