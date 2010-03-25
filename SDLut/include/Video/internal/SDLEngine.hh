#ifndef SDL_ENGINE_HH
#define SDL_ENGINE_HH

/*******************************************************************************
 * Interface with other systems                                                *
 * An Engine is the class coding the behaviour of the displayed content        *
 * that is related to the display system itself, rather than the application   *
 * For example :                                                               *
 * - logos displaying which render method                                      *
 * - fps and other informative display for debug                               *
 * - etc. Maybe the name "Engine" is misleading. It might be changed later on  *
 *   depending on its actual use                                               *
 * Warning : GUI, is related to the application, and not to the display system *
 *******************************************************************************/

#include "Video/internal/SDLRGBSurface.hh"
#include "Video/internal/OpenGL/SDLGLSurface.hh"
#include "Video/internal/SDLVideoSurface.hh"
#include "Video/internal/OpenGL/OGLLogo.hh"

namespace SDLut
{
namespace video
{
namespace internal
{


// Default 2D Engine ( only used if no engine is defined )
class SDLEngine
{
protected:
    //will be initialized in init
    //might be better in a constructor actually...
    std::auto_ptr<RGBSurface> m_logo;


#ifdef WK_OPENGL_FOUND
    //OpenGL logo + SDL Logo in texture
    //OpenGL logo displayed only if renderer is opengl
    OGL::OGLLogo m_Logo;
#else
    //SDL default logo in BMP/PNG
    Logo m_Logo;
#endif

public:

    SDLEngine();
    virtual ~SDLEngine();

    //this render function should not modify the engine
#ifdef WK_OPENGL_FOUND
    virtual bool render(OGL::VideoGLSurface & screen) const;
#else
    virtual bool render(VideoSurface & screen) const;
#endif

    //to initialise the engine, just called once before any render
    //virtual bool init(int width, int height);

    //call everytime the display is resized
    //virtual bool resize(int width, int height);
};



}
}
}




#endif //SDL_ENGINE_HH
