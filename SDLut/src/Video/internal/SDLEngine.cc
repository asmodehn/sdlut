#include "Video/internal/SDLEngine.hh"

#include "SDLConfig.hh"

#include "SDLResources.inc"

namespace SDLut
{
namespace video
{
namespace internal
{

//loading the default RGBSurface from the Resources as logo
SDLEngine::SDLEngine() : m_Logo()
{
}

//this render function should not modify the engine
#ifdef WK_SDLut_FOUND_OPENGL
bool SDLEngine::render(OGL::VideoGLSurface & screen) const
#else
bool SDLEngine::render(VideoSurface & screen) const
#endif
{
    bool res = false;
    res = m_Logo.render(screen);

    return res;
}

/*
//to initialise the engine, just called once before any render
bool SDLEngine::init(int width, int height)
{
    //m_glLogo.init();

    return true;
}

//get called everytime the display is resized
bool SDLEngine::resize(int width, int height)
{
    return true;
}
*/
SDLEngine::~SDLEngine()
{
}


}
}
}

