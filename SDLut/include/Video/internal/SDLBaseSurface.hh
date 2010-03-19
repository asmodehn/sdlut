#ifndef SDL_BASESURFACE_HH
#define SDL_BASESURFACE_HH


#include "Logger.hh"

#include "WkPlatform.h"
//to be able to know which renderers can be used on the platform

#include "Video/Rect.hh"
#include "Video/internal/SDLPixelFormat.hh"

#include <iostream>
#include <cassert>
#include <memory>

//declaring SDL_type for late binding
struct SDL_Surface;


namespace SDLut
{
namespace video
{
    namespace internal {

///defining a enumeration for renderers availables
///here because must be available for both video and rgb surfaces
#ifdef WK_OPENGL_FOUND
enum Renderer { SDL, OpenGL };
#else
enum Renderer { SDL };
#endif


/**
 * \class BaseSurface
 *
 *
 * \brief Abstract Class to manage Surfaces
 *
 * Abstract Class to handle common behaviour between display surface
 * and other surface types...
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

//TODO : make this class pure virtual one (how then?)... and manage creation of _surf with exception
//in the derivating tree
//The goal is to have _surf and this really tied.
class BaseSurface
{
    friend class ScreenBuffer;

public:
    ///To enable external classes to retrive the renderer which must be defined in all classes
    ///This type of detection avoid dynamic casts, which can be annoying and shouldnt be common anyway.
    virtual Renderer getRenderer() = 0;

protected:

    //Moved out of RGBSurface, because VideoSurface might need those sometime...
    //SDL interprets each pixel as a 32-bit number, so our masks must depend
    //on the endianness (byte order) of the machine
    //Here we setup the default internal pixel format : RGBA
#if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
    static const unsigned long r_default_mask = 0xff000000;
    static const unsigned long g_default_mask = 0x00ff0000;
    static const unsigned long b_default_mask = 0x0000ff00;
    static const unsigned long a_default_mask = 0x000000ff;
#else // SDL_BYTEORDER == SDL_LIL_ENDIAN
    static const unsigned long r_default_mask = 0x000000ff;
    static const unsigned long g_default_mask = 0x0000ff00;
    static const unsigned long b_default_mask = 0x00ff0000;
    static const unsigned long a_default_mask = 0xff000000;
#endif
    static const unsigned short bpp_default_alpha = 32;
    static const unsigned short bpp_default_noalpha = 24;

    //TODO : improve wrapping with const SDL_Surface * // or maybe (const?) SDL_Surface &
    //... look at SDL_video.h to access correctly to SDL_Surface like as for PixelFormat and everything else

    //the adress of SDL_Surface struct should never change
    //SDL_Surface * const _surf;
    //except for resize...
    std::auto_ptr<SDL_Surface> ptm_surf; ///< the actual allocated surface

    const PixelFormat * ptm_pformat; //container for the SDL_PixelFormat embedded in the SDL_Surface

public: //useful else we can't access those functions outside of friend class (for example in GuiChan)


    /// This method return true if the surface is initialized, false otherwise.
    bool initialized() const
    {
        return ptm_surf.get() != 0;
    }
    //could be useless if exception handle is well coded in the heriting tree


    ///This method return true if all is OK,or if it doesn't need being locked/unlocked.
    ///it return false only if this cannot be locked...
    bool lock(void);
    bool unlock(void);

    virtual PixelColor getpixel(int x, int y);
    virtual void setpixel(int x, int y, PixelColor pixel);

protected:
    //Default Constructor overload
    BaseSurface();
    ///< should be called only by subclasses

    ///RAII Conversion Constructor
    explicit BaseSurface(SDL_Surface * s);
    ///< should be called only by subclasses

    ///RAII Conversion Constructor with explicit ownership transfer as it s using an auto_ptr
    explicit BaseSurface(std::auto_ptr<SDL_Surface> s);
    ///< should be called only by subclasses

    ///to assign a surface to a BaseSurface
    bool set_SDL_Surface(SDL_Surface * s);
    ///< should be called only by subclasses

    ///to assign a surface to a BaseSurface
    bool set_SDL_Surface(std::auto_ptr<SDL_Surface> s);
    ///< should be called only by subclasses

    /** \brief Copy constructor overload.
      */
    BaseSurface(const BaseSurface & s);
    BaseSurface(const BaseSurface & s , unsigned long flags, PixelFormat pfmt);

    /** \brief assignement operator overload.
    */
    BaseSurface& operator=(const BaseSurface& s);

    ///<usefull accessor for children only
    unsigned long getFlags(void) const;

    ///<protected because parameter const differs between derivates
    bool blit(const BaseSurface& src, Rect& dest_rect, const Rect& src_rect );

public:

    /// Virtual Destructor
    virtual ~BaseSurface();

    ///Accessors

protected:

    //usefull to get the SDL structure
    const SDL_Surface * get_pSDL() const
    {
        return ptm_surf.get();
    }

public:
    //usefull to get the SDL structure without no risk of modifying it
    SDL_Surface get_SDL() const;

    const SDL_Surface & get_rSDL() const
    {
        return *ptm_surf; // Indirection of auto_ptr ???? -> TO INVESTIGATE....
    }

public:
    unsigned int getHeight(void) const;
    unsigned int getWidth(void) const;

    Rect getSize() const
    {
        return Rect(0,0,getWidth(),getHeight());
    }

    int getBPP(void) const;
    bool isSWset(void) const;
    bool isHWset(void) const;
    bool isHWAccelset(void) const;
    bool isRLEAccelset(void) const;
    bool isPreAllocset(void) const;

    //if not NULL, contains the raw pixel data for the surface
    //shouldnt be public -> format problems, managed by pixel format
    //TO FIX
    void * getpixels(void) const;

    ///Accessor to pixelFormat
    virtual const PixelFormat& getPixelFormat(void) const;

    //Set the clip rect
    //Default Reset the clip rect to the full size of the surface
    inline void setClipRect(void)
    {
        return setClipRect(Rect(0,0,getWidth(),getHeight()));
    }
    void setClipRect(const Rect& rect);
    //get the clip rect
    Rect getClipRect(void) const;

    //save the surface to a BMP file.
    bool saveBMP(std::string filename) const;
    //TODO : the same with other formats

    //Fill
    virtual bool fill (const PixelColor& color);
    virtual bool fill (const PixelColor& color, Rect dest_rect);


public:
    bool resize(const Rect & r)
    {
        return resize(r.getw(),r.geth());
    }

    virtual bool resize(int width, int height) = 0;

    friend RAGE::Logger & operator << (RAGE::Logger & ostr, const BaseSurface & surf);

};

    }
}
} //namespace SDLut::SDL

#endif
