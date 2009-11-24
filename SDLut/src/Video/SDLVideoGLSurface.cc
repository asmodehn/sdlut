#include "Video/SDLVideoGLSurface.hh"
#include "SDLConfig.hh"
#include <typeinfo> //for std::bad_cast
//#include <sstream>

//#define DEBUG 2

namespace RAGE
{
namespace SDL
{

//Constructor
VideoGLSurface::VideoGLSurface(int width, int height, int bpp) throw (std::logic_error)
try
:
    VideoSurface(width,height,bpp)
{
#ifdef DEBUG
    Log << nl << "VideoGLSurface::VideoGLSurface() called ...";
#endif

    if (!initialized())
    {
        Log << nl <<"Unable to set " << width << " x " << height << " GL display surface : ";
        throw std::logic_error("VideoSurface::VideoSurface() Failed.");
    }

#ifdef DEBUG
    Log << nl << "VideoGLSurface::VideoGLSurface() done.";
#endif

}
catch (std::exception &e)
{
    Log << nl << "VideoGLSurface:: Exception in Constructor !" <<
    nl << e.what() << nl << GetError() << std::endl;
    //TODO : much more explicit error message...
}

VideoGLSurface::~VideoGLSurface()
{}

//Useless in OpenGL
bool VideoGLSurface::update(Rect r)
{
    return true;
}

//Useless in OpenGL
bool VideoGLSurface::update(std::vector<Rect> rlist)
{
    return true;
}


bool VideoGLSurface::refresh(void)
{
    //This should always be true...
    //if (isOpenGLset())
    //{
    SDL_GL_SwapBuffers();
    return true;
    //}
    //else
    //	return SDL_Flip(_surf.get()) == 0;
}


RGBAColor VideoGLSurface::getpixel(int x, int y)
{
    unsigned char pixel[4];
    glReadPixels(x, y, 1, 1, GL_RGBA, GL_BYTE, &pixel);

#if (SDL_BYTE_ORDER == SDL_BIG_ENDIAN)
    RGBAColor color(pixel[3], pixel[2], pixel[1], pixel[0]);
#else
    RGBAColor color(pixel[0], pixel[1], pixel[2], pixel[3]);
#endif
    return color;
}

void VideoGLSurface::setpixel(int x, int y, RGBAColor color)
{

#if (DEBUG == 2)
    Log << nl << "VideoGLSurface::setpixel ( " << x << ", "<< y << ", " << color << ") called...";
#endif

    //render it
    //2D Rendering

    glDisable( GL_DEPTH_TEST ) ;
    glMatrixMode( GL_PROJECTION ) ;
    glLoadIdentity() ;

    glOrtho( 0, this->getWidth(), this->getHeight(), 0, 0, 1 ) ;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if ( color.hasAlpha() )
    {
        glEnable(GL_BLEND);
        glEnable(GL_ALPHA_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    glColor4ub(color.getR(), color.getG(), color.getB(), color.getA() );

    glBegin( GL_POINTS ) ;

    glVertex2i( x, y ) ;

    glEnd() ;


    if ( color.hasAlpha() )
    {
        glDisable(GL_ALPHA_TEST);
        glDisable(GL_BLEND);
    }

#if (DEBUG == 2)
    Log << nl << "VideoGLSurface::setpixel ( " << x << ", "<< y << ", " << color << ") done.";
#endif


}


//TODO : rethink about that again...( recopy the content if 2D or not at all ??? )
bool VideoGLSurface::resize(int width, int height, bool keepcontent)
{

#ifdef DEBUG
    Log << nl << "VideoGLSurface::resize(" << width << ", " << height << ") called...";
#endif

    bool res;
    std::auto_ptr<SDL_Surface> oldSurf(0);
    if ( keepcontent && !isOpenGLset())
    {
        oldSurf.reset( SDL_CreateRGBSurface(SDL_SWSURFACE,getWidth(),getHeight(),getBPP(),r_default_mask,g_default_mask, b_default_mask, a_default_mask) );
        SDL_DisplayFormat(oldSurf.get());
        SDL_BlitSurface(_surf.get(),NULL,oldSurf.get(),NULL);
    }

    //BEWARE : should match DisplaySurface Constructor code
    std::auto_ptr<SDL_Surface> newSurf( SDL_SetVideoMode(width,height,getBPP(),getFlags()) );

    if (!newSurf.get()) //SetVideoMode has failed
    {
        Log << "Unable to resize to " << width << " x " << height << " 2D display surface " << nl << GetError();

#ifdef DEBUG
        Log << nl << "VideoSurface::resize(" << width << ", " << height << ") failed.";
#endif
        res = false;
    }
    else
    {

        if (keepcontent  && !isOpenGLset() && oldSurf.get() != 0)
        {
            SDL_BlitSurface(oldSurf.get(), NULL , newSurf.get(), NULL);
            SDL_FreeSurface(oldSurf.get());
        }
        _surf=newSurf;

#ifdef DEBUG
        Log << nl << "VideoGLSurface::resize(" << width << ", " << height << ") succeeded.";
#endif
        res = true;
    }

    SDL_FreeSurface(oldSurf.release());

    return (res && initialized());
}


//Blit src into the current surface.
bool VideoGLSurface::blit (RGBSurface& src, Rect& dest_rect, const Rect& src_rect)
{
#if (DEBUG == 2)
    Log << nl << "VideoGLSurface::blit (const RGBSurface& src," << dest_rect << ", " << src_rect << ") called...";
#endif
    bool success = false;

    try
    {
        //Test if src is a GLSurface
        // RGB / GL surface difference has to be hidden from client,
        // but rendering speed should remain optimum...
        GLSurface& glsrc = dynamic_cast<GLSurface&>(src);

        glsrc.saveBMP("testing.bmp");

        //optimisation tricks
        //TODO :  the conversion to texture should be done just after modification (as a customisable default), as render must remain optimum,
        // only the emergency conversion to display format is useful here. Maybe even not...
        if ( glsrc.modified )
        {
            glsrc.computeGLWidthHeight();
            glsrc.convertPixels();
            glsrc.optimised = false; // to trigger regeneration of texture if needed
        }
        if ( ! glsrc.optimised )
        {
            //if not converted to display format already,
            //or if the surface has changed since last blit,
            //then convert it now (optimisation)
            //TODO : find a way to do that without impacting rendering speed...
            glsrc.convertToDisplayFormat();
        }


        //finding texture size in coord weight
        float texx= static_cast<float>(src_rect.getx()) / glsrc.getTextureWidth();
        float texy= static_cast<float>(src_rect.gety()) / glsrc.getTextureHeight();
        float texw= static_cast<float>(src_rect.getw()) / glsrc.getTextureWidth();
        float texh= static_cast<float>(src_rect.geth()) / glsrc.getTextureHeight();


        //render it
        //2D Rendering

        glDisable( GL_DEPTH_TEST ) ;
        glMatrixMode( GL_PROJECTION ) ;
        glLoadIdentity() ;

        glOrtho( 0, getWidth(), getHeight(), 0, 0, 1 ) ;
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        if ( glsrc.isSRCAlphaset() || glsrc.isSRCColorKeyset())
        {
            glEnable(GL_BLEND);
            glEnable(GL_ALPHA_TEST);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        //Enable texturing
        glEnable(GL_TEXTURE_2D);

        //Load the texture
        glBindTexture(GL_TEXTURE_2D, glsrc.textureHandle);

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


        if ( glsrc.isSRCAlphaset() || glsrc.isSRCColorKeyset())
        {
            glDisable(GL_ALPHA_TEST);
            glDisable(GL_BLEND);
        }

        //Disable texturing
        glDisable(GL_TEXTURE_2D);

        success = true;

    }
    catch (std::bad_cast& bc)
    {
        //If not convert it
        Log << " bad_cast caught: Surface wasnt a GLSurface. " << bc.what() ;
        Log << " Conversion should be done before in Image::ConvertToDisplayFormat() " ;
        success = false;
    }


#if (DEBUG == 2)
    Log << nl << "VideoGLSurface::blit (const RGBSurface& src," << dest_rect << ", " << src_rect << ") done.";
#endif

    return success;
}



//Fill
bool VideoGLSurface::fill (const RGBAColor& color)
{
    Rect dest_rect(getWidth(), getHeight());
    return fill( color, dest_rect );
}

bool VideoGLSurface::fill (const RGBAColor& color, Rect dest_rect)
{

#if (DEBUG == 2)
    Log << nl << "VideoGLSurface::fill ( " << color << ", " << dest_rect << ") called...";
#endif
    bool success = false;
    //render it
    //2D Rendering

    glDisable( GL_DEPTH_TEST ) ;
    glMatrixMode( GL_PROJECTION ) ;
    glLoadIdentity() ;

    glOrtho( 0, this->getWidth(), this->getHeight(), 0, 0, 1 ) ;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if ( color.hasAlpha() )
    {
        glEnable(GL_BLEND);
        glEnable(GL_ALPHA_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    glColor4ub(color.getR(), color.getG(), color.getB(), color.getA() );

    glBegin( GL_QUADS ) ;

    glVertex2i(dest_rect.getx(), dest_rect.gety() ) ;
    glVertex2i(dest_rect.getx(), dest_rect.gety() + dest_rect.geth()) ;
    glVertex2i(dest_rect.getx() + dest_rect.getw(), dest_rect.gety() + dest_rect.geth()) ;
    glVertex2i( dest_rect.getx() + dest_rect.getw(), dest_rect.gety()) ;

    glEnd() ;


    if ( color.hasAlpha() )
    {
        glDisable(GL_ALPHA_TEST);
        glDisable(GL_BLEND);
    }


    success = true;

#if (DEBUG == 2)
    Log << nl << "VideoGLSurface::fill ( " << color << ", " << dest_rect << ") called...";
#endif

    return success;

}

Logger & operator << (Logger & log, const VideoGLSurface & surf)
{
    //TODO : call base operator here...
    //log << static_cast<BaseSurface>(surf);
    log << nl<<std::boolalpha << "- Fullscreen ? " << surf.isFullScreenset() << nl
    << "- OpenGL ? " << surf.isOpenGLset() << nl
    << "- Resizable ? " << surf.isResizableset() << nl
    << "- NoFrame ? " << surf.isNoFrameset() <<nl
    << "- AnyFormat ? " << surf.isAnyFormatset() << nl
    << "- Double Buffered ? " << surf.isDoubleBufset();
    return log;
}

}
} //namespace RAGE::SDL
