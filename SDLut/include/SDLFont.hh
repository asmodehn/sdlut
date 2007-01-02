#ifndef SDLFONT_HH
#define SDLFONT_HH


#include "SDLConfig.hh"
#include "SDLColor.hh"
#include "SDLRect.hh"
#include "SDLRGBSurface.hh"

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

private:
	//TODO : fix the problem when the TTF is absent !!!
	TTF::Font * _font;//private class to handle SDL_ttf detection and use
		//_font == NULL if TTF not available ( or unable to initialise the font )
	Default::Font * _deffont;

public:

	//constructor
	Font( int ptsize = 16) throw (std::logic_error);
	Font(std::string filename, int ptsize = 16) throw (std::logic_error);

	//Copy constructor
	//duplicate the TTF pointed class to avoid side effect of further modification
	Font(const Font & font);
	//assignement operator
	Font & operator=(const Font &);

	//destructor
	~Font();


	//Check for TTF detected and available
	bool isTTFAvailable()
	{
		return (_font != NULL) ;
	}


	//Attributes Access
	static void byteSwapUNICODE(bool swapped);

	typedef enum { Normal, Bold, Italic, Underline }Style;

	Style getStyle();
	void setStyle(Style s);
	
	int height();
	int ascent();
	int descent();
	int lineskip();
	long faces();
	bool faceIsFixedWidth();
	std::string faceFamilyName();
	std::string faceStyleName();
	Rect size(std::string text);


	//Rendering

	//The Background color is used only if RenderMode = Shaded otherwise the background is transparent.
	RGBSurface * render(std::string text, Color c, RenderMode mode, Color bgc = Color()) const;



};

	}
}


#endif
