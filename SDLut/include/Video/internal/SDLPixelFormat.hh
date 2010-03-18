#ifndef SDL_PIXELFORMAT_HH
#define SDL_PIXELFORMAT_HH

#include "Video/Color.hh"
#include "Logger.hh"
//declaring SDL_type for late binding
struct SDL_PixelFormat;

namespace SDLut
{
namespace video
{
    class ImageLoader;

    namespace internal {

class PixelFormat
{
    //because SDLPixelColor needs to access actual SDL_PixelFormat
    friend class VideoInfo;
    friend class VideoSurface;
    friend class RGBSurface;
    friend class BaseSurface;
    friend class video::ImageLoader;

    bool pointerCopy;

protected:
    //read-only access
    //the address of the SDL_PixelFormat struct should never change
    const SDL_PixelFormat* const ptm_sdl_pformat;

    //default Constructor
    PixelFormat();

    //Copy Constructor from SDL_PixelFormat
    //This handle explicit casts
    explicit PixelFormat(const SDL_PixelFormat* pf);
    //DEVELOPER BEWARE ! Don't free the original pixelformat.
    //The user should never be able to free the original pixelformat
    //nor to use SDL directly.

public: //necessary if we want to use getPixelFormat() accessor from the BaseSurface class when we're not in a PixelFormat's friend class
    virtual ~PixelFormat(void);






    virtual int getBitsPerPixel() const;
    virtual int getBytesPerPixel() const;
    virtual int getRshift() const;
    virtual int getGshift() const;
    virtual int getBshift() const;
    virtual int getAshift() const;

    virtual int getRloss() const;
    virtual int getGloss() const;
    virtual int getBloss() const;
    virtual int getAloss() const;

    //BEWARE ! sometimes this has no sense, because only the palette is set...
    //TODO : Handle this...
    virtual unsigned long getRmask() const;
    virtual unsigned long getGmask() const;
    virtual unsigned long getBmask() const;
    virtual unsigned long getAmask() const;

    virtual PixelColor getColorKey() const;
    virtual int getAlpha() const;
    Palette getPalette() const;

    //display all detected informations about pixelformat
    friend RAGE::Logger & operator << (RAGE::Logger & ostr, const PixelFormat & pformat);

    //methods for Color conversion :
    virtual PixelColor getPixelColor(const Color& color) const ;
    virtual Color getColor(const PixelColor& val) const ;

    //converting pixel color form one pixel format to another.
    virtual PixelColor convert(PixelColor pc, const PixelFormat & pf) const;

};

    }
}
} //namespace SDLut::SDL

#endif
