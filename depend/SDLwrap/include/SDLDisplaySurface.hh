#ifndef SDLDISPLAYSURFACE_HH
#define SDLDISPLAYSURFACE_HH

/**
 * \class DisplaySurface
 *
 * \ingroup Video
 * \ingroup WindowManager
 *
 * \brief This class is handle a display surface and also the Window Manager behaviour.
 *
 * This class has two derivatives depending if your display is 2D or 3D.
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

#include "SDLConfig.hh"
#include "SDLBaseSurface.hh"
#include "SDLRGBSurface.hh" //to help with backup of screen surface

namespace SDL {

//There can be only one -> Singleton Pattern
//Must be used via derivated class
class DisplaySurface : public BaseSurface
{

	friend class Overlay;
	//friend class AppWindow;

protected:

	static Uint32 flags;

	//Constructor
	//Note : The user should not be able to set raw SDL flags manually.
	DisplaySurface(int width, int height, int bpp, Uint32 flags) throw (std::logic_error);

public:

    static std::vector<int> availableWidth,availableHeight;

	//Destructor
	virtual ~DisplaySurface() {}
	//this kind of surface shouldnt be deleted by hand. the raw SDL methods takes care of it

//Save Screen -> backup the screen content in a new RGBSurface...
	virtual bool saveContent(void) = 0;
	//restore Screen -> blit the saved surface to the center of the display surface
	virtual bool restoreContent(void) = 0;
  //to resize the display
  virtual bool resize (int width, int height) = 0;
	//to update the display
	virtual bool update(void) = 0;

	//Maybe in Window only ?
	bool update(Rect r);
	bool update(std::vector<Rect> rlist);
	//May be using a default value.. depending on what has to be done for GLWindow



    //those methods just changes the static flags used on display creation.
	//use the App::methods to also reset the display.
	static inline void setOpenGL(bool val)  { if (val) flags|= SDL_OPENGL; else flags&= (~SDL_OPENGL) ; }
	static inline void setFullscreen(bool val)  { if (val) flags|= SDL_FULLSCREEN; else flags&= (~SDL_FULLSCREEN) ; }
	static inline void setResizable(bool val) { if (val) flags|= SDL_RESIZABLE; else flags&= (~SDL_RESIZABLE) ;}
	static inline void setNoFrame(bool val) { if (val) flags|= SDL_NOFRAME; else flags&= (~SDL_NOFRAME) ;}
	static inline void setDoubleBuf(bool val) { if (val) flags|= SDL_DOUBLEBUF; else flags&= (~SDL_DOUBLEBUF) ;}
	static inline void setAnyFormat(bool val) { if (val) flags|= SDL_ANYFORMAT; else flags&= (~SDL_ANYFORMAT) ;}
	static inline void setSWSurface(bool val) { if (val) flags|= SDL_SWSURFACE; else flags&= (~SDL_SWSURFACE) ;}
	static inline void setHWSurface(bool val) { if (val) flags|= SDL_HWSURFACE; else flags&= (~SDL_HWSURFACE) ;}
	static inline void setHWPalette(bool val) { if (val) flags|= SDL_HWPALETTE; else flags&= (~SDL_HWPALETTE) ;}
	static inline void setAsyncBlit(bool val) { if (val) flags|= SDL_ASYNCBLIT; else flags&= (~SDL_ASYNCBLIT) ;}


	//Accessors
	inline bool isOpenGLset(void) const {return ( SDL_OPENGL & (_surf!=NULL)?_surf->flags:flags ) != 0;}
	inline bool isFullScreenset(void) const {return ( SDL_FULLSCREEN & (_surf!=NULL)?_surf->flags:flags ) != 0;}
	inline bool isResizableset(void) const {return ( SDL_RESIZABLE & (_surf!=NULL)?_surf->flags:flags ) != 0;}
	inline bool isNoFrameset(void) const {return ( SDL_NOFRAME & (_surf!=NULL)?_surf->flags:flags ) != 0;}
	inline bool isAnyFormatset(void) const {return ( SDL_ANYFORMAT & (_surf!=NULL)?_surf->flags:flags ) != 0;}
	virtual inline bool isDoubleBufset(void) const {return ( SDL_DOUBLEBUF & (_surf!=NULL)?_surf->flags:flags ) != 0;}
	//unused
	inline bool isASyncBlitset(void) const {return ( SDL_ASYNCBLIT & (_surf!=NULL)?_surf->flags:flags ) != 0;}
	inline bool isHWPaletteset(void) const {return ( SDL_HWPALETTE & (_surf!=NULL)?_surf->flags:flags ) != 0;}

	static bool checkAvailableSize( const PixelFormat * fmt );
	static bool checkAvailableSize( void);
    static int getSuggestedBPP(int width, int height);

	virtual void debug(void) const;
};

} //namespace SDL

#endif
