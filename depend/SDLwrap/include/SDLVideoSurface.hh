#ifndef SDL_VideoSurface_HH
#define SDL_VideoSurface_HH

/**
 * \class VideoSurface
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
class VideoSurface : public BaseSurface
{

	friend class Overlay;
	friend class Window;

protected:

	static Uint32 _defaultflags;
    Color _background;

    //todo : make it an embedded object not a pointer... might need some improvements in BaseSurface for the creation/copy
    RGBSurface * _backupscreen;

	//Constructor
	//Note : The user should not be able to set raw SDL flags manually.
	VideoSurface(int width, int height, int bpp, Uint32 flags = _defaultflags ) throw (std::logic_error);

public:

    static std::vector<int> availableWidth,availableHeight;

	//Destructor
	virtual ~VideoSurface();
	//this kind of surface shouldnt be deleted by hand. the raw SDL methods takes care of it

//Save Screen -> backup the screen content in a new RGBSurface...
	virtual bool saveContent(void);
	//restore Screen -> blit the saved surface to the center of the display surface
	virtual bool restoreContent(void);
  //to resize the display
  virtual bool resize (int width, int height);
	//to update the display
	virtual bool update(void);

    //set the backgrund color
    virtual void setBGColor(const Color & color) { _background = color; fill(_background);}
    virtual Color getBGColor () { return _background;}


	//Maybe in Window only ?
	bool update(Rect r);
	bool update(std::vector<Rect> rlist);
	//May be using a default value.. depending on what has to be done for GLWindow



    //those methods just changes the static flags used on display creation.
	//use the App::methods to also reset the display.
	static inline void setOpenGL(bool val)  { if (val) _defaultflags|= SDL_OPENGL; else _defaultflags&= (~SDL_OPENGL) ; }
	static inline void setFullscreen(bool val)  { if (val) _defaultflags|= SDL_FULLSCREEN; else _defaultflags&= (~SDL_FULLSCREEN) ; }
	static inline void setResizable(bool val) { if (val) _defaultflags|= SDL_RESIZABLE; else _defaultflags&= (~SDL_RESIZABLE) ;}
	static inline void setNoFrame(bool val) { if (val) _defaultflags|= SDL_NOFRAME; else _defaultflags&= (~SDL_NOFRAME) ;}
	static inline void setDoubleBuf(bool val) { if (val) _defaultflags|= SDL_DOUBLEBUF; else _defaultflags&= (~SDL_DOUBLEBUF) ;}
	static inline void setAnyFormat(bool val) { if (val) _defaultflags|= SDL_ANYFORMAT; else _defaultflags&= (~SDL_ANYFORMAT) ;}
	static inline void setSWSurface(bool val) { if (val) _defaultflags|= SDL_SWSURFACE; else _defaultflags&= (~SDL_SWSURFACE) ;}
	static inline void setHWSurface(bool val) { if (val) _defaultflags|= SDL_HWSURFACE; else _defaultflags&= (~SDL_HWSURFACE) ;}
	static inline void setHWPalette(bool val) { if (val) _defaultflags|= SDL_HWPALETTE; else _defaultflags&= (~SDL_HWPALETTE) ;}
	static inline void setAsyncBlit(bool val) { if (val) _defaultflags|= SDL_ASYNCBLIT; else _defaultflags&= (~SDL_ASYNCBLIT) ;}


	//Accessors
	inline bool isOpenGLset(void) const {return ( SDL_OPENGL & ((_surf!=NULL)?_surf->flags:_defaultflags )) != 0;}
	inline bool isFullScreenset(void) const {return ( SDL_FULLSCREEN & ((_surf!=NULL)?_surf->flags:_defaultflags )) != 0;}
	inline bool isResizableset(void) const {return ( SDL_RESIZABLE & ((_surf!=NULL)?_surf->flags:_defaultflags )) != 0;}
	inline bool isNoFrameset(void) const {return ( SDL_NOFRAME & ((_surf!=NULL)?_surf->flags:_defaultflags )) != 0;}
	inline bool isAnyFormatset(void) const {return ( SDL_ANYFORMAT & ((_surf!=NULL)?_surf->flags:_defaultflags )) != 0;}
	virtual inline bool isDoubleBufset(void) const {return ( SDL_DOUBLEBUF & ((_surf!=NULL)?_surf->flags:_defaultflags )) != 0;}
	//unused
	inline bool isASyncBlitset(void) const {return ( SDL_ASYNCBLIT & ((_surf!=NULL)?_surf->flags:_defaultflags )) != 0;}
	inline bool isHWPaletteset(void) const {return ( SDL_HWPALETTE & ((_surf!=NULL)?_surf->flags:_defaultflags )) != 0;}

	static bool checkAvailableSize( const PixelFormat * fmt );
	static bool checkAvailableSize( void);
    static int getSuggestedBPP(int width, int height);

	friend Logger & operator << (Logger & log, const VideoSurface & surf);
};

} //namespace SDL

#endif
