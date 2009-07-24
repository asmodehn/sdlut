#ifndef SDL_OVERLAY_HH
#define SDL_OVERLAY_HH

#include "Math/SDLRect.hh"
#include "Video/SDLVideoSurface.hh"
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

struct SDL_Overlay;

namespace RAGE
{
    namespace SDL {

//TODO : test it...
class Overlay
{
	//address of the SDL_Overlay structure should never change
	SDL_Overlay * const _overlay;

	typedef enum { YV12, IYUV, YUY2, UYVY, YVYU } Format;
	static unsigned long formatConvert(Format f );

public :
	//Constructor
	//maybe the current display size must be used ?
	Overlay(Format f, int width = DEFAULT_DISPLAY_WIDTH, int height = DEFAULT_DISPLAY_HEIGHT, VideoSurface * dsurf = &App::getInstance().getDisplay().getDisplay());
	//Destructor
	~Overlay();

	//Methods
	Format getFormat(void) const;
	int getHeight(void) const;
	int getWidth(void) const;
	int getPlanes(void) const;
	bool isHWAccel(void) const;

	//locks
	bool lock(void);
	void unlock(void);

	//return true of dislay is successfull
	bool display(Rect r);
};
    }
}

#endif
