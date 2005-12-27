#include "SDLVideoInfo.hh"
#include "SDLManager.hh"
namespace SDL {

//VideoInfo* VideoInfo::_Instance=NULL;

//beware : throw bad_alloc if SDL_GetVideoInfo failed.
//Usefull for windows because this must be called AFTER SDL_setVideo
//On linux/unix this should be called BEFORE to set best pixelmode...
VideoInfo::VideoInfo(void) throw (std::logic_error)
try : _info(SDL_GetVideoInfo())
{
	if (_info==NULL)
		throw std::logic_error("SDL_GetVideoInfo() return NULL");
}
catch (std::exception &e)
{
	Log << "Exception catched in VideoInfo Constructor !!!" << nl << e.what() ;
	//_info should remain NULL if there was an error...
	//and *this* is not constructed since we throw an exception
};



std::string VideoInfo::getDriverName(void) const
{
	char name[32]; //32 should be enough
	SDL_VideoDriverName(name,32);
	return std::string(name);
}

//return the SDLPixelFormat for the current video device
PixelFormat * VideoInfo::getPixelFormat() const
		{
#ifdef DEBUG
        assert(_info);
        Log << nl << "SDL_VideoInfo @ " << _info << std::endl;
        assert(_info->vfmt);
        Log << nl << "SDL_PixelFormat @ " << _info->vfmt << std::endl;
#endif
return new PixelFormat(_info->vfmt);
}

Logger & operator << (Logger & log, const VideoInfo & vinfo)
{
	log << nl << "VideoInfo::debug()"  << nl <<
	"- Driver Name : " << vinfo.getDriverName() << nl <<
	std::boolalpha <<
	"- Is it possible to create Hardware Surfaces? " << vinfo.isHWAvailable() << nl <<
	"- Is there a window manager available? " << vinfo.isWMAvailable() << nl <<
	"- Are hardware to hardware blits accelerated? " << vinfo.isBlitHWAccelAvailable() << nl <<
	"- Are hardware to hardware colorkey blits accelerated? " << vinfo.isBlitHWCCAccelAvailable() << nl <<
	"- Are hardware to hardware alpha blits accelerated? " << vinfo.isBlitHWAAccelAvailable() << nl <<
	"- Are software to hardware blits accelerated? " << vinfo.isBlitSWAccelAvailable() << nl <<
	"- Are software to hardware colorkey blits accelerated? " << vinfo.isBlitSWCCAccelAvailable() << nl <<
	"- Are software to hardware alpha blits accelerated? " << vinfo.isBlitSWAAccelAvailable() << nl <<
	"- Are color fills accelerated? " << vinfo.isBlitFillAccelAvailable() << nl <<
	"- Total amount of video memory in Kilobytes : " << vinfo.videoMemSize() << nl <<
	"- PixelFormat @ : "<< vinfo.getPixelFormat() ;

	return log;
}

} //namespace SDL
