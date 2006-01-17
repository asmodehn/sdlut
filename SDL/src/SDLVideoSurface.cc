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
        VideoSurface::VideoSurface(int width, int height, int bpp, Engine * engine) throw (std::logic_error)
        try
:
            BaseSurface(SDL_SetVideoMode(width,height,bpp,_defaultflags )), _engine(engine)
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

        bool VideoSurface::update(void)
        {
            if (_engine !=NULL )
                _engine->render();
            return SDL_Flip(_surf) == 0;
        }

        //SaveScreen -> backup the screen content in a RGBSurface...
        bool VideoSurface::saveContent(void)
        {
            if (_engine!=NULL)
                return _engine->saveContent();
            else
                return false;
        }

        //restoreScreen -> blit the saved surface to the center of the screen
        bool VideoSurface::restoreContent(void)
        {

            //if the engine cant save, then we take a screenshot and use it
            if (_engine!=NULL )
                return _engine->restoreContent();
            else
                return false;
        }

        bool VideoSurface::setBGColor(const Color & color)
        {
#ifdef DEBUG
            assert(_engine);
            Log << nl << "VideoSurface::setBGColor(" << color << ") called ...";
#endif

            bool res = false;
            if ( _engine != NULL )
            {
                _engine->setBGColor(color);
                res = true;
            }
            else
            {
                Log << nl << "Warning : setBGColor ignored : Engine not set.";
            }


#ifdef DEBUG
            Log << nl << "VideoSurface::setBGColor(" << color << ") done.";
#endif
            return res;

        }

        bool VideoSurface::resize(int width, int height)
        {
            Log << nl << " resizing VideoSurface";
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
                if (_engine != NULL )
                {
                    Log << nl << "Resizing Engine";
                    _engine->resize(width,height);
                }
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
    }
} //namespace RAGE::SDL
