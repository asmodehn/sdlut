#include "Video/SDLVideoSurface.hh"
#include "SDLConfig.hh"
//#include <sstream>

namespace RAGE
{
    namespace SDL
    {

        std::vector<int> VideoSurface::availableWidth;
        std::vector<int> VideoSurface::availableHeight;
        unsigned long VideoSurface::_defaultflags = SDL_RESIZABLE | SDL_DOUBLEBUF | SDL_ANYFORMAT | SDL_HWSURFACE | SDL_HWPALETTE ;

        //Constructor
        VideoSurface::VideoSurface(int width, int height, int bpp) throw (std::logic_error)
        try
        :
            BaseSurface(SDL_SetVideoMode(width,height,bpp,_defaultflags )),_background(0,0,0)
        {
#ifdef DEBUG
            Log << nl << "VideoSurface::VideoSurface() called ...";
#endif

             if (!initialized())
            {
                Log << nl <<"Unable to set " << width << " x " << height << " display surface : ";
                throw std::logic_error("SDL_SetVideoMode() return NULL");
            }

#ifdef DEBUG
            Log << nl << "VideoSurface::VideoSurface() done.";
#endif

        }
        catch (std::exception &e)
        {
            Log << nl << "VideoSurface:: Exception in Constructor !" <<
            nl << e.what() << nl << GetError() << std::endl;
            //TODO : much more explicit error message...
        }

        VideoSurface::~VideoSurface()
        {}


        bool VideoSurface::checkAvailableSize( const PixelFormat * fmt )
        {
            SDL_Rect ** modes;
            bool res;
            //we copy the pixelformat (because of const behaviour...)
            SDL_PixelFormat* test_fmt= new SDL_PixelFormat( *(fmt->_pformat));

            modes=SDL_ListModes(test_fmt, _defaultflags);
            if (modes == (SDL_Rect **)0)
                res=false;
            else
            {
                availableWidth.clear();
                availableHeight.clear();

                if (modes == (SDL_Rect **)-1)
                {
                    availableWidth.push_back(-1);
                    availableHeight.push_back(-1);
                }
                else
                {
                    for(int i=0;modes[i];++i)
                    {
                        availableWidth.push_back(modes[i]->w);
                        availableHeight.push_back(modes[i]->h);
                    }
                }
                res=true;
            }

            Log << nl << "Available Modes : " ;
            if ( availableHeight[0] == -1 || availableWidth[0] == -1 )
                Log << "all" << std::endl;
            else
            {
                for (unsigned int i=0; i<availableHeight.size() ; i++)
                {
                    Log <<  "- " << availableHeight[i] << "x" << availableWidth[i] << nl;
                }
                Log << std::endl;
            }


	delete[] modes;
	delete test_fmt;
            return res;
        }

        bool VideoSurface::checkAvailableSize(void)
        {
            return checkAvailableSize( getVideoInfo()->getPixelFormat());
        }

        int VideoSurface::getSuggestedBPP(int width, int height)
        {
#ifdef DEBUG
            Log << nl << "VideoSurface::getSuggestedBPP(" << width << ", " << height << ") called...";
            assert( getVideoInfo()); //to make sure the auto_ptr is not 0
            assert( getVideoInfo()->getPixelFormat());
#endif

            int res = SDL_VideoModeOK(width,height,getVideoInfo()->getPixelFormat()->getBitsPerPixel(),_defaultflags);

#ifdef DEBUG

            Log << nl << "VideoSurface::getSuggestedBPP(" << width << ", " << height << ") done.";
#endif

            return res;
        }

