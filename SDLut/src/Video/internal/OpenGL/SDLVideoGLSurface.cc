#include "Video/internal/OpenGL/SDLVideoGLSurface.hh"
#include "SDLConfig.hh"
#include <typeinfo> //for std::bad_cast
//#include <sstream>

//#define DEBUG 2

#ifndef min
#define min( a , b )  ( (a)>(b) )?(b):(a)
#endif


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

    //mandatory, because VideoGLSurface might not be have GL enabled...
    if ( isOpenGLset() )
    {
        //Setting up the GL Viewport
        glViewport(0,0,(GLsizei)getWidth(),(GLsizei)getHeight());
    }

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
    if ( isOpenGLset())
    {
        return true;
    }
    else
    {
        return VideoSurface::update(r);
    }
}

//Useless in OpenGL
bool VideoGLSurface::update(std::vector<Rect> rlist)
{

    if ( isOpenGLset())
    {
        return true;
    }
    else
    {
        return VideoSurface::update(rlist);
    }
}


bool VideoGLSurface::refresh(void)
{
    if (isOpenGLset())
    {
        SDL_GL_SwapBuffers();
        return true;
    }
    else
    	return VideoSurface::refresh();
}


PixelColor VideoGLSurface::getpixel(int x, int y)
{
    PixelColor color;
    if ( isOpenGLset() )
    {

    unsigned int p[4];
    glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, &p);

    Uint32 pixel;

//#if (SDL_BYTE_ORDER == SDL_BIG_ENDIAN)
//    color = (0xff000000 & pixel[3]) | (0x00ff0000 & pixel[2]) | (0x0000ff00 & pixel[1]) | (0x000000ff & pixel[0]);
//#else
//    color = (0xff000000 & pixel[0]) | (0x00ff0000 & pixel[1]) | (0x0000ff00 & pixel[2]) | (0x000000ff & pixel[3]);
//#endif
//
//OR
//
        //pixel= *(Uint32 *)p;
#if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        pixel= p[0] << 24 | p[1] << 16 | p[2] << 8 | p[3];
#else
        pixel= p[0] | p[1] << 8 | p[2] << 16 | p[3] << 24;
#endif
    }
    else
    {
        color = VideoSurface::getpixel(x,y);
    }
    return color;
}

