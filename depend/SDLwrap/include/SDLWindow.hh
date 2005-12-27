#ifndef SDL_WINDOW_HH
#define SDL_WINDOW_HH

/**
 * \class SDLWindow
 *
 * \ingroup Video
 *
 * \brief This class is a 2DWindow
 *
 * This class implement in C++ the behaviour of SDLDdisplaySurface when the content is only 2D.
 *
 * \note should be only used by SDLSurfaceFactory for more safety...
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

#include "SDLConfig.hh"
#include "SDLDisplaySurface.hh"

namespace SDL {

class Window : public DisplaySurface
{
	//To access the contructor
	friend class AppWindow;

protected:

//todo : make it an embedded object not a pointer... might need some improvements in BaseSurface for the creation/copy
    RGBSurface * _backupscreen;

    //using the flags form DisplaySurface
	Window(int width, int height, int bpp) throw (std::logic_error);

public:

	//Destructor
	virtual ~Window();

	//just test if DoubleBuf is set.
	inline bool isDoubleBufset(void) const {return ( SDL_DOUBLEBUF & _surf->flags ) != 0;}

	bool resize(int width, int height);

	//TODO : SaveScreen -> backup the screen content in a RGBSurface...
	virtual bool saveContent();
	//TODO : restoreScreen -> blit the saved surface to the screen
	virtual bool restoreContent();

	bool update(void);

	//display specific informations
	friend Logger & operator << (Logger & log, const Window & win);


};

} //namespace SDL

#endif
