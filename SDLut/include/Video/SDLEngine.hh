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

#include "SDLRGBSurface.hh"
#include "SDLGLSurface.hh"
#include "SDLVideoSurface.hh"
#include "OGLLogo.hh"

namespace RAGE
{
namespace SDL
{


// Default 2D Engine ( only used if no engine is defined )
class SDLEngine
{
protected:
    //will be initialized in init
    //might be better in a constructor actually...
    std::auto_ptr<RGBSurface> m_logo;

    //SDL default logo
    Logo m_Logo;

#ifdef WK_OPENGL_FOUND
    //OpenGL logo
    OGLLogo m_glLogo;
#endif

public:

    SDLEngine();
    virtual ~SDLEngine();

    //this render function should not modify the engine
    virtual bool render(VideoSurface & screen) const;

    //to initialise the engine, just called once before any render
    //virtual bool init(int width, int height);

    //call everytime the display is resized
    //virtual bool resize(int width, int height);
};




}
}




#endif //SDL_ENGINE_HH
