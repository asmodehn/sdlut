#include "Video/SDLEngine.hh"

#include "Video/SDLSurfaceLoader.hh"
#include "SDLConfig.hh"

#include "SDLResources.inc"

namespace RAGE
{
namespace SDL
{

//loading the default RGBSurface from the Resources as logo
SDLEngine::SDLEngine() : m_Logo(), m_glLogo()
{
}

//this render function should not modify the engine
bool SDLEngine::render(VideoSurface & screen) const
{
    bool res = false;
    res = m_Logo.render(screen);

    //if OpenGL renderer
    if ( screen.getRenderer() == OpenGL )
    {
        res = res && m_glLogo.render(screen);
    }

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

