#include "Video/Image.hh"
#include "SDLConfig.hh"

#include "SDLApp.hh"
//here just to be able to access the Manager without explicitly showing it in the interface
//as the interface might be used directly by the client...
//TODO : Have a Singleton containing the settings of the Application, available everywhere through SDLConfig.hh

namespace RAGE
{
namespace SDL
{

#ifdef WK_OPENGL_FOUND

///Conversion Constructor with explicit ownership transfert
Image::Image(std::auto_ptr<GLSurface> s) throw (std::logic_error)
        : m_img(NULL)
{
    m_img=s;
    if ( m_img.get() == NULL ) throw std::logic_error("Error in image Conversion Constructor!!!");
}
#endif // WK_OPENGL_FOUND

///Conversion Constructor

///Conversion Constructor with explicit ownership transfert
Image::Image(std::auto_ptr<RGBSurface> s) throw (std::logic_error)
        : m_img(NULL)
{
#ifdef WK_OPENGL_FOUND
    m_img.reset(new GLSurface(*s));// conversion if needed
#else
    m_img=s;
#endif
    if ( m_img.get() == NULL ) throw std::logic_error("Error in image Conversion Constructor!!!");
}



//Constructor
//BPP should NEVER be == 0 !!!!
Image::Image( int width, int height, int bpp,
              bool alpha,
              bool colorkey,
              bool hardware
            ) throw (std::logic_error)

{
#ifdef WK_OPENGL_FOUND
        m_img.reset(new GLSurface(width, height, bpp, alpha, colorkey, hardware));
#else
        m_img.reset(new RGBSurface(width, height, bpp, alpha, colorkey, hardware));
#endif
}


Image::Image( void * pixeldata, int depth, int pitch, int width, int height
            ) throw (std::logic_error)
{

#ifdef WK_OPENGL_FOUND
        m_img.reset(new GLSurface(pixeldata, depth, pitch, width, height));
#else
        m_img.reset(new RGBSurface(pixeldata, depth, pitch, width, height));
#endif
}

Image::Image(const Image & img)
: m_img(NULL)
{

#ifdef WK_OPENGL_FOUND
        m_img.reset(new GLSurface(*(img.m_img)));
#else
        m_img.reset(new RGBSurface(*(img.m_img)));
#endif

}

Image::~Image()
{
}

bool Image::saveBMP( std::string filename )
{
    return m_img->saveBMP(filename);
}

bool Image::resize(int width, int height, bool keepcontent)
{
    return m_img->resize(width, height, keepcontent );
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


} //SDL

} // RAGE


