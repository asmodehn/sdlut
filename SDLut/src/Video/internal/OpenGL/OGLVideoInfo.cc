#include "Video/internal/OpenGL/OGLVideoInfo.hh"
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
#pragma message ("OpenGL Found. Compiling OGL::OGLVideoInfo.")
//may be connected with constructor ???
bool OGLVideoInfo::loadGLLibrary(const std::string & path)
{
    return SDL_GL_LoadLibrary(path.c_str()) == 0;
}

OGLVideoInfo::OGLVideoInfo()
: VideoInfo()
{
}

OGLVideoInfo::OGLVideoInfo(unsigned int width, unsigned int height, unsigned int bpp, unsigned long vflags)
: VideoInfo(width,height,bpp,vflags)
{
}



RAGE::Logger & operator << (RAGE::Logger & log, const OGLVideoInfo & glvi)
{
    log << nl << "OGLVideoInfo : " ;


    log << nl << glvi.upcast();
    return log;
}
#else
#pragma message ("No OpenGL ! OGL::OGLVideoInfo class not compiled.")
#endif
}
}
}
}