		std::auto_ptr <std::list <std::pair <int, int> > > VideoSurface::Get_Resolution_List()
		{
			//NB:  we could use SDL_ListModes (http://www.libsdl.org/cgi/docwiki.cgi/SDL_ListModes) to do the same job as this function but it doesn't work well 

			std::auto_ptr <std::list <std::pair <int, int> > > res (new std::list <std::pair <int, int> > );

			//Add standard PC resolutions to the list (http://en.wikipedia.org/wiki/List_of_common_resolutions). This should be updated when new screen using others resolution will appear or if there r missing resolutions.
			res->push_back(std::pair<int,int>(800,600));
			res->push_back(std::pair<int,int>(856,480));
			res->push_back(std::pair<int,int>(960,540));
			res->push_back(std::pair<int,int>(960,720));
			res->push_back(std::pair<int,int>(1024,576));
			res->push_back(std::pair<int,int>(1024,768));
			res->push_back(std::pair<int,int>(1152,720));
			res->push_back(std::pair<int,int>(1152,864));
			res->push_back(std::pair<int,int>(1280,720));
			res->push_back(std::pair<int,int>(1280,768));
			res->push_back(std::pair<int,int>(1280,800));
			res->push_back(std::pair<int,int>(1280,960));
			res->push_back(std::pair<int,int>(1280,1024));
			res->push_back(std::pair<int,int>(1366,768));
			res->push_back(std::pair<int,int>(1400,1050));
			res->push_back(std::pair<int,int>(1440,900));
			res->push_back(std::pair<int,int>(1440,1080));
			res->push_back(std::pair<int,int>(1600,900));
			res->push_back(std::pair<int,int>(1600,1200));
			res->push_back(std::pair<int,int>(1680,1050));
			res->push_back(std::pair<int,int>(1920,1080));
			res->push_back(std::pair<int,int>(1920,1200));
			res->push_back(std::pair<int,int>(1920,1440));
			res->push_back(std::pair<int,int>(2048,1600));
			res->push_back(std::pair<int,int>(2560,1600));
			res->push_back(std::pair<int,int>(2560,2048));
			res->push_back(std::pair<int,int>(4096,2560));

			res->sort();
			res->unique();

			short bpp = 32; //we test for 32bit coz we only want resolutions available in all mode (8/16/24/32)
			for (std::list< std::pair<int, int> >::iterator it = res->begin(); it != res->end(); )
			{	
				if ( SDL_VideoModeOK(it->first, it->second, bpp, SDL_FULLSCREEN) == 0 )
					it = res->erase(it); //mode not available
				else
					++it;
			}

			return res;
		}


        bool VideoSurface::refresh(void)
        {
#ifdef HAVE_OPENGL
			if (isOpenGLset())
			{
				SDL_GL_SwapBuffers(); return true;
			}
			else
#endif //HAVE_OPENGL
				return SDL_Flip(_surf.get()) == 0;
        }

//TODO : rethink about that again...( recopy the content if 2D or not at all ??? )
        bool VideoSurface::resize(int width, int height, bool keepcontent)
        {

#ifdef DEBUG
            Log << nl << "VideoSurface::resize(" << width << ", " << height << ") called...";
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
        Log << nl << "VideoSurface::resize(" << width << ", " << height << ") succeeded.";
#endif
		res = true;
	    }

	    SDL_FreeSurface(oldSurf.release());

	    return (res && initialized());
    }


    bool VideoSurface::update(Rect r)
    {
        fill(_background);
        SDL_UpdateRect(_surf.get(), r.getx(), r.gety(), r.getw(), r.geth());
        return true;
    }

    bool VideoSurface::update(std::vector<Rect> rlist)
    {
        fill(_background);

        SDL_Rect* list = new SDL_Rect[rlist.size()];
        for (unsigned int i=0; i<rlist.size() ; i++)
            list[i]=*(rlist[i]._rect);
        SDL_UpdateRects(_surf.get(), rlist.size(), list);
 
        return true;
    }


