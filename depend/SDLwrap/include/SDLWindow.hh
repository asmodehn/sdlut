#ifndef SDLWINDOW_HH
#define SDLWINDOW_HH

/*******************************************************************************
 * Handle a 2D Window
 * Beware : must only be used by Surface Factory
 ******************************************************************************/

#include "SDLConfig.hh"
#include "SDLDisplaySurface.hh"


class SDLWindow : public SDLDisplaySurface
{
	//To access the contructor
	friend class SDLSurfaceFactory;
	
protected:
	
	//Contructor : build the super
	//BEWARE : flags must be the same than in factory...
	SDLWindow(int width, int height, int bpp, Uint32 flags) throw (std::logic_error);
	
public:
	
	//Destructor
	~SDLWindow() {}
	
	//just test if DoubleBuf is set.
	inline bool isDoubleBufset(void) const {return SDL_DOUBLEBUF & _surf->flags;}
	
	bool resize(int width, int height);
	
	//TODO : SaveScreen -> backup the screen content in a RGBSurface...
	virtual SDLRGBSurface * save(void);
	//TODO : restoreScreen -> blit the saved surface to the screen
	virtual bool restore(const SDLRGBSurface& savedScreen);
	
	bool update(void);

	//display specific informations
	void debug(void) const;

   	
};


#endif
