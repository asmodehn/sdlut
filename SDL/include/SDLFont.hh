#ifndef SDLFONT_HH
#define SDLFONT_HH


#include "SDLConfig.hh"

namespace RAGE
{
    namespace SDL
    {


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

//		TTF_OpenFont
//(13:16:55) XorfacX: et TTF_RenderText_Solid
//(13:17:57) XorfacX: et evidemt TTF_Font*

#endif



};

	}
}

#endif