    //those methods just changes the static flags used on display creation.
	//use the App::methods to also reset the display.
    void VideoSurface::setOpenGL(bool val)
    {
	    if (val)
		    _defaultflags|= SDL_OPENGL;
	    else
		    _defaultflags&= (~SDL_OPENGL) ;
    }
    void VideoSurface::setFullscreen(bool val)
    {
	    if (val)
		    _defaultflags|= SDL_FULLSCREEN;
	    else
		    _defaultflags&= (~SDL_FULLSCREEN) ;
    }
    void VideoSurface::setResizable(bool val)
    {
	    if (val)
		    _defaultflags|= SDL_RESIZABLE;
	    else
		    _defaultflags&= (~SDL_RESIZABLE) ;
    }
    void VideoSurface::setNoFrame(bool val)
    {
	    if (val)
		    _defaultflags|= SDL_NOFRAME;
	    else
		    _defaultflags&= (~SDL_NOFRAME) ;
    }
    void VideoSurface::setDoubleBuf(bool val)
    {
	    if (val)
		    _defaultflags|= SDL_DOUBLEBUF;
	    else
		    _defaultflags&= (~SDL_DOUBLEBUF) ;
    }
    void VideoSurface::setAnyFormat(bool val)
    {
	    if (val)
		    _defaultflags|= SDL_ANYFORMAT;
	    else
		    _defaultflags&= (~SDL_ANYFORMAT) ;
    }
    void VideoSurface::setSWSurface(bool val)
    {
	    if (val)
		    _defaultflags|= SDL_SWSURFACE;
	    else
		    _defaultflags&= (~SDL_SWSURFACE) ;
    }
    void VideoSurface::setHWSurface(bool val)
    {
	    if (val)
		    _defaultflags|= SDL_HWSURFACE;
	    else
		    _defaultflags&= (~SDL_HWSURFACE) ;
    }
    void VideoSurface::setHWPalette(bool val)
    {
	    if (val)
		    _defaultflags|= SDL_HWPALETTE;
	    else
		    _defaultflags&= (~SDL_HWPALETTE) ;
    }
    void VideoSurface::setAsyncBlit(bool val)
    {
	    if (val)
		    _defaultflags|= SDL_ASYNCBLIT;
	    else
		    _defaultflags&= (~SDL_ASYNCBLIT) ;
    }


            //Accessors
    bool VideoSurface::isOpenGLset(void) const
    {
	    return ( SDL_OPENGL & (initialized()?_surf->flags:_defaultflags )) != 0;
    }
    bool VideoSurface::isFullScreenset(void) const
    {
	    return ( SDL_FULLSCREEN & (initialized()?_surf->flags:_defaultflags )) != 0;
    }
    bool VideoSurface::isResizableset(void) const
    {
	    return ( SDL_RESIZABLE & (initialized()?_surf->flags:_defaultflags )) != 0;
    }
    bool VideoSurface::isNoFrameset(void) const
    {
	    return ( SDL_NOFRAME & (initialized()?_surf->flags:_defaultflags )) != 0;
    }
    bool VideoSurface::isAnyFormatset(void) const
    {
	    return ( SDL_ANYFORMAT & (initialized()?_surf->flags:_defaultflags )) != 0;
    }
    bool VideoSurface::isDoubleBufset(void) const
    {
	    return ( SDL_DOUBLEBUF & (initialized()?_surf->flags:_defaultflags )) != 0;
    }
            //unused
    bool VideoSurface::isASyncBlitset(void) const
    {
	    return ( SDL_ASYNCBLIT & (initialized()?_surf->flags:_defaultflags )) != 0;
    }
    bool VideoSurface::isHWPaletteset(void) const
    {
	    return ( SDL_HWPALETTE & (initialized()?_surf->flags:_defaultflags )) != 0;
    }


    Logger & operator << (Logger & log, const VideoSurface & surf)
    {
        //log << static_cast<BaseSurface>(surf);
        log << nl<<std::boolalpha << "- Fullscreen ? " << surf.isFullScreenset() << nl
        << "- Resizable ? " << surf.isResizableset() << nl
        << "- NoFrame ? " << surf.isNoFrameset() <<nl
        << "- AnyFormat ? " << surf.isAnyFormatset() << nl
        << "- Double Buffered ? " << surf.isDoubleBufset();
        return log;
    }
}
} //namespace RAGE::SDL
