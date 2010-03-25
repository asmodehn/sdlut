#ifndef SDL_RGBSURFACE_HH
#define SDL_RGBSURFACE_HH

/*******************************************************************************
 * Handle a Graphical Surface
 ******************************************************************************/

#include "Video/internal/SDLBaseSurface.hh"
#include "Video/Color.hh"
#include "System/SDLRWOps.hh"

namespace SDLut
{
namespace video
{
namespace internal
{

class RGBSurface : public BaseSurface
{
    //To be able to construct RGBSurface from Font :
    friend class Font;
    friend class FontImpl;
    friend class FontExtend;

    //To be able to construct RGBSurface from Loader :
    friend class ImageLoader;

    friend class VideoSurface;


public:
    virtual Renderer getRenderer()
    {
        return SDL;
    }

protected:

    //set to true if the convert to Display format function has been called for this surface.
    bool optimised;

    ///Conversion Constructor
    explicit RGBSurface(SDL_Surface * s) throw (std::logic_error); ///< This one should be called only by friends

    ///Conversion Constructor with explicit ownership transfert
    explicit RGBSurface(std::auto_ptr<SDL_Surface> s) throw (std::logic_error);

public :

    //Constructor
    //BPP should NEVER be == 0 !!!!
    RGBSurface( int width, int height, int bpp,
                bool alpha = false,
                bool colorkey = false,
                bool hardware = false,
                unsigned long r_mask = r_default_mask,
                unsigned long g_mask = g_default_mask,
                unsigned long b_mask = b_default_mask,
                unsigned long a_mask = a_default_mask
              ) throw (std::logic_error);

    RGBSurface( void * pixeldata, int depth, int pitch, int width, int height,
                unsigned long r_mask = r_default_mask,
                unsigned long g_mask = g_default_mask,
                unsigned long b_mask = b_default_mask,
                unsigned long a_mask = a_default_mask
              ) throw (std::logic_error);

    RGBSurface(system::RWOps& rwops) throw (std::logic_error);

public :
    //should be used as the copy constructor. But should also be able to get DisplaySurface as input...
    RGBSurface(const RGBSurface & s ) throw (std::logic_error); // deep copy
    RGBSurface& operator=(const RGBSurface& s);
    //Conversion constructor
    //NB : will get called if the Surface is not RGB only.
    //RGBSurface(const BaseSurface & s ) throw (std::logic_error);
    //RGBSurface& operator=(const BaseSurface& s);


    //Destructor
    virtual ~RGBSurface() {}

    bool resetColorKey(bool ckey, const PixelColor & key, bool rleAccel = true);
    bool resetAlpha(bool alpha, unsigned int value, bool rleAccel = true);

    //Use Standard Colors here
    //setPixel();
    //getPixel();

    /*	void setUpdateRect(int x, int y, int w, int h);
    	int update(void);
    */

    virtual bool resize(int width, int height);

    bool isSRCColorKeyset(void);
    bool isSRCAlphaset(void);

    PixelColor getColorKey();

    bool isOptimised()
    {
        return optimised;
    }
    virtual bool convertToDisplayFormat();


    //Beware ! The final blitting rectangle is saved in dest_rect.
    //blit all src into the current surface
    inline bool blit (const RGBSurface& src, Rect& dest_rect)
    {
        Rect src_rect(0,0,src.getWidth(), src.getHeight());
        return blit(src, dest_rect, src_rect);
    }
    //Blit only src_rect of src into the current surface.
    virtual bool blit (const RGBSurface& src, Rect& dest_rect, const Rect& src_rect);


    bool flip(bool vertical = true, bool horizontal = false);

    friend RAGE::Logger & operator << (RAGE::Logger & ostr, const RGBSurface & surf);

};

}
}
} //namespace SDLut::SDL

#endif
