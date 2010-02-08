#include "Video/SDLEngine.hh"

#include "Video/SDLSurfaceLoader.hh"
#include "SDLConfig.hh"

#include "SDLResources.inc"

namespace RAGE
{
namespace SDL
{

//loading the default RGBSurface from the Resources as logo
SDLEngine::SDLEngine() : m_logo(0)
{
    SurfaceLoader loader;
#ifdef WK_OPENGL_FOUND
    loader.resetOpengl(true);
#endif
    try
    {
        RWOps _iconres( _defaultImage,sizeof(_defaultImage) );
        m_logo = loader.load( _iconres );
    }
    catch (std::exception &)
    {
        Log << nl << " ERROR : Unable to load Default Logo ! ";
        //shouldnt happen. therefore no rethrow. ( assumed RAII )
        //if this occurs, behavior is totally unknown...
    }
}

//this render function should not modify the engine
bool SDLEngine::render(VideoSurface & screen) const
{
    Rect dest( screen.getWidth() - m_logo->getWidth(), screen.getHeight() - m_logo->getHeight(), m_logo->getWidth(), m_logo->getHeight());
    bool res = screen.blit(*m_logo,dest);

    //if OpenGL renderer
    if ( m_logo->getRenderer() == OpenGL )
    {
        m_glLogo.render(screen);
    }


    res = res && screen.update(dest);
    //Maybe the refresh strategy should be implemented under -> in Video Surface ??
    return res;
}

//to initialise the engine, just called once before any render
bool SDLEngine::init(int width, int height)
{
    //if OpenGLrenderer
    if (m_logo->getRenderer() == OpenGL )
{
    //set size of rendered gllogo equals to sdllogo
    m_glLogo.init(m_logo->getWidth(), m_logo->getHeight());
}

    return true;
}

//get called everytime the display is resized
bool SDLEngine::resize(int width, int height)
{
    return true;
}

SDLEngine::~SDLEngine()
{
}

}
}

