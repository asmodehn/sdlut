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
//#include "SDLUserInput.hh"
#include "SDLVideoInfo.hh"
#include "SDLRGBSurface.hh" //to help with backup of screen surface

namespace SDL {

//There can be only one -> Singleton Pattern
//Must be used via derivated class
class DisplaySurface : public BaseSurface
{

	friend class Overlay;

protected:	
		
	static DisplaySurface* _screen;
	static std::string _title, _icon;
	
	//Constructor
	//Note : The user should not be able to set flags manually. use screen(...) for this
	DisplaySurface(int width, int height, int bpp, Uint32 flags) throw (std::logic_error);
	
	//NOTE : flags is still Uint32 here, because this should not be used by the client, but only by the factory...
public:
	
	//Destructor
	virtual ~DisplaySurface() {}

  //to resize the display
  virtual bool resize (int width, int height) = 0;
	//to update the display
	virtual bool update(void) = 0;
	//Maybe in Window only ?
	bool update(Rect r);
	bool update(std::vector<Rect> rlist);
	//May be using a default value.. depending on what has to be done for GLWindow
	
	//Save Screen -> backup the screen content in a new RGBSurface...
	virtual RGBSurface* save(void) = 0;
	//restore Screen -> blit the saved surface to the center of the display surface
	virtual bool restore(const RGBSurface& backupScreen) { return false; }
	
	//Accessors
	inline bool isOpenGLset(void) const {return ( SDL_OPENGL & _surf->flags ) != 0;}
	inline bool isFullScreenset(void) const {return ( SDL_FULLSCREEN & _surf->flags ) != 0;}
	inline bool isResizableset(void) const {return ( SDL_RESIZABLE & _surf->flags ) != 0;}					
	inline bool isNoFrameset(void) const {return ( SDL_NOFRAME & _surf->flags ) != 0;}
	inline bool isAnyFormatset(void) const {return ( SDL_ANYFORMAT & _surf->flags ) != 0;}
	virtual inline bool isDoubleBufset(void) const {return ( SDL_DOUBLEBUF & _surf->flags ) != 0;}
	//unused
	inline bool isASyncBlitset(void) const {return ( SDL_ASYNCBLIT & _surf->flags ) != 0;}
	inline bool isHWPaletteset(void) const {return ( SDL_HWPALETTE & _surf->flags ) != 0;}
	
		
	//WM methods
	static void setCaption(std::string title = DEFAULT_WINDOW_TITLE, std::string icon = DEFAULT_WINDOW_ICON);
	static void getCaption(std::string & title, std::string & icon);
	static inline void setTitle(std::string title) { setCaption(title); }
	static inline void setIcon(std::string icon) { setCaption(_title,icon); }
	//return true on success, false otherwise
	static bool iconify(void);
	static bool toggleFullScreen(void);
	/*enablegrabInput(void);
	disableGrabInput(void);
	queryGrabInput(void);
	*/
	virtual void debug(void) const;
};

} //namespace SDL

#endif
