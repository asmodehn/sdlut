#include "SDLVideoSurface.hh"
#include "SDLEngine.hh"
//#include <sstream>

namespace SDL
{

    std::vector<int> VideoSurface::availableWidth;
    std::vector<int> VideoSurface::availableHeight;
    Uint32 VideoSurface::_defaultflags = SDL_RESIZABLE | SDL_DOUBLEBUF | SDL_ANYFORMAT | SDL_HWSURFACE | SDL_HWPALETTE ;

    //Constructor
    VideoSurface::VideoSurface(int width, int height, int bpp, Uint32 flags, Engine * engine) throw (std::logic_error)
    try
    :
        BaseSurface(SDL_SetVideoMode(width,height,bpp,flags )),_engine(engine),_backupscreen(NULL)
    {
        if (_surf == NULL)
        {
            Log << nl <<"Unable to set " << width << " x " << height << " display surface : ";
            throw std::logic_error("SDL_SetVideoMode() return NULL");
        }

        //If a caption has been defined
        //SDL_WM_SetCaption(_title.c_str(), _icon.c_str());
        //shouldnt be needed if already done before...

    }
    catch (std::exception &e)
    {
        Log << nl << "Exception catched in VideoSurface Constructor !!!" << nl <<
        e.what() << nl << GetError() << std::endl;
        //TODO : much more explicit error message...
    };

    VideoSurface::~VideoSurface()
    {
        if (_backupscreen !=NULL )
            delete _backupscreen;
    }


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



        return res;
    }

    bool VideoSurface::checkAvailableSize(void)
    {
        return checkAvailableSize( getVideoInfo()->getPixelFormat());
    }

    int VideoSurface::getSuggestedBPP(int width, int height)
    {
#ifdef DEBUG
        assert( getVideoInfo());
        Log << nl << "VideoInfo Accessible @ " << getVideoInfo() << std::endl;
        assert( getVideoInfo()->getPixelFormat());
        Log << nl << "PixelFormat Accessible @ " << getVideoInfo()->getPixelFormat() << std::endl;
#endif

        return SDL_VideoModeOK(width,height,getVideoInfo()->getPixelFormat()->getBitsPerPixel(),_defaultflags);
    }

    bool VideoSurface::update(void)
    {
        //fill(_engine->_background);
        _engine->render();
        return SDL_Flip(_surf) == 0;
    }

    //SaveScreen -> backup the screen content in a RGBSurface...
    bool VideoSurface::saveContent(void)
    {
        bool enginesave=false;
        //if the engine cant save, then we take a screenshot and use it
        if (_engine==NULL || (enginesave=_engine->saveContent())==false)
        {
            if (_backupscreen != NULL )
                delete _backupscreen;

            Log << nl << "Window::saveContent()" << std::endl;
            // we create a new RGB surface to clone the display...
            _backupscreen= new RGBSurface(*this);
        }

        return enginesave || _backupscreen!=NULL;
    }

    //restoreScreen -> blit the saved surface to the center of the screen
    bool VideoSurface::restoreContent(void)
    {
        bool res;

        bool enginerestore=false;
        //if the engine cant save, then we take a screenshot and use it
        if (_engine==NULL || (enginerestore=_engine->restoreContent())==false)
        {
            if (_backupscreen == NULL)
                return false;
            Log << nl << "Window::restoreContent()" << std::endl;

            //to restore the content in the middle of the window
            Point newpos;
            newpos.setx( (getWidth()-_backupscreen->getWidth()) / 2 );
            newpos.sety( (getHeight()-_backupscreen->getHeight()) / 2 );

            Log << nl << "Blitting backupscreen at " << newpos << std::endl;
            res = blit(*_backupscreen, newpos);
        }

        return enginerestore || res;
    }

    void VideoSurface::setBGColor(const Color & color)
    {
        assert(_engine);
        _engine->setBGColor(color);
        fill(_engine->_background);
    }

    bool VideoSurface::resize(int width, int height)
    {
        bool res = false;
        //BEWARE : should match DisplaySurface Constructor code
        SDL_Surface * newSurf = SDL_SetVideoMode(width,height,getBPP(),getFlags());

        if (newSurf==NULL) //SetVideoMode has failed
        {
            Log << "Unable to resize to " << width << " x " << height << " 2D display surface " << nl << GetError();
        }
        else //setvideoMode successfull
        {
            _surf=newSurf;
            res = true;
            //BEWARE : According to the doc, the display surface should never be freed by the caller of SetVideoMode. SDL_Quit will handle that.
            fill(_engine->_background);
        }

        return res;
    }


    bool VideoSurface::update(Rect r)
    {
        if (locked())
            return false;//to prevent calling while locked
        else
            SDL_UpdateRect(_surf, r.getx(), r.gety(), r.getw(), r.geth());
        return true;
    }

    bool VideoSurface::update(std::vector<Rect> rlist)
    {
        if (locked())
            return false;//to prevent calling while locked
        else
        {
            SDL_Rect* list = new SDL_Rect[rlist.size()];
            for (unsigned int i=0; i<rlist.size() ; i++)
                list[i]=*(rlist[i]._rect);
            SDL_UpdateRects(_surf, rlist.size(), list);
        }
        return true;
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

} //namespace SDL