void VideoGLSurface::setpixel(int x, int y, PixelColor color)
{

#if (DEBUG == 2)
    Log << nl << "VideoGLSurface::setpixel ( " << x << ", "<< y << ", " << color << ") called...";
#endif

    if ( isOpenGLset() )
    {
    //render it
    //2D Rendering

    glDisable( GL_DEPTH_TEST ) ;
    glMatrixMode( GL_PROJECTION ) ;
    glLoadIdentity() ;

    glOrtho( 0, this->getWidth(), this->getHeight(), 0, 0, 1 ) ;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //alpha test
#if (SDL_BYTE_ORDER == SDL_BIG_ENDIAN)
    if ( (color & 0x000000ff) != 0 )
#else
    if ( (color & 0xff000000) != 0 )
#endif
    {
        glEnable(GL_BLEND);
        glEnable(GL_ALPHA_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    Uint8 p[4];
    //conversion from BaseSurface code
    *(Uint32 *)p = (Uint32) color;

    glColor4ubv(p);

    glBegin( GL_POINTS ) ;

    glVertex2i( x, y ) ;

    glEnd() ;


    //alpha test
#if (SDL_BYTE_ORDER == SDL_BIG_ENDIAN)
    if ( (color & 0x000000ff) != 0 )
#else
    if ( (color & 0xff000000) != 0 )
#endif
    {
        glDisable(GL_ALPHA_TEST);
        glDisable(GL_BLEND);
    }
    }
    else
    {
        VideoSurface::setpixel(x,y,color);
    }

#if (DEBUG == 2)
    Log << nl << "VideoGLSurface::setpixel ( " << x << ", "<< y << ", " << color << ") done.";
#endif


}


// keepcontent option very useful for quickly resizing surface to fit in OpengL power of two policy
// TODO : check if we actually need to signal resized surface as modified...
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
        SDL_BlitSurface(ptm_surf.get(),NULL,oldSurf.get(),NULL);
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
        ptm_surf=newSurf;

    if(isOpenGLset())
    {
        //Setting up the GL Viewport
        glViewport(0,0,(GLsizei)getWidth(),(GLsizei)getHeight());
    }

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
    Log << nl << "VideoGLSurface::blit ( RGBSurface& src," << dest_rect << ", " << src_rect << ") called...";
#endif
bool res = false;
if(isOpenGLset())
{
    GLSurface* glsrc;
    try
    {
        Log << nl << "Surface wasnt recognized as a GLSurface !!! Forcing conversion" ;
        //Test if src is a GLSurface
        // RGB / GL surface difference has to be hidden from client,
        // but rendering speed should remain optimum...
        glsrc = &(dynamic_cast<GLSurface&>(src));
        //optimisation tricks
        //TODO :  the conversion to texture should be done just after every modification (as a customisable default), as render must remain optimum,
        // only the emergency conversion to display format is useful here. Maybe even not...
    }
    catch (std::bad_cast& bc)
    {
        //If not convert it
        Log << " bad_cast caught: Surface wasnt a GLSurface. " << bc.what() ;
        Log << " Creating GLSurface for rendering..." ;

        glsrc = new GLSurface(src);
        //no modification to handle here : GLSurf is brand new

    }

    src = *glsrc;//updating original


    res= blit(*glsrc,dest_rect,src_rect);
}
else
{
    res= VideoSurface::blit(src,dest_rect,src_rect);
}



#if (DEBUG == 2)
    Log << nl << "VideoGLSurface::blit (RGBSurface& src," << dest_rect << ", " << src_rect << ") done.";
#endif

return res;
}

//Blit src into the current surface.
bool VideoGLSurface::blit (GLSurface& glsrc, Rect& dest_rect, const Rect& src_rect)
{
    #if (DEBUG == 2)
    Log << nl << "VideoGLSurface::blit (GLSurface& src," << dest_rect << ", " << src_rect << ") called...";
#endif

//For safety
//if OpenGL is not set
if ( ! isOpenGLset() )
{
    return VideoSurface::blit(glsrc,dest_rect,src_rect);
}

        //TODO :  the conversion to texture should be done just after every modification (as a customisable default), as render must remain optimum,
        // only the emergency conversion to display format is useful here. Maybe even not...
        if ( glsrc.modified )
        {
            glsrc.computeGLWidthHeight();
            glsrc.convertPixels();
            glsrc.optimised = false; // to trigger regeneration of texture if needed
        }

        if ( ! glsrc.optimised )
        {
                //generate the GL texture if needed
                glsrc.convertToDisplayFormat();
        }


        //Log << nl << glsrc.getPixelFormat();

        //in case the dest_rect is of different size than src_rect, we need to avoid scaling
        // of the texture by opengl
        dest_rect.resetw( min ( dest_rect.getw(), src_rect.getw()) );
        dest_rect.reseth( min ( dest_rect.geth(), src_rect.geth()) );

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
            //glEnable(GL_ALPHA_TEST);
            //alpha meaning in SDL : 255 = opaque, 0 = transparent
            //glAlphaFunc(GL_GREATER,0.0f);
            // need to have same alpha meaning in OpenGL...
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);// -> this works for transparent = 1.0f and opaque = 0.0f
            //here we need
            //glBlendFunc( GL_ONE_MINUS_SRC_ALPHA,GL_SRC_ALPHA);
        }

        //Enable texturing
        glEnable(GL_TEXTURE_2D);

        //Load the texture
        glBindTexture(GL_TEXTURE_2D, glsrc.textureHandle);
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


        if ( glsrc.isSRCAlphaset() || glsrc.isSRCColorKeyset())
        {
            glDisable(GL_ALPHA_TEST);
            glDisable(GL_BLEND);
        }

        //Disable texturing
        glDisable(GL_TEXTURE_2D);


#if (DEBUG == 2)
    Log << nl << "VideoGLSurface::blit (GLSurface& src," << dest_rect << ", " << src_rect << ") done.";
#endif

    return true;
}



//Fill
bool VideoGLSurface::fill (const PixelColor& pcolor)
{
    Rect dest_rect(0,0,getWidth(), getHeight());
    return fill( pcolor, dest_rect );
}

bool VideoGLSurface::fill (const PixelColor& pcolor, Rect dest_rect)
{

/////TODO : FIX IT

#if (DEBUG == 2)
    Log << nl << "VideoGLSurface::fill ( " << color << ", " << dest_rect << ") called...";
#endif
    bool success = false;

    if ( isOpenGLset() )
    {
    //render it
    //2D Rendering

    glDisable( GL_DEPTH_TEST ) ;
    glMatrixMode( GL_PROJECTION ) ;
    glLoadIdentity() ;

    glOrtho( 0, getWidth(), getHeight(), 0, 0, 1 ) ;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    //TODO : this might be improved without using Color
    //there should be a more direct way...
    Color color= getPixelFormat().getColor(pcolor);
    if ( color.hasAlpha() )
    {
        glEnable(GL_BLEND);
        //glEnable(GL_ALPHA_TEST);
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
    }
    else
    {
        success = VideoSurface::fill(pcolor,dest_rect);
    }

#if (DEBUG == 2)
    Log << nl << "VideoGLSurface::fill ( " << pcolor << ", " << dest_rect << ") called...";
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

