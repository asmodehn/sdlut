#ifndef SDL_GLSURFACE_HH
#define SDL_GLSURFACE_HH

/*******************************************************************************
 * Handle a Graphical GL Surface
 ******************************************************************************/

#include "Video/internal/SDLRGBSurface.hh"
#include "Video/internal/OpenGL/OGLPixelFormat.hh"
namespace SDLut
{

namespace font
{
class FontExtend;
}

namespace video
{
class ImageLoader;

namespace internal
{
class Logo;

namespace OGL
{

#ifdef WK_SDLut_FOUND_OPENGL
class GLSurface : public video::internal::RGBSurface
{

    friend class VideoGLSurface;

    friend class video::ImageLoader;
    friend class video::internal::Logo; //so that Logo can access texturehandle and render itself.

    friend class font::FontExtend;

public:
    virtual Renderer getRenderer()
    {
        return OpenGL;
    }

private:
    ///Conversion Constructor
    explicit GLSurface(SDL_Surface * s) throw (std::logic_error); ///< This one should be called only by friends

    ///Conversion Constructor with explicit ownership transfert
    explicit GLSurface(std::auto_ptr<SDL_Surface> s) throw (std::logic_error);

protected:

    //to mark the texture as modified, if texture update needed before using it
    bool modified;

    unsigned int textureHandle;
    unsigned int textureFormat;

    unsigned int m_actualWidth;
    unsigned int m_actualHeight;

    unsigned int getTextureHandle();

public :

    //Constructor
    //BPP should NEVER be == 0 !!!!
    GLSurface( int width, int height, int bpp,
               bool alpha = false,
               bool colorkey = false,
               bool hardware = false,
               unsigned long r_mask = r_default_mask,
               unsigned long g_mask = g_default_mask,
               unsigned long b_mask = b_default_mask,
               unsigned long a_mask = a_default_mask
             ) throw (std::logic_error);

    GLSurface( void * pixeldata, int depth, int pitch, int width, int height,
               unsigned long r_mask = r_default_mask,
               unsigned long g_mask = g_default_mask,
               unsigned long b_mask = b_default_mask,
               unsigned long a_mask = a_default_mask
             ) throw (std::logic_error);

    GLSurface ( system::RWOps & rwops) throw(std::logic_error);

    ///Conversion from internal RGBSurface. Used by Image if needed in emergency.
    explicit GLSurface( const RGBSurface & rgbs) throw (std::logic_error);

    ///Copy from internal GLSurface.
    explicit GLSurface( const GLSurface & gls) throw (std::logic_error);


    virtual ~GLSurface();

    //reutrne hte OpenGL texture size ( same as internal SDL_Surface
    unsigned int getTextureWidth();
    unsigned int getTextureHeight();

    //Return actual original surface size, before OpenGL transofrmation
    virtual unsigned int getWidth();
    virtual unsigned int getHeight();


    ///Accessor to pixelFormat
    const PixelFormat& getPixelFormat(void) const;

    bool convertToDisplayFormat(Renderer r);

    bool resetColorKey(bool ckey, const PixelColor & key, bool rleAccel = true);
    bool resetAlpha(bool alpha, unsigned int value, bool rleAccel = true);


    //saveBMP // TODO useful for screenshots

    virtual bool resize(int width, int height, bool force = false);

    bool fill (const PixelColor& color, Rect dest_rect);

    bool blit (const RGBSurface& src, Rect& dest_rect, const Rect& src_rect);

    friend Core::Logger & operator << (Core::Logger & ostr, const RGBSurface & surf);

};

#else
/* OGLLogo is defined only if Built with OpenGL */
#endif // WK_SDLut_FOUND_OPENGL


}
}
}
} //namespace SDLut::SDL

#endif
