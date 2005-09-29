#ifndef SDLGLWINDOW_HH
#define SDLGLWINDOW_HH

/*******************************************************************************
 * Handle an OpenGL Window
 * Beware : must only be used by Surface Factory
 ******************************************************************************/

#include "SDLConfig.hh"

#include "SDLDisplaySurface.hh"
#include "Interface3D.hh"
#include <cassert>

class SDLGLWindow : public SDLDisplaySurface
{
protected:
	static Interface3D* engine;

public:
	
	//Constructor
	SDLGLWindow(int width, int height, int bpp, Uint32 flags) throw (std::logic_error)
	: SDLDisplaySurface(width, height, bpp, flags)
	{
		engine->init(getWidth(),getHeight());
	}
	
	//Destructor
	~SDLGLWindow() {delete engine;}
	
	inline bool isOpenGLset(void) const {return SDL_OPENGL & _surf->flags;}

  bool resize (int width, int height);
  
  //TODO : Save Screen -> backup the screen content in a new RGBSurface AND SAVE THE CURRENT SCENE STATE...
	virtual SDLRGBSurface* save(void) {return NULL;}
	  
	bool update(void);//call scene3D->render
	
	//TODO : overload Basesurface functions that cannot be used here, because there is NO OPENGL Blit
	//or overload using opengl textures ...
	
	//Branch to another 3Dengine
	//static void set3DEngine(Interface3D* eng) {engine=eng;}
	
/*******************************************************************************
 * This is not recommended
 * Use it only for backward compatibility purpose
 //void enableBlit(void);
 //void disableBlit(void);
 //inline bool isBlitset(void) {return SDL_OPENGLBLIT & _flags;}
 //Usefull only if Blit is set
 //static void enableDoubleBuf(void);
 //static void disableDoubleBuf(void);
 //inline bool isDoubleBufset(void) const
 //{return SDL_DOUBLEBUF & screen()->getSurface()->flags;}
 ******************************************************************************/
};

#endif //SDLGLWINDOW_HH
