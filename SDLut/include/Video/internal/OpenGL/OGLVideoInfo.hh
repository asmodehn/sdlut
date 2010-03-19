#ifndef OGLVIDEOINFO_HH
#define OGLVIDEOINFO_HH

/**
 * \class OGLVideoInfo
 *
 *
 * \brief This class is an OpenGL Video Info, similar to the SDL one
 *
 * This class implements the opengl functions related to SDL Video Info
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

//This may be useless in Windows....
//TEst to do on linux, to choose a class behaviour
class OGLVideoInfo : public VideoInfo
{
    public :
    OGLVideoInfo() {}

    ~OGLVideoInfo() {}

    //may be connected with constructor ???
    bool loadGLLibrary(const std::string & path);

    //TODO : I don't know how to manage this....
    //getProcAddress



    //Accessor to GLAttributes
    //Note : DoubleBuf is managed by GLWindow, like 2D doublebuf
    //TODO -> error managed by exceptions ???
    //TODO -> different behavior depending if GLWindow is already set or not ? ( refer SDLManager... )


    friend RAGE::Logger & operator << (RAGE::Logger & ostr, const OGLVideoInfo & glvi);
};

    } // OGL
} // internal
} // video
} // namespace SDLut

#endif

