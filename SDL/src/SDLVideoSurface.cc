#include "SDLVideoSurface.hh"
//#include <sstream>

namespace RAGE
{
    namespace SDL
    {

        std::vector<int> VideoSurface::availableWidth;
        std::vector<int> VideoSurface::availableHeight;
        Uint32 VideoSurface::_defaultflags = SDL_RESIZABLE | SDL_DOUBLEBUF | SDL_ANYFORMAT | SDL_HWSURFACE | SDL_HWPALETTE ;

        //Constructor
        VideoSurface::VideoSurface(int width, int height, int bpp) throw (std::logic_error)
        try
        :
            BaseSurface(SDL_SetVideoMode(width,height,bpp,_defaultflags )),_background(0,0,0), _engine(NULL)
        {
#ifdef DEBUG
            Log << nl << "VideoSurface::VideoSurface() called ...";
#endif

             if (_surf == NULL)
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
        };

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
            assert( getVideoInfo());
            assert( getVideoInfo()->getPixelFormat());
#endif

            int res = SDL_VideoModeOK(width,height,getVideoInfo()->getPixelFormat()->getBitsPerPixel(),_defaultflags);

#ifdef DEBUG

            Log << nl << "VideoSurface::getSuggestedBPP(" << width << ", " << height << ") done.";
#endif

            return res;
        }


            bool VideoSurface::setEngine(Engine * engine)
            {
                assert(engine);
                _engine = engine;
                return _engine->init(getWidth(),getHeight());
            }

        bool VideoSurface::update(void)
        {

            fill(_background);
            if (_engine !=NULL )
            {
                _engine->render();
            }
            return SDL_Flip(_surf) == 0;
        }


        bool VideoSurface::setBGColor(const Color & color)
        {
#ifdef DEBUG
            Log << nl << "VideoSurface::setBGColor(" << color << ") called ...";
#endif

            bool res = false;

            _background=color;
            res = fill(_background);

#ifdef DEBUG

            Log << nl << "VideoSurface::setBGColor(" << color << ") done.";
#endif

            return res;

        }

        bool VideoSurface::resize(int width, int height)
        {

#ifdef DEBUG
            Log << nl << "VideoSurface::resize(" << width << ", " << height << ") called...";
#endif

            bool res = false;

            RGBSurface* _backupscreen;

            //if no engine that means no render loop implemented, we save the old screen
            if (_engine ==NULL)
            {
                // we create a new RGB surface to clone the display...
                _backupscreen= new RGBSurface(*this);
            }
            //BEWARE : should match DisplaySurface Constructor code
            SDL_Surface * newSurf = SDL_SetVideoMode(width,height,getBPP(),getFlags());

            if (newSurf==NULL) //SetVideoMode has failed
            {
                Log << "Unable to resize to " << width << " x " << height << " 2D display surface " << nl << GetError();
                return false;
            }
            assert(newSurf); // should be always OK
            _surf=newSurf;
            res = fill(_background);
            //BEWARE : According to the doc, the display surface should never be freed by the caller of SetVideoMode. SDL_Quit will handle that.
            if (_engine == NULL )
            {
                if (_backupscreen !=NULL) //if no engine, we blit the old surface on the new screen surface
                {
                    //to restore the content in the middle of the window
                    Point newpos;
                    newpos.setx( (getWidth()-_backupscreen->getWidth()) / 2 );
                    newpos.sety( (getHeight()-_backupscreen->getHeight()) / 2 );
                    res = res && blit(*_backupscreen, newpos);
                }
            }
            else
            {
                res = res && _engine->resize(width,height);
            }

#ifdef DEBUG
        Log << nl << "VideoSurface::resize(" << width << ", " << height << ") done.";
#endif

        return res;
    }


    bool VideoSurface::update(Rect r)
    {
        fill(_background);
        if (locked())
            return false;//to prevent calling while locked
        else
            SDL_UpdateRect(_surf, r.getx(), r.gety(), r.getw(), r.geth());
        return true;
    }

    bool VideoSurface::update(std::vector<Rect> rlist)
    {
        fill(_background);
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
}
} //namespace RAGE::SDL
