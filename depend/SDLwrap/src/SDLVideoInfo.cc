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

void VideoInfo::debug(void) const
{
	Log << nl << "VideoInfo::debug()"  << nl <<
	"- Driver Name : " << getDriverName() << nl <<
	std::boolalpha <<
	"- Is it possible to create Hardware Surfaces? " << isHWAvailable() << nl <<
	"- Is there a window manager available? " << isWMAvailable() << nl <<
	"- Are hardware to hardware blits accelerated? " << isBlitHWAccelAvailable() << nl <<
	"- Are hardware to hardware colorkey blits accelerated? " << isBlitHWCCAccelAvailable() << nl <<
	"- Are hardware to hardware alpha blits accelerated? " << isBlitHWAAccelAvailable() << nl <<
	"- Are software to hardware blits accelerated? " << isBlitSWAccelAvailable() << nl <<
	"- Are software to hardware colorkey blits accelerated? " << isBlitSWCCAccelAvailable() << nl <<
	"- Are software to hardware alpha blits accelerated? " << isBlitSWAAccelAvailable() << nl <<
	"- Are color fills accelerated? " << isBlitFillAccelAvailable() << nl <<
	"- Total amount of video memory in Kilobytes : " << videoMemSize() << nl <<	std::endl;
	getPixelFormat().debug();
}

} //namespace SDL
