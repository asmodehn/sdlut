#ifndef Image_HH
#define Image_HH

#include "Video/internal/SDLRGBSurface.hh"
#include "Video/internal/OpenGL/SDLGLSurface.hh"

#include "Video/Rect.hh"
#include "Video/Color.hh"

namespace SDLut
{
namespace video
{

/**
 * \class Image
 * \ingroup SDLut_Video
 *
 * \brief This class handles an Image
 *
 * This class hides the details of implementation of 2D images
 *
 * \author Alex
 *
 * \date 2010\03\19
 *
 * contact : asmodehn@gna.org
 */


class Image
{
    friend class ImageLoader; // to access conversion constructors
    friend class ScreenBuffer;// to access m_img

protected:
#ifdef WK_OPENGL_FOUND
    std::auto_ptr<internal::OGL::GLSurface> m_img;
#else
    std::auto_ptr<internal::RGBSurface> m_img;
#endif

#ifdef WK_OPENGL_FOUND
    ///Conversion Constructor with explicit ownership transfert
    explicit Image(std::auto_ptr<internal::OGL::GLSurface> s) throw (std::logic_error);
#endif
//this is also valid in OpenGL : a GL surface will be made from RGB surfaces

    ///Conversion Constructor with explicit ownership transfert
    explicit Image(std::auto_ptr<internal::RGBSurface> s) throw (std::logic_error);


public:

    //Constructor
    //BPP should NEVER be == 0 !!!!
    Image( unsigned int width = 0, unsigned int height = 0, unsigned short bpp = 8,
           bool alpha = false,
           bool colorkey = false,
           bool hardware = false
         ) throw (std::logic_error);

    Image( void * pixeldata, int depth, int pitch, unsigned int width,unsigned int height
         ) throw (std::logic_error);

    Image(const Image &);

    ~Image();

    bool saveBMP ( std::string filename);

    //bool convertToDisplayFormat( Renderer r = SDL );

    /**
     * Resize the Image to the given dimensions if dimensions varies from the Image's dimensions
     *
     * @width: future width of the image
     * @height: future height of the image
     *
     * return true if resize successful or not needed
     */
    bool resize(unsigned int width, unsigned int height);

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

    unsigned int getHeight(void) const
    {
        return m_img->getHeight();
    }

    unsigned int getWidth(void) const
    {
        return m_img->getWidth();
    }

    Color getpixel(unsigned int x, unsigned int y) const;
    void setpixel(unsigned int x, unsigned int y, const Color & pixel);

    //TODO : set alpha of the surface, using colorkey if possible ( alpha = 255 and SDL )
    //setAlpha(unsigned char alpha);

    /**
     * Reset the colorkey the image
     *
     * @ckey, true set the colorKey, false remove it
     * @ck, the colorKey value
     *
     * Return: true if everything went fine, false otherwise
     */
    bool resetColorKey(bool ckey, Color ck );

    /**
     * Get the colorkey of the image
     *
     * Return: the Colorkey or exception if no colorKey set.
     */
    Color getColorKey();

    bool hasColorKey();

    /**
     * Reset the global alpha value of the image
     *
     * @val, the global alpha value [0..255]. 255 is opaque, 0 is transparent.
     *
     * Return: true if everything went fine, false otherwise
     */
    bool resetGlobalAlpha(int val = 255);


    /**
     * Get the global Alpha value
     * Return: the alpha value. (255 means no global alpha)
     */
    int getGlobalAlpha();

};





} //SDL

} // SDLut

#endif //Image_HH
