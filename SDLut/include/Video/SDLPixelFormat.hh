#ifndef SDL_PIXELFORMAT_HH
#define SDL_PIXELFORMAT_HH

#include "SDLColor.hh"
#include "Logger.hh"
//declaring SDL_type for late binding
struct SDL_PixelFormat;

namespace RAGE
{
namespace SDL
{

class PixelFormat
{
    //because SDLPixelColor needs to access actual SDL_PixelFormat
    friend class VideoInfo;
    friend class VideoSurface;
    friend class RGBSurface;
    friend class BaseSurface;
    friend class SurfaceLoader;

    bool pointerCopy;

protected:
    //read-only access
    //the address of the SDL_PixelFormat struct should never change
    const SDL_PixelFormat* const ptm_sdl_pformat;


    //Copy Constructor from SDL_PixelFormat
    //This handle explicit casts
    explicit PixelFormat(const SDL_PixelFormat* pf);
    //DEVELOPER BEWARE ! Don't free the original pixelformat.
    //The user should never be able to free the original pixelformat
    //nor to use SDL directly.

public: //necessary if we want to use getPixelFormat() accessor from the BaseSurface class when we're not in a PixelFormat's friend class
    ~PixelFormat(void);



    //default Constructor
    //PixelFormat(void) { _pformat= new SDL_PixelFormat; }
    //TODO : To avoid using uninitialized PixelFormat , put default constructor on protected
    //Really Useful ??


    int getBitsPerPixel() const;
    int getBytesPerPixel() const;
    int getRshift() const;
    int getGshift() const;
    int getBshift() const;
    int getAshift() const;

    int getRloss() const;
    int getGloss() const;
    int getBloss() const;
    int getAloss() const;

    //BEWARE ! sometimes this has no sense, because only the palette is set...
    //TODO : Handle this...
    unsigned long getRmask() const;
    unsigned long getGmask() const;
    unsigned long getBmask() const;
    unsigned long getAmask() const;

    PixelColor getColorKey() const;
    int getAlpha() const;
    Palette getPalette() const;

    //display all detected informations about pixelformat
    friend Logger & operator << (Logger & ostr, const PixelFormat & pformat);

    //methods for Color conversion :
    PixelColor getValueFromColor(const Color& color) const ;
    Color getColorFromValue(const PixelColor& val) const ;

};

}
} //namespace RAGE::SDL

#endif
