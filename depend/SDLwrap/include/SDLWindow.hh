#ifndef SDLWINDOW_HH
#define SDLWINDOW_HH

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
	friend class SurfaceFactory;
	
protected:
	
	//Contructor : build the super
	//BEWARE : flags must be the same than in factory...
	Window(int width, int height, int bpp, Uint32 flags) throw (std::logic_error);
	
public:
	
	//Destructor
	~Window() {}
	
	//just test if DoubleBuf is set.
	inline bool isDoubleBufset(void) const {return ( SDL_DOUBLEBUF & _surf->flags ) != 0;}
	
	bool resize(int width, int height);
	
	//TODO : SaveScreen -> backup the screen content in a RGBSurface...
	virtual RGBSurface * save(void);
	//TODO : restoreScreen -> blit the saved surface to the screen
	virtual bool restore(const RGBSurface& savedScreen);
	
	bool update(void);

	//display specific informations
	void debug(void) const;

   	
};

} //namespace SDL

#endif
