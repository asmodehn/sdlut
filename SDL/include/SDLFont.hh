#ifndef SDLFONT_HH
#define SDLFONT_HH


#include "SDLConfig.hh"
#include "SDLColor.hh"

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

	friend class RGBSurface; // to access render()

public:
	typedef enum { Solid, Shaded, Blended } RenderMode;

#ifdef HAVE_SDLTTF
private:
        TTF_Font * _font;
protected:
	//The Background color is used only if RenderMode = Shaded otherwise the background is transparent.
	//Are all those different way of rendering text really usefull ??
	SDL_Surface* render(std::string text, Color c, RenderMode mode, Color bgc = Color()) const;

public:
	Font(std::string filename, int ptsize = 16) throw (std::logic_error);
	~Font();
	

#endif



};

	}
}

#endif
