#include "Video/internal/OpenGL/OGLPixelFormat.hh"
#include "SDLConfig.hh"

using namespace RAGE;

namespace SDLut
{
namespace video
{
    namespace internal
    {
        namespace OGL
        {

#ifdef WK_OPENGL_FOUND

//TODO : check maybe opengl pixel format is not needed
// SDL seems to manage pixel format for OpenGL fine, once you know how it works...
// But GLVideoInfo needed for setting up videosurface (SDL_GL_Attribute) before displaying it...

    //default Constructor
    OGLPixelFormat::OGLPixelFormat(void)
    : PixelFormat()
    {
    }

    OGLPixelFormat::OGLPixelFormat(const SDL_PixelFormat* pf)
    : PixelFormat(pf)
    {
    }

    OGLPixelFormat::~OGLPixelFormat()
    {}




    int OGLPixelFormat::getBitsPerPixel() const
    {
        return PixelFormat::getBitsPerPixel();
    }

    int OGLPixelFormat::getBytesPerPixel() const
    {
        return PixelFormat::getBytesPerPixel();
    }

    int OGLPixelFormat::getRshift() const
    {
        return PixelFormat::getRshift();
    }

    int OGLPixelFormat::getGshift() const
    {
        return PixelFormat::getGshift();
    }

    int OGLPixelFormat::getBshift() const
    {
        return PixelFormat::getBshift();
    }

    int OGLPixelFormat::getAshift() const
    {
        return PixelFormat::getAshift();
    }

    int OGLPixelFormat::getRloss() const
    {
           return PixelFormat::getRloss();
    }
    int OGLPixelFormat::getGloss() const
    {
        return PixelFormat::getGloss();
    }
    int OGLPixelFormat::getBloss() const
    {
        return PixelFormat::getBloss();
    }
    int OGLPixelFormat::getAloss() const
    {
        return PixelFormat::getAloss();
    }

    unsigned long OGLPixelFormat::getRmask() const
    {
        return PixelFormat::getRmask();
    }
    unsigned long OGLPixelFormat::getGmask() const
    {
        return PixelFormat::getGmask();
    }
    unsigned long OGLPixelFormat::getBmask() const
    {
        return PixelFormat::getBmask();
    }
    unsigned long OGLPixelFormat::getAmask() const
    {
        return PixelFormat::getAmask();
    }





int OGLPixelFormat::getRSize(void) const
{
    int res;
    SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &res);
    return res;
}

int OGLPixelFormat::getGSize(void) const
{
    int res;
    SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &res);
    return res;
}

int OGLPixelFormat::getBSize(void) const
{
    int res;
    SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &res);
    return res;
}

int OGLPixelFormat::getASize(void) const
{
    int res;
    SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &res);
    return res;
}

int OGLPixelFormat::getBufferSize(void) const
{
    int res;
    SDL_GL_GetAttribute(SDL_GL_BUFFER_SIZE, &res);
    return res;
}

int OGLPixelFormat::getDepthSize(void) const
{
    int res;
    SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &res);
    return res;
}

int OGLPixelFormat::getStencilSize(void) const
{
    int res;
    SDL_GL_GetAttribute(SDL_GL_STENCIL_SIZE, &res);
    return res;
}

int OGLPixelFormat::getAccumRSize(void) const
{
    int res;
    SDL_GL_GetAttribute(SDL_GL_ACCUM_RED_SIZE, &res);
    return res;
}

int OGLPixelFormat::getAccumGSize(void) const
{
    int res;
    SDL_GL_GetAttribute(SDL_GL_ACCUM_GREEN_SIZE, &res);
    return res;
}

int OGLPixelFormat::getAccumBSize(void) const
{
    int res;
    SDL_GL_GetAttribute(SDL_GL_ACCUM_BLUE_SIZE, &res);
    return res;
}

int OGLPixelFormat::getAccumASize(void) const
{
    int res;
    SDL_GL_GetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, &res);
    return res;
}

bool OGLPixelFormat::setRSize(int bits)
{
    return SDL_GL_SetAttribute(SDL_GL_RED_SIZE, bits) == 0;
}

bool OGLPixelFormat::setGSize(int bits)
{
    return SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, bits) == 0;
}

bool OGLPixelFormat::setBSize(int bits)
{
    return SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, bits) == 0;
}

bool OGLPixelFormat::setASize(int bits)
{
    return SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, bits) == 0;
}

bool OGLPixelFormat::setBufferSize(int bits)
{
    return SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, bits) == 0;
}

bool OGLPixelFormat::setDepthSize(int bits)
{
    return SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, bits) == 0;
}

bool OGLPixelFormat::setStencilSize(int bits)
{
    return SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, bits) == 0;
}

bool OGLPixelFormat::setAccumRSize(int bits)
{
    return SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, bits) == 0;
}

bool OGLPixelFormat::setAccumGSize(int bits)
{
    return SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, bits) == 0;
}

bool OGLPixelFormat::setAccumBSize(int bits)
{
    return SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, bits) == 0;
}

bool OGLPixelFormat::setAccumASize(int bits)
{
    return SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, bits) == 0;
}

PixelColor OGLPixelFormat::getColorKey() const
{
    return PixelFormat::getColorKey();
}

int OGLPixelFormat::getAlpha() const
{
    return PixelFormat::getAlpha();
}



RAGE::Logger & operator << (RAGE::Logger & log, const OGLPixelFormat & glman)
{
    log << static_cast<const PixelFormat &>(glman); // calling parent log
    log << nl << "OGLPixelFormat : " << nl <<
    "GL Red Size = " << glman.getRSize() << nl <<
    "GL Green Size = " << glman.getGSize() << nl <<
    "GL Blue Size = " << glman.getBSize() << nl <<
    "GL Alpha Size = " << glman.getASize() << nl <<
    "GL Buffer Size = " << glman.getBufferSize() << nl <<
    "GL Depth Size = " << glman.getDepthSize() << nl <<
    "GL Stencil Size = " << glman.getStencilSize() << nl <<
    "GL Accum Red Size = " << glman.getAccumRSize() << nl <<
    "GL Accum Green Size = " << glman.getAccumGSize() << nl <<
    "GL Accum Blue Size = " << glman.getAccumBSize() << nl <<
    "GL Accum Alpha Size = " << glman.getAccumASize() ;
    return log;
}
#else
#pragma message "No OpenGL ! OGLPixelFormat class not generated."
#endif

        }}
}
}

