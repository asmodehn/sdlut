#ifndef SDL_OVERLAY_HH
#define SDL_OVERLAY_HH

#include "SDLConfig.hh"
#include "SDLRect.hh"
#include "SDLVideoSurface.hh"
#include "SDLApp.hh"

/**
 * \class SDLOverlay
 *
 * \ingroup Video
 *
 * \brief This class wraps SDL_Overlay
 *
 * This class implement in C++ all the SDL functions related to SDL_Overlay
 *
 * \note NOT TESTED YET
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

namespace SDL {

//TODO : test it...
class Overlay
{
	//address of the SDL_Overlay structure should never change
	SDL_Overlay * const _overlay;

	typedef enum { YV12, IYUV, YUY2, UYVY, YVYU } Format;
	static Uint32 formatConvert(Format f )
	{
		Uint32 format = 0;
		switch (f)
		{
			case YV12 : format = SDL_YV12_OVERLAY; break;
			case IYUV : format = SDL_IYUV_OVERLAY; break;
			case YUY2 : format = SDL_YUY2_OVERLAY; break;
			case UYVY : format = SDL_UYVY_OVERLAY; break;
			case YVYU : format = SDL_YVYU_OVERLAY; break;
			default : break;//should not happen
		}
		return format;
	}

public :
	//Constructor
	//maybe the current display size must be used ?
	Overlay(Format f, int width = DEFAULT_DISPLAY_WIDTH, int height = DEFAULT_DISPLAY_HEIGHT, VideoSurface* dsurf = App::getInstance().getAppWindow()->getDisplay())
	: _overlay(SDL_CreateYUVOverlay(width,height,formatConvert(f),dsurf->_surf))
	{}
	//Destructor
	~Overlay() { SDL_FreeYUVOverlay(_overlay);}

	//Methods
	Format getFormat(void) const;
	int getHeight(void) const {return _overlay->w;}
	int getWidth(void) const {return _overlay->h;}
	int getPlanes(void) const {return _overlay->planes;}
	bool isHWAccel(void) const {return _overlay->hw_overlay;}

	//locks
	bool lock(void)
	{
		return SDL_LockYUVOverlay(_overlay)==0;
	}
	void unlock(void)
	{
		SDL_UnlockYUVOverlay(_overlay);
	}

	//return true of dislay is successfull
	bool display(Rect r)
	{
		return SDL_DisplayYUVOverlay(_overlay,r._rect) == 0;
	}
};

}

#endif
