#include "Video/internal/SDLLogo.hh"

#include "SDLConfig.hh"

#include "SDLResources.inc"

using namespace RAGE;

namespace SDLut
{
    namespace video
    {
namespace internal
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
    try
    {
        system::RWOps _iconres( resources::_defaultImage,sizeof(resources::_defaultImage) );
        #ifdef WK_OPENGL_FOUND
        m_logo.reset(new OGL::GLSurface( _iconres ));
        #else
        m_logo.reset(new RGBSurface( _iconres ));
        #endif
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
    //we copy the image
    #ifdef WK_OPENGL_FOUND
    OGL::GLSurface* newlogo = new OGL::GLSurface(mylogo);
    #else
    RGBSurface* newlogo = new RGBSurface(mylogo);
    #endif
    m_logo.reset(newlogo);
}


//this render function should not modify the engine
#ifdef WK_OPENGL_FOUND
bool Logo::render(OGL::VideoGLSurface & screen) const
#else
bool Logo::render(VideoSurface & screen) const
#endif
{
    Rect dest( screen.getWidth() - m_logo->getWidth(), screen.getHeight() - m_logo->getHeight(), m_logo->getWidth(), m_logo->getHeight());
    bool res = screen.blit(*m_logo,dest);

    res = res && screen.update(dest);
    //Maybe the refresh strategy should be implemented under -> in Video Surface ??
    return res;
}

}
    }
}
