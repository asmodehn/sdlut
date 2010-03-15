#ifndef Image_HH
#define Image_HH

/*******************************************************************************
 * Handle an Image
 ******************************************************************************/

#include "Video/internal/SDLRGBSurface.hh"
#include "Video/internal/OpenGL/SDLGLSurface.hh"

#include "Video/Rect.hh"
#include "Video/Color.hh"

namespace RAGE
{
namespace SDL
{


class Image
{
    friend class ImageLoader; // to access conversion constructors
    friend class ScreenBuffer;// to access m_img

protected:
#ifdef WK_OPENGL_FOUND
    std::auto_ptr<GLSurface> m_img;
#else
    std::auto_ptr<RGBSurface> m_img;
#endif

#ifdef WK_OPENGL_FOUND
    ///Conversion Constructor with explicit ownership transfert
    explicit Image(std::auto_ptr<GLSurface> s) throw (std::logic_error);
#endif
//this is also valid in OpenGL : a GL surface will be made from RGB surfaces

    ///Conversion Constructor with explicit ownership transfert
    explicit Image(std::auto_ptr<RGBSurface> s) throw (std::logic_error);


public:

    //Constructor
    //BPP should NEVER be == 0 !!!!
    Image( int width = 0, int height = 0, int bpp = 8,
           bool alpha = false,
           bool colorkey = false,
           bool hardware = false
         ) throw (std::logic_error);

    Image( void * pixeldata, int depth, int pitch, int width, int height
         ) throw (std::logic_error);

    Image(const Image &);

    ~Image();

    bool saveBMP ( std::string filename);

    //bool convertToDisplayFormat( Renderer r = SDL );

    bool resize(int width, int height, bool keepcontent = false);

    bool fill (const Color& color)
    {
        Rect dest_rect(0,0,getWidth(), getHeight());
        return fill( color, dest_rect );
    }
    bool fill (const Color& color, const Rect& dest_rect);


    //Blit src surface on this surface
    //Beware ! The final blitting rectangle is saved in dest_rect.
    inline bool blit (const Image& src, Rect& dest_rect)
    {
        Rect src_rect(0,0,src.getWidth(), src.getHeight());
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

    Color getpixel(int x, int y)
    {
        return m_img->getPixelFormat().getColor(m_img->getpixel(x, y));
    }

    void setpixel(int x, int y, const Color & pixel)
    {
        return  m_img->setpixel(x, y, m_img->getPixelFormat().getPixelColor( pixel));
    }

};





} //SDL

} // RAGE

#endif //Image_HH
