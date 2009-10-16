#ifndef Image_HH
#define Image_HH

/*******************************************************************************
 * Handle an Image
 ******************************************************************************/

#include "Video/SDLRGBSurface.hh"
#include "Video/SDLGLSurface.hh"

#include "Math/SDLRect.hh"
#include "Video/SDLColor.hh"

namespace RAGE
{
namespace SDL
{


class Image
{
    friend class ImageLoader;
    friend class ScreenBuffer;
    friend class Font;

    RGBSurface* m_img;

public: // TMP : until ImageLoader becomes operational

    ///Conversion Constructor
    explicit Image(RGBSurface * s) throw (std::logic_error); ///< This one should be called only by friends

    ///Conversion Constructor with explicit ownership transfert
    explicit Image(std::auto_ptr<RGBSurface> s) throw (std::logic_error);

public:

    //Constructor
    //BPP should NEVER be == 0 !!!!
    Image( int width, int height, int bpp,
           bool alpha = false,
           bool colorkey = false,
           bool hardware = false
         ) throw (std::logic_error);

    Image( void * pixeldata, int depth, int pitch, int width, int height
         ) throw (std::logic_error);

    ~Image();

    bool convertToDisplayFormat( Renderer r = SDL );

    bool resize(int width, int height, bool keepcontent = false);

    bool fill (const RGBAColor& color)
    {
        Rect dest_rect(getWidth(), getHeight());
        return fill( color, dest_rect );
    }
    bool fill (const RGBAColor& color, const Rect& dest_rect);


    //Blit src surface on this surface
    inline bool blit (const Image& src, const Point& dest_pos=Point())
    {
        Rect dest_rect(dest_pos,src.getWidth(), src.getHeight());
        return blit(src, dest_rect);
    }
    inline bool blit (const Image& src, const Point& dest_pos, const Rect& src_rect)
    {
        Rect dest_rect(dest_pos,src_rect.getw(), src_rect.geth());
        return blit(src, dest_rect, src_rect);
    }
    //Beware ! The final blitting rectangle is saved in dest_rect.
    inline bool blit (const Image& src, Rect& dest_rect)
    {
        Rect src_rect(src.getWidth(), src.getHeight());
        return blit(src, dest_rect, src_rect);
    }

    bool blit (const Image& src, Rect& dest_rect, const Rect& src_rect);

    int getHeight(void) const
    {
        return m_img->getHeight();
    }

    int getWidth(void) const
    {
        return m_img->getWidth();
    }

    RGBAColor getpixel(int x, int y)
    {
        return m_img->getpixel(x, y);
    }

    void setpixel(int x, int y, const RGBAColor & pixel)
    {
        return m_img->setpixel(x, y, pixel);
    }

};





} //SDL

} // RAGE

#endif //Image_HH
