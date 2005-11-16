#include "SDLVideoInfo.hh"

namespace SDL {

VideoInfo* VideoInfo::_Instance=NULL;

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
	Config::addLog( "Exception catched in VideoInfo Constructor !!!" );
	//_info should remain NULL if there was an error...
	//and *this* is not constructed since we throw an exception
}


VideoInfo* VideoInfo::Info(void)
{
	if (_Instance == NULL)
	{
		try
		{
			_Instance=new VideoInfo();
		}
		catch (std::exception& e)
		{
			//Keep this catch to prevent program terminate...
			Config::addLog(e.what());
			//no need to delete Instance, since constructor throw an exception
			//the VideoInfo Instance wasn't built
		}
	}
	return _Instance;
}

std::string VideoInfo::getDriverName(void) const
{
	char name[32]; //32 should be enough
	SDL_VideoDriverName(name,32);
	return std::string(name);
}

void VideoInfo::debug(void) const
{
	std::stringstream logstr;
	logstr << "VideoInfo::debug()"  << "\n" <<
	"- Driver Name : " << getDriverName() << "\n" <<
	std::boolalpha <<
	"- Is it possible to create Hardware Surfaces? " << isHWAvailable() << "\n" <<
	"- Is there a window manager available? " << isWMAvailable() << "\n" <<
	"- Are hardware to hardware blits accelerated? " << isBlitHWAccelAvailable() << "\n" <<
	"- Are hardware to hardware colorkey blits accelerated? " << isBlitHWCCAccelAvailable() << "\n" <<
	"- Are hardware to hardware alpha blits accelerated? " << isBlitHWAAccelAvailable() << "\n" <<
	"- Are software to hardware blits accelerated? " << isBlitSWAccelAvailable() << "\n" <<
	"- Are software to hardware colorkey blits accelerated? " << isBlitSWCCAccelAvailable() << "\n" <<
	"- Are software to hardware alpha blits accelerated? " << isBlitSWAAccelAvailable() << "\n" <<
	"- Are color fills accelerated? " << isBlitFillAccelAvailable() << "\n" <<
	"- Total amount of video memory in Kilobytes : " << videoMemSize() <<
	std::endl;
	Config::addLog(logstr.str());

	getPixelFormat().debug();
}

} //namespace SDL
