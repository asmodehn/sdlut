#include "Video/internal/OpenGL/OGLVideoInfo.hh"
#include "SDLConfig.hh"

using namespace Core;

namespace SDLut
{
namespace video
{
namespace internal
{
namespace OGL
{

#ifdef WK_SDLut_FOUND_OPENGL
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



Core::Logger & operator << (Core::Logger & log, const OGLVideoInfo & glvi)
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

