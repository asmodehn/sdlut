#include "Video/Image.hh"
#include "SDLConfig.hh"

#include "SDLApp.hh"
//here just to be able to access the Manager without explicitly showing it in the interface
//as the interface might be used directly by the client...
//TODO : Have a Singleton containing the settings of the Application, available everywhere through SDLConfig.hh

namespace SDLut
{
namespace video
{

#ifdef WK_SDLut_FOUND_OPENGL

///Conversion Constructor with explicit ownership transfert
Image::Image(std::auto_ptr<internal::OGL::GLSurface> s) throw (std::logic_error)
        : m_img(NULL)
{
    m_img=s;
    if ( m_img.get() == NULL ) throw std::logic_error("Error in image Conversion Constructor!!!");
}
#endif // WK_SDLut_FOUND_OPENGL_

///Conversion Constructor

///Conversion Constructor with explicit ownership transfert
Image::Image(std::auto_ptr<internal::RGBSurface> s) throw (std::logic_error)
        : m_img(NULL)
{
#ifdef WK_SDLut_FOUND_OPENGL
    m_img.reset(new internal::OGL::GLSurface(*s));// conversion if needed
#else
    m_img=s;
#endif
    if ( m_img.get() == NULL ) throw std::logic_error("Error in image Conversion Constructor!!!");
}



//Constructor
//BPP should NEVER be == 0 !!!!
Image::Image( unsigned int width, unsigned int height, unsigned short bpp,
              bool alpha,
              bool colorkey,
              bool hardware
            ) throw (std::logic_error)

{
#ifdef WK_SDLut_FOUND_OPENGL
    m_img.reset(new internal::OGL::GLSurface(width, height, bpp, alpha, colorkey, hardware));
#else
    m_img.reset(new internal::RGBSurface(width, height, bpp, alpha, colorkey, hardware));
#endif
}


Image::Image( void * pixeldata, int depth, int pitch, unsigned int width, unsigned int height
            ) throw (std::logic_error)
{

#ifdef WK_SDLut_FOUND_OPENGL
    m_img.reset(new internal::OGL::GLSurface(pixeldata, depth, pitch, width, height));
#else
    m_img.reset(new internal::RGBSurface(pixeldata, depth, pitch, width, height));
#endif
}

Image::Image(const Image & img)
        : m_img(NULL)
{

#ifdef WK_SDLut_FOUND_OPENGL
    m_img.reset(new internal::OGL::GLSurface(*(img.m_img)));
#else
    m_img.reset(new internal::RGBSurface(*(img.m_img)));
#endif

}

Image::~Image()
{
}

bool Image::saveBMP( std::string filename )
{
    return m_img->saveBMP(filename);
}

bool Image::resize(unsigned int width, unsigned int height)
{
    bool res = true;
    if (m_img->getWidth() != width || m_img->getHeight() != height)
        res = m_img->resize(width, height);

    return res;
}


bool Image::fill (const Color& color, const Rect& dest_rect)
{
    return m_img->fill(m_img->getPixelFormat().getPixelColor(color),dest_rect);
}

bool Image::blit (const Image& src, Rect& dest_rect, const Rect& src_rect)
{
    m_img->blit( *(src.m_img), dest_rect, src_rect );
    return true; //todo
}

Color Image::getpixel(unsigned int x, unsigned int y) const
{
    Color res;
    //We need to check the pixel is in the image
    if (x >= 0 && y >= 0 && x < getWidth() && y < getHeight())
    {
        res = m_img->getPixelFormat().getColor(m_img->getpixel(x, y));
    }
    else
    {
        throw std::logic_error("Trying to get a pixel outside of Image range");
    }
    return res;
}

void Image::setpixel(unsigned int x, unsigned int y, const Color & pixel)
{
    //We need to check the pixel is in the image
    if (x >= 0 && y >= 0 && x < getWidth() && y < getHeight())
    {
        m_img->setpixel(x, y, m_img->getPixelFormat().getPixelColor( pixel));
    }
    else
    {
        throw std::logic_error("Trying to pu a pixel outside of Image range");
    }
}

bool Image::resetColorKey(bool ckey, Color ck)
{
    return m_img->resetColorKey(ckey, m_img->getPixelFormat().getPixelColor( ck ) );
}

Color Image::getColorKey()
{
    return m_img->getPixelFormat().getColor(m_img->getColorKey());
}

bool Image::hasColorKey()
{
    return m_img->isSRCColorKeyset();
}

/**
 * Reset the global alpha value of the image
 *
 * @val, the global alpha value [0..255]. 255 is opaque, 0 is transparent.
 *
 * Return: true if everything went fine, false otherwise
 */
bool Image::resetGlobalAlpha(int val)
{
    return m_img->resetAlpha( ( val >0 && val <= 255), val);
}


/**
 * Get the global Alpha value
 * Return: the alpha value. (255 means no global alpha)
 */
int Image::getGlobalAlpha()
{
    return m_img->isSRCAlphaset();
}



} //SDL

} // SDLut


