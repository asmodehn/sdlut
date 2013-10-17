#include "Video/internal/SDLLogo.hh"

#include "SDLConfig.hh"

#include "SDLResources.inc"

using namespace Core;

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
#ifdef WK_SDLut_FOUND_OPENGL
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
#ifdef WK_SDLut_FOUND_OPENGL
    OGL::GLSurface* newlogo = new OGL::GLSurface(mylogo);
#else
    RGBSurface* newlogo = new RGBSurface(mylogo);
#endif
    m_logo.reset(newlogo);
}


//this render function should not modify the engine
#ifdef WK_SDLut_FOUND_OPENGL
bool Logo::render(OGL::VideoGLSurface & screen) const
{
    Rect dest_rect( screen.getWidth() - m_logo->getWidth(), screen.getHeight() - m_logo->getHeight());
    Rect src_rect(0,0,m_logo->getWidth(),m_logo->getHeight());
    dest_rect.resetw( src_rect.getw() );
    dest_rect.reseth( src_rect.geth() );

    //if OpenGL is not set
    if ( ! screen.isOpenGLset() )
    {
        //memorising clip rectangle and resetting
        Rect clip = screen.getClipRect();
        screen.resetClipRect();

        //normal SDL 2D render
        bool res = screen.blit(*m_logo,dest_rect);
        res = res && screen.update(dest_rect);

        //restoring old clip rect
        screen.resetClipRect(clip);
        return res;
    }
    else
    {

        if ( ! m_logo->optimised )
        {
            //generate the GL texture if needed
            if ( m_logo->convertToDisplayFormat(screen.getRenderer()) == false )
            {
                Log << nl << "Error while converting Logo to GL display format";
            }
        }

        //finding texture size in coord weight
        float texx= static_cast<float>(src_rect.getx()) / m_logo->getTextureWidth();
        float texy= static_cast<float>(src_rect.gety()) / m_logo->getTextureHeight();
        float texw= static_cast<float>(src_rect.getw()) / m_logo->getTextureWidth();
        float texh= static_cast<float>(src_rect.geth()) / m_logo->getTextureHeight();


        //to NOT use clip rectangle
        glDisable(GL_SCISSOR_TEST);

        //render it
        //2D Rendering

        glDisable( GL_DEPTH_TEST ) ;
        glMatrixMode( GL_PROJECTION ) ;
        glLoadIdentity() ;

        glOrtho( 0, screen.getWidth(), screen.getHeight(), 0, 0, 1 ) ;
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        //Enable texturing
        glEnable(GL_TEXTURE_2D);

        //Load the texture
        glBindTexture(GL_TEXTURE_2D, m_logo->textureHandle);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

        glBegin( GL_QUADS ) ;
        glTexCoord2f( texx,texy) ;
        glVertex2i(dest_rect.getx(), dest_rect.gety() ) ;

        glTexCoord2f( texx, texy+texh) ;
        glVertex2i(dest_rect.getx(), dest_rect.gety() + dest_rect.geth()) ;

        glTexCoord2f( texx+texw, texy+texh) ;
        glVertex2i(dest_rect.getx() + dest_rect.getw(), dest_rect.gety() + dest_rect.geth()) ;

        glTexCoord2f( texx+texw, texy) ;
        glVertex2i( dest_rect.getx() + dest_rect.getw(), dest_rect.gety()) ;

        glEnd() ;


        //Disable texturing
        glDisable(GL_TEXTURE_2D);

        return true;
    }

}

#else
bool Logo::render(VideoSurface & screen) const
{
    Rect dest( screen.getWidth() - m_logo->getWidth(), screen.getHeight() - m_logo->getHeight(), m_logo->getWidth(), m_logo->getHeight());
    bool res = screen.blit(*m_logo,dest);

    res = res && screen.update(dest);
    //Maybe the refresh strategy should be implemented under -> in Video Surface ??
    return res;
}
#endif

}
}
}
