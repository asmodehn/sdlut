#include "Video/SDLVideoInfo.hh"
#include "SDLManager.hh"

#include "SDLConfig.hh"
namespace RAGE
{
namespace SDL
{

//VideoInfo* VideoInfo::_Instance=NULL;

//beware : throw bad_alloc if SDL_GetVideoInfo failed.
//Usefull for windows because this must be called AFTER SDL_setVideo
//On linux/unix this should be called BEFORE to set best pixelmode...
VideoInfo::VideoInfo(void) throw (std::logic_error)
try
:
    pvm_sdl_vinfo(SDL_GetVideoInfo()),ptm_pformat(NULL)
{
#ifdef DEBUG
    Log << nl << "VideoInfo::VideoInfo() called ...";
#endif

    if (pvm_sdl_vinfo==NULL)
        throw std::logic_error("SDL_GetVideoInfo() return NULL");
    else
        ptm_pformat = new PixelFormat(pvm_sdl_vinfo->vfmt);

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
        : pvm_sdl_vinfo(vi.pvm_sdl_vinfo), ptm_pformat(vi.ptm_pformat)
{

}

VideoInfo& VideoInfo::operator=(const VideoInfo& vi)
{
    delete ptm_pformat, ptm_pformat = NULL;
    ptm_pformat = vi.ptm_pformat;
    return *this;
}


VideoInfo::~VideoInfo()
{
#ifdef DEBUG
    Log << nl << "VideoInfo::~VideoInfo() called ...";
#endif

    delete ptm_pformat, ptm_pformat = NULL;
    //delete _info; //This is managed by SDL, we cant delete that here

#ifdef DEBUG

    Log << nl << "VideoInfo::~VideoInfo() done.";
#endif
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
    return SDL_GetVideoInfo()->current_w;
}
//return current height of video mode, or of the desktop mode if called before SDL_SetVideoMode
unsigned int VideoInfo::getCurrentHeight() const
{
    return SDL_GetVideoInfo()->current_h;
}


//return the SDLPixelFormat for the current video device
const PixelFormat & VideoInfo::getPixelFormat() const
{
    return *ptm_pformat;
}

Logger & operator << (Logger & log, const VideoInfo & vinfo)
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
} //namespace RAGE::SDL
