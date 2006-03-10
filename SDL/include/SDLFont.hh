#ifndef SDLFONT_HH
#define SDLFONT_HH


#include "SDLConfig.hh"

/**
 * \class Font
 *
 * \ingroup Text
 *
 * \brief This class handles Font Display
 *
 * This class wraps TTF_Font, provided by SDL_ttf if present, otherwise uses a standard default font to provide a minimum set of functions
 *
 * \note
 *
 * \author Alex
 *
 * \date 2006/03/10
 *
 * Contact: asmodehn@gna.org
 *
 */

class Font {

#ifdef HAVE_SDLTTF
        TTF_Font * _font;
#endif



};


#endif
