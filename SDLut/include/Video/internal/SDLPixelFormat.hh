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

namespace internal
{
class VideoSurface;


/**
 * \class Palette
 *
 *
 * \brief This class wraps SDL_Palette
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

//read-only access
class Palette
{
    friend class PixelFormat;

    bool pointerCopy;
protected:
    //the adress of the SLD_Palette struct should never change
    //read only_access
    const SDL_Palette * const ptm_sdl_palette;
    // protected to prevent manual creation of palette
    //maybe completely useless...
    // default : one black color
    /*Palette(int ncolors = 1) : _palette(new SDL_Palette)
    {
    	_palette->ncolors = ncolors;
    	_palette->colors = (new Color[ncolors])->_color;
    	pointerCopy = false;
    }*/
    //idem for the copy contructor
    /*Palette(const Palette & p ) : _palette(new SDL_Palette)
    {
    	_palette->ncolors = p.getNColors();
    	for (int i=0; i<_palette->ncolors ; i++)
    		_palette->colors[i] = p._palette->colors[i];
    	pointerCopy = false;
    }*/
    //to handle explicit cast from SDL
    //beware : store only a pointer...
    //so the original should not be destroyed !
    explicit Palette(const SDL_Palette* palette);

public:

    ~Palette(void);

    int getNColors(void) const;
    Color getColors(int index) const;

};




class PixelFormat
{
    //because SDLPixelColor needs to access actual SDL_PixelFormat
    friend class VideoInfo;
    friend class SDLut::video::internal::VideoSurface;
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
