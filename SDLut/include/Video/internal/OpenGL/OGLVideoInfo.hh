#ifndef OGLVIDEOINFO_HH
#define OGLVIDEOINFO_HH

/**
 * \class OGLVideoInfo
 *
 *
 * \brief This class is an OpenGL Video Info, similar to the SDL one
 *
 * This class implements the opengl functions related to SDL Video Info
 * Especially the SGL_GL_set/get_attributes, that can be set either before display creation or after.
 *
 * \author Alex
 *
 * \date 2010/03/17
 *
 * Contact: asmodehn@gna.org
 *
 */

#include "Logger.hh"
#include "Video/internal/SDLVideoInfo.hh"
#include <string>

namespace SDLut
{
namespace video
{
namespace internal
{
namespace OGL
{

#ifdef WK_OPENGL_FOUND

//This may be useless in Windows....
//TEst to do on linux, to choose a class behaviour
class OGLVideoInfo : public VideoInfo
{

private: //accessed by friends only
    const VideoInfo & upcast() const
    {
        return *this;
    }


public :
    OGLVideoInfo();
    OGLVideoInfo(unsigned int width, unsigned int height, unsigned int bpp, unsigned long vflags) ;
    virtual ~OGLVideoInfo() {}

    //may be connected with constructor ???
    bool loadGLLibrary(const std::string & path);

    //TODO : how to manage this....
    //getProcAddress





    //Accessor to GLAttributes
    //Note : DoubleBuf is managed by GLWindow, like 2D doublebuf
    //TODO -> error managed by exceptions ???
    //TODO -> different behavior depending if GLWindow is already set or not ? ( refer SDLManager... )


    friend RAGE::Logger & operator << (RAGE::Logger & ostr, const OGLVideoInfo & glvi);
};

#else
/* OGLLogo is defined only if Built with OpenGL */
#endif // WK_OPENGL_FOUND


} // OGL
} // internal
} // video
} // namespace SDLut

#endif

