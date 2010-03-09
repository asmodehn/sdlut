#ifndef SDLFONT_HH
#define SDLFONT_HH

#include "Video/SDLColor.hh"
#include "Math/SDLRect.hh"
#include "Video/SDLRGBSurface.hh"

#include <memory>

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

class FontImpl;
class FontExtend;

class Font
{

public:
    typedef enum { Default, Normal, Bold, Italic, Underline} Style;
    typedef enum { Solid, Shaded, Blended } RenderMode;

private:

//#ifdef WK_SDLTTF_FOUND
//    std::auto_ptr<FontExtend> pvm_font;
//#else
    std::auto_ptr<FontImpl> pvm_font;
//#endif

public:

    //constructor
    Font() throw (std::logic_error);
    //if filename not found, uses default lib
    Font(std::string filename , int ptsize = 16);

    //Copy constructor
    //duplicate the TTF pointed class to avoid side effect of further modification
    Font(const Font & font);
    //assignement operator
    Font & operator=(const Font &);

    //destructor
    ~Font();

    bool setTTF(std::string filename , int ptsize = 16);
    bool isTTFAvailable() const;

    Style getStyle() const;
    void setStyle(Style s);

    Rect getSize(const std::string& text);
    int getHeight() const;


    //Rendering
    //The Background color is used only if RenderMode = Shaded otherwise the background is transparent.
    std::auto_ptr<RGBSurface> render(std::string text, Color c, RenderMode mode, Color bgc = Color()) const;

};

}
}


#endif
