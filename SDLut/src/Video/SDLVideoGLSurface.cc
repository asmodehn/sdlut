#include "Video/SDLVideoGLSurface.hh"
#include "SDLConfig.hh"
//#include <sstream>

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

        bool VideoGLSurface::refresh(void)
        {
			//This should always be true...
			//if (isOpenGLset())
			//{
				SDL_GL_SwapBuffers(); return true;
			//}
			//else
			//	return SDL_Flip(_surf.get()) == 0;
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
		bool VideoGLSurface::blit (const BaseSurface& src, Rect& dest_rect, const Rect& src_rect)
		{
#ifdef DEBUG
			Log << nl << "VideoGLSurfac::blit() " ;
#endif
			try
			{
				//Test if src is a GLSurface
				//TODO : design needs to make sure of this... somehow...
				const GLSurface& glsrc = dynamic_cast<const GLSurface&>(src);

	
			//render it
			//2D Rendering
	
			glDisable( GL_DEPTH_TEST ) ;
			glMatrixMode( GL_PROJECTION ) ;
			glLoadIdentity() ;

			glOrtho( 0, getWidth(), getHeight(), 0, 0, 1 ) ;
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
	
			//Enable texturing
			glEnable(GL_TEXTURE_2D);
	
			//Load the texture
			glBindTexture(GL_TEXTURE_2D, glsrc.textureHandle);
	
			glBegin( GL_QUADS ) ;
				glTexCoord2i( 0,0) ;
				glVertex2i( getWidth() - glsrc.getWidth() , getHeight()- glsrc.getHeight() ) ;

				glTexCoord2i( 0, 1) ;
				glVertex2i( getWidth() - glsrc.getWidth() , getHeight()) ;
	
				glTexCoord2i( 1, 1) ;
				glVertex2i( getWidth() , getHeight()) ;
				
				glTexCoord2i( 1, 0) ;
				glVertex2i( getWidth(), getHeight() - glsrc.getHeight() ) ;
			glEnd() ;


			//Disable texturing
			glDisable(GL_TEXTURE_2D);
			
			}
			catch (std::bad_cast& bc)
			{
				//If not convert it
				//TODO
				Log << "bad_cast caught: " << bc.what() ;
			}

			return true;
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
