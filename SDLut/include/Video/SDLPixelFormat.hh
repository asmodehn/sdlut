#ifndef SDL_PIXELFORMAT_HH
#define SDL_PIXELFORMAT_HH

#include "SDLColor.hh"
#include "Logger.hh"
//declaring SDL_type for late binding
struct SDL_PixelFormat;

namespace RAGE
{
namespace SDL
{

class PixelFormat
{
    //because SDLPixelColor needs to access actual SDL_PixelFormat
    friend class VideoInfo;
    friend class VideoSurface;
    friend class RGBSurface;
    friend class BaseSurface;
    friend class ImageLoader;

    bool pointerCopy;

protected:
    //read-only access
    //the address of the SDL_PixelFormat struct should never change
    const SDL_PixelFormat* const ptm_sdl_pformat;


    //Copy Constructor from SDL_PixelFormat
    //This handle explicit casts
    explicit PixelFormat(const SDL_PixelFormat* pf);
    //DEVELOPER BEWARE ! Don't free the original pixelformat.
    //The user should never be able to free the original pixelformat
    //nor to use SDL directly.

public: //necessary if we want to use getPixelFormat() accessor from the BaseSurface class when we're not in a PixelFormat's friend class
    ~PixelFormat(void);



    //default Constructor
    //PixelFormat(void) { _pformat= new SDL_PixelFormat; }
    //TODO : To avoid using uninitialized PixelFormat , put default constructor on protected
    //Really Useful ??


    int getBitsPerPixel() const;
    int getBytesPerPixel() const;
    int getRshift() const;
    int getGshift() const;
    int getBshift() const;
    int getAshift() const;

    int getRloss() const;
    int getGloss() const;
    int getBloss() const;
    int getAloss() const;

    //BEWARE ! sometimes this has no sense, because only the palette is set...
    //TODO : Handle this...
    unsigned long getRmask() const;
    unsigned long getGmask() const;
    unsigned long getBmask() const;
    unsigned long getAmask() const;

    PixelColor getColorKey() const;
    int getAlpha() const;
    Palette getPalette() const;

    //display all detected informations about pixelformat
    friend Logger & operator << (Logger & ostr, const PixelFormat & pformat);

    //methods for Color conversion :
    PixelColor getPixelColor(const Color& color) const ;
    Color getColor(const PixelColor& val) const ;

/*
#ifdef WK_OPENGL_FOUND
    const GLbyte [] getGLColor3bv(const PixelColor& val) const;
    const GLshort [] getGLColor3sv(const PixelColor& val) const;
    const GLint [] getGLColor3iv(const PixelColor& val) const;
    const GLfloat [] getGLColor3fv(const PixelColor& val) const;
    const GLdouble [] getGLColor3dv(const PixelColor& val) const;
    const GLubyte [] getGLColor3ubv(const PixelColor& val) const;
    const GLushort [] getGLColor3usv(const PixelColor& val) const;
    const GLuint [] getGLColor3uiv(const PixelColor& val) const;

    const GLbyte [] getGLColor4bv(const PixelColor& val) const;
    const GLshort [] getGLColor4sv(const PixelColor& val) const;
    const GLint [] getGLColor4iv(const PixelColor& val) const;
    const GLfloat [] getGLColor4fv(const PixelColor& val) const;
    const GLdouble [] getGLColor4dv(const PixelColor& val) const;
    const GLubyte [] getGLColor4ubv(const PixelColor& val) const;
    const GLushort [] getGLColor4usv(const PixelColor& val) const;
    const GLuint [] getGLColor4uiv(const PixelColor& val) const;

#endif
*/

};

}
} //namespace RAGE::SDL

#endif
