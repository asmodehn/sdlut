#include "Video/internal/SDLVideoInfo.hh"
#include "SDLManager.hh"

#include "SDLConfig.hh"

using namespace RAGE;

namespace SDLut
{
namespace video
{
namespace internal
{

///IF run before SDL_SetVideo, it should contain best available mode
///IF run after SDL_SetVideo, it will contain current used mode
VideoInfo::VideoInfo(void)
try :   pvm_sdl_vinfo(SDL_GetVideoInfo()), ptm_pformat(new PixelFormat(pvm_sdl_vinfo->vfmt)),
        ptm_videoflags(SDL_RESIZABLE | SDL_DOUBLEBUF | SDL_ANYFORMAT | SDL_HWSURFACE | SDL_HWPALETTE )
{
#ifdef DEBUG
    Log << nl << "VideoInfo::VideoInfo() called ...";
#endif

    if (pvm_sdl_vinfo==NULL)
        throw std::logic_error("SDL_GetVideoInfo() return NULL");
    else
    {

    //putting advised values as requested values
    ptm_requestedWidth = pvm_sdl_vinfo->current_w;
    ptm_requestedHeight = pvm_sdl_vinfo->current_h;
    ptm_requestedBPP = pvm_sdl_vinfo->vfmt->BitsPerPixel;

        //if (ptm_pformat)
        //    delete ptm_pformat, ptm_pformat = NULL;
        //ptm_pformat = new PixelFormat(pvm_sdl_vinfo->vfmt);
        pointerCopy = false;
    }

#ifdef DEBUG

    Log << nl << "VideoInfo::VideoInfo() done.";
#endif

}
catch (std::exception &e)
{
    Log << "VideoInfo:: Exception in Constructor !" << nl << e.what() << std::endl;
    //_info should remain NULL if there was an error...
    //and *this* is not constructed since we throw an exception
}

VideoInfo::VideoInfo(unsigned int width, unsigned int height, unsigned int bpp, unsigned long vflags)
try
:
    pvm_sdl_vinfo(SDL_GetVideoInfo()), ptm_pformat(new PixelFormat(pvm_sdl_vinfo->vfmt)), ptm_videoflags(vflags )
{
#ifdef DEBUG
    Log << nl << "VideoInfo::VideoInfo() called ...";
#endif

    if (pvm_sdl_vinfo==NULL)
        throw std::logic_error("SDL_GetVideoInfo() return NULL");
    else
    {

    //putting advised values as requested values
    ptm_requestedWidth = width;
    ptm_requestedHeight = height;
    ptm_requestedBPP = bpp;

        pointerCopy = false;
    }

#ifdef DEBUG

    Log << nl << "VideoInfo::VideoInfo() done.";
#endif

}
catch (std::exception &e)
{
    Log << "VideoInfo:: Exception in Constructor !" << nl << e.what() << std::endl;
    //_info should remain NULL if there was an error...
    //and *this* is not constructed since we throw an exception
}


VideoInfo::VideoInfo( const VideoInfo& vi)
        : pvm_sdl_vinfo(vi.pvm_sdl_vinfo), ptm_pformat(vi.ptm_pformat), ptm_videoflags(vi.ptm_videoflags)
{
    pointerCopy = true;
}

/*
VideoInfo& VideoInfo::operator=(const VideoInfo& vi)
{

    delete pvm_sdl_vinfo, pvm_sdl_vinfo = vi.pvm_sdl_vinfo
    delete ptm_pformat, ptm_pformat = vi.ptm_pformat;
    pointerCopy = true;
    return *this;
}
*/

bool VideoInfo::checkAvailableSize( const PixelFormat & fmt )
{
    SDL_Rect ** modes;
    bool res;
    //we copy the pixelformat (because of const behaviour...)
    SDL_PixelFormat* test_fmt= new SDL_PixelFormat( *(fmt.ptm_sdl_pformat));

    modes=SDL_ListModes(test_fmt, ptm_videoflags);
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
            for (int i=0;modes[i];++i)
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

bool VideoInfo::checkAvailableSize(void)
{
    return checkAvailableSize( getPixelFormat());
}

int VideoInfo::getSuggestedBPP(int width, int height)
{
#ifdef DEBUG
    Log << nl << "VideoSurface::getSuggestedBPP(" << width << ", " << height << ") called...";
#endif

    int res = SDL_VideoModeOK(width,height,getPixelFormat().getBitsPerPixel(),ptm_videoflags);

#ifdef DEBUG

    Log << nl << "VideoSurface::getSuggestedBPP(" << width << ", " << height << ") done.";
#endif

    return res;
}

std::auto_ptr <std::list <std::pair <int, int> > > VideoInfo::Get_Resolution_List()
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




VideoInfo::~VideoInfo()
{
#ifdef DEBUG
    Log << nl << "VideoInfo::~VideoInfo() called ...";
#endif

    if ( ! pointerCopy )
    {
        delete ptm_pformat;//, ptm_pformat = NULL;
    //delete pvm_sdl_vinfo; //This is managed by SDL, we cant delete that here
    }

#ifdef DEBUG

    Log << nl << "VideoInfo::~VideoInfo() done.";
#endif
}



//those methods just changes the static flags used on display creation.
//use the App::methods to also reset the display.
void VideoInfo::requestOpenGL(bool val)
{
    if (val)
        ptm_videoflags|= SDL_OPENGL;
    else
        ptm_videoflags&= (~SDL_OPENGL) ;
}
void VideoInfo::requestFullscreen(bool val)
{
    if (val)
        ptm_videoflags|= SDL_FULLSCREEN;
    else
        ptm_videoflags&= (~SDL_FULLSCREEN) ;
}
void VideoInfo::requestResizable(bool val)
{
    if (val)
        ptm_videoflags|= SDL_RESIZABLE;
    else
        ptm_videoflags&= (~SDL_RESIZABLE) ;
}
void VideoInfo::requestNoFrame(bool val)
{
    if (val)
        ptm_videoflags|= SDL_NOFRAME;
    else
        ptm_videoflags&= (~SDL_NOFRAME) ;
}
void VideoInfo::requestDoubleBuf(bool val)
{
    if (val)
        ptm_videoflags|= SDL_DOUBLEBUF;
    else
        ptm_videoflags&= (~SDL_DOUBLEBUF) ;
}
void VideoInfo::requestAnyFormat(bool val)
{
    if (val)
        ptm_videoflags|= SDL_ANYFORMAT;
    else
        ptm_videoflags&= (~SDL_ANYFORMAT) ;
}
void VideoInfo::requestSWSurface(bool val)
{
    if (val)
        ptm_videoflags|= SDL_SWSURFACE;
    else
        ptm_videoflags&= (~SDL_SWSURFACE) ;
}
void VideoInfo::requestHWSurface(bool val)
{
    if (val)
        ptm_videoflags|= SDL_HWSURFACE;
    else
        ptm_videoflags&= (~SDL_HWSURFACE) ;
}
void VideoInfo::requestHWPalette(bool val)
{
    if (val)
        ptm_videoflags|= SDL_HWPALETTE;
    else
        ptm_videoflags&= (~SDL_HWPALETTE) ;
}
void VideoInfo::requestAsyncBlit(bool val)
{
    if (val)
        ptm_videoflags|= SDL_ASYNCBLIT;
    else
        ptm_videoflags&= (~SDL_ASYNCBLIT) ;
}

void VideoInfo::requestSize(unsigned width, unsigned int height)
{
            //TODO : check if mode is available before changing request
            ptm_requestedHeight= height;
            ptm_requestedWidth = width;
}

void VideoInfo::requestBPP(unsigned short bpp)
        {
            //TODO : check mode is OK before changing request
         ptm_requestedBPP = bpp;
        }


    bool VideoInfo::isOpenGL() const
    {
        return ! (0 == ptm_videoflags & SDL_OPENGL) ;
    }
    bool VideoInfo::isFullscreen() const
    {
        return ! ( 0 == ptm_videoflags & SDL_FULLSCREEN);
    }
    bool VideoInfo::isResizable() const
    {
        return ! ( 0 == ptm_videoflags & SDL_RESIZABLE);
    }
    bool VideoInfo::isNoFrame() const
    {
        return ! ( 0 == ptm_videoflags & SDL_NOFRAME);
    }
    bool VideoInfo::isDoubleBuf() const
    {
        return ! ( 0 == ptm_videoflags & SDL_DOUBLEBUF);
    }
    bool VideoInfo::isAnyFormat() const
    {
        return ! ( 0 == ptm_videoflags & SDL_ANYFORMAT);
    }
    bool VideoInfo::isSWSurface() const
    {
        return ! ( 0 == ptm_videoflags & SDL_SWSURFACE);
    }
    bool VideoInfo::isHWSurface() const
    {
        return ! ( 0 == ptm_videoflags & SDL_HWSURFACE);
    }
    bool VideoInfo::isHWPalette() const
    {
        return ! ( 0 == ptm_videoflags & SDL_HWPALETTE);
    }
    bool VideoInfo::isAsyncBlit() const
    {
        return ! ( 0 == ptm_videoflags & SDL_ASYNCBLIT);
    }

std::string VideoInfo::getDriverName(void) const
{
    char name[32]; //32 should be enough
    SDL_VideoDriverName(name,32);
    return std::string(name);
}

//return true if hardware acceleration is enabled
bool VideoInfo::isHWAvailable() const
{
    return pvm_sdl_vinfo->hw_available;
}

//return true if a window manager is available
bool VideoInfo::isWMAvailable() const
{
    return pvm_sdl_vinfo->wm_available;
}

//return true if hardware to hardware blits are accelerated
bool VideoInfo::isBlitHWAccelAvailable() const
{
    return pvm_sdl_vinfo->blit_hw;
}

//return true if hardware to hardware colorkey blits are accelerated
bool VideoInfo::isBlitHWCKAccelAvailable() const
{
    return pvm_sdl_vinfo->blit_sw_CC;
}

//return true if hardware to hardware alpha blits are accelerated
bool VideoInfo::isBlitHWAAccelAvailable() const
{
    return pvm_sdl_vinfo->blit_sw_A;
}

//return true if software to hardware blits are accelerated
bool VideoInfo::isBlitSWAccelAvailable() const
{
    return pvm_sdl_vinfo->blit_sw;
}

//return true if software to hardware colorkey blits are accelerated
bool VideoInfo::isBlitSWCKAccelAvailable() const
{
    return pvm_sdl_vinfo->blit_sw_CC;
}

//return true if software to hardware alpha blits are accelerated
bool VideoInfo::isBlitSWAAccelAvailable() const
{
    return pvm_sdl_vinfo->blit_sw_A;
}

//return true if color fills are accelerated
bool VideoInfo::isBlitFillAccelAvailable() const
{
    return pvm_sdl_vinfo->blit_fill;
}

//return the total amount of video memory in kilobytes
unsigned long VideoInfo::videoMemSize() const
{
    return pvm_sdl_vinfo->video_mem;
}

//return current width of video mode, or of the desktop mode if called before SDL_SetVideoMode
unsigned int VideoInfo::getCurrentWidth() const
{
    return pvm_sdl_vinfo->current_w;
}
//return current height of video mode, or of the desktop mode if called before SDL_SetVideoMode
unsigned int VideoInfo::getCurrentHeight() const
{
    return pvm_sdl_vinfo->current_h;
}


//return the SDLPixelFormat for the current video device
const PixelFormat & VideoInfo::getPixelFormat() const
{
    return *ptm_pformat;
}

RAGE::Logger & operator << (RAGE::Logger & log, const VideoInfo & vinfo)
{
    log << nl << "VideoInfo :"  << nl <<
    " - Driver Name : " << vinfo.getDriverName() << nl <<
    std::boolalpha <<
    " - Is it possible to create Hardware Surfaces? " << vinfo.isHWAvailable() << nl <<
    " - Is there a window manager available? " << vinfo.isWMAvailable() << nl <<
    " - Are hardware to hardware blits accelerated? " << vinfo.isBlitHWAccelAvailable() << nl <<
    " - Are hardware to hardware colorkey blits accelerated? " << vinfo.isBlitHWCKAccelAvailable() << nl <<
    " - Are hardware to hardware alpha blits accelerated? " << vinfo.isBlitHWAAccelAvailable() << nl <<
    " - Are software to hardware blits accelerated? " << vinfo.isBlitSWAccelAvailable() << nl <<
    " - Are software to hardware colorkey blits accelerated? " << vinfo.isBlitSWCKAccelAvailable() << nl <<
    " - Are software to hardware alpha blits accelerated? " << vinfo.isBlitSWAAccelAvailable() << nl <<
    " - Are color fills accelerated? " << vinfo.isBlitFillAccelAvailable() << nl <<
    " - Total amount of video memory in Kilobytes : " << vinfo.videoMemSize() << nl <<
    " - PixelFormat @ : "<< vinfo.getPixelFormat() ;

    return log;
}

}
}
} //namespace SDLut::SDL
