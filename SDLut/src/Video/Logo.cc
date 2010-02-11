#include "Video/Logo.hh"

#include "Video/SDLSurfaceLoader.hh"
#include "SDLConfig.hh"

#include "SDLResources.inc"

namespace RAGE
{
    namespace SDL
    {

int Logo::m_render_width = 128;
int Logo::m_render_height = 64;


void Logo::resizerender(int renderwidth, int renderheight)
{
    m_render_width = renderwidth;
    m_render_height = renderheight;
}


//loading the default RGBSurface from the Resources as logo
Logo::Logo()
{

    //TODO : OpenGL or not strategy should be defined...
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

Logo::~Logo()
{
}



void Logo::setLogoImage( const RGBSurface & mylogo )
{
    RGBSurface* newlogo = new RGBSurface(mylogo);
    m_logo.reset(newlogo);
}


//this render function should not modify the engine
bool Logo::render(VideoSurface & screen) const
{
    //TODO : manage resize proportionally to the screen size
    Rect dest( screen.getWidth() - m_logo->getWidth(), screen.getHeight() - m_logo->getHeight(), m_logo->getWidth(), m_logo->getHeight());
    bool res = screen.blit(*m_logo,dest);

    res = res && screen.update(dest);
    //Maybe the refresh strategy should be implemented under -> in Video Surface ??
    return res;
}

    }
}
