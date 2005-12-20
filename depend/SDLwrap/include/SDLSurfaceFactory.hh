#ifndef SDLSURFACEFACTORY_HH
#define SDLSURFACEFACTORY_HH

#include "SDLConfig.hh"

#include "SDLBaseSurface.hh"
#include "SDLDisplaySurface.hh"
#include "SDLRGBSurface.hh"
#include "SDLWindow.hh"
#include "SDLGLWindow.hh"

/**
 * \class SurfaceFactory
 *
 * \ingroup Video
 *
 * \brief This class is a a Factory for SDLSurfaces.
 *
 * This class implement a lot of functions related to SDLSurface in an easy and obvious way.
 * Because there is only one dislay surface, the related methods and members are static.
 *
 * \note maybe we will be able in the future to get rid of this... (not sure how yet)
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

namespace SDL {

/*******************************************************************************
 * This is a Factory, used to manage creation of all SDLSurfaces.
 * Because there is only one display surface, the related functions are static
 ******************************************************************************/

class SurfaceFactory
{

protected :
	static int displayWidth, displayHeight;
	static int displayBPP;
	static Uint32 displayFlags;
	static std::vector<int> availableDisplayWidth,availableDisplayHeight;
	static DisplaySurface* screen;

	int RGBWidth, RGBHeight;
	int RGBBPP;
	Uint32 RGBFlags;
	std::vector<RGBSurface*> surfaceList;


public:

	//Access to current screen
	static inline DisplaySurface* getScreen(void)
	{
		if (screen == NULL )
			return createDisplay();
		else
			return screen;
	}

	static inline bool isScreenSet(void)
	{ return screen!=NULL; }

	//This set the display flags for the future display surface
	//return false if no modes available for those flags
	static bool setDisplayFlags( bool openGL = false, bool fullScreen = false,
							bool resizable = true, bool noFrame = false,
							bool doubleBuf = true,  bool anyFormat = true,
							bool SWSurface = false ,bool HWSurface = true,
							bool HWPalette = true, bool asyncBlit = false);

	//This set the display size for the future display surface
	//return false if no video modes are available
	static bool setDisplaySize( int width = DEFAULT_DISPLAY_WIDTH, int height = DEFAULT_DISPLAY_HEIGHT);

	//This set the display bpp for the future display surface
	static void setDisplayBPP( int bpp = DEFAULT_DISPLAY_BPP)
	{
		displayBPP = bpp;
	}


	//This manage display creation. If there is already one display created,
	//the older one is deleted by calling the singleton initializer...
	//Then a new display with different parameters can be created
    static DisplaySurface* createDisplay(std::string title = DEFAULT_WINDOW_TITLE, std::string icon = DEFAULT_WINDOW_ICON );

	//Check if there is any available display size for the current displayFlags
	//return false if there are none.
    //No PixelFormat means using the one from VideoInfo
    static bool checkAvailableDisplaySize(void);
    static bool checkAvailableDisplaySize(const PixelFormat& fmt);

	//return 0 if the current mode is not supported under any depth,
	//otherwise return the bpp of the best suitable video mode
	static int checkVideoMode(void);

    //if the first element is -1, any size will be ok;
    static inline std::vector<int> getAvailableDisplayHeight() {return availableDisplayHeight;}
    static inline std::vector<int> getAvailableDisplayWidth() {return availableDisplayWidth;}

    //Factory for RGBSurfaces
    SurfaceFactory(int rgbWidth = DEFAULT_RGB_WIDTH, int rgbHeight = DEFAULT_RGB_HEIGHT, int rgbBPP = DEFAULT_RGB_BPP)
	{
		setRGBSize(rgbWidth,rgbHeight); setRGBBPP(rgbBPP); setRGBFlags();
	}
	~SurfaceFactory()
	{
		for (unsigned int i=0; i<surfaceList.size(); i++) delete surfaceList[i];
	}

    bool setRGBFlags( bool SWSURFACE = true, bool HWSURFACE = false, bool SRCCOLORKEY = false, bool SRCALPHA = false);
    void setRGBSize( int width, int height)
    {
		RGBWidth = width; RGBHeight = height;
	}
    void setRGBBPP ( int bpp )
    {
		RGBBPP = bpp;
	}
	//return the index of the created surface in the list
	//if the surface cannot be created return the last created surface
//	  unsigned int createRGBSurface(void);
//    unsigned int createRGBSurface(int width , int height , Color color = Color() );
//    unsigned int createRGBSurface(void* pixeldata, int depth, int pitch);
//    creates surfaces from picture files.
//    unsigned int createRGBSurface( std::string filename );
//    same than above. also allow you to specify a background (to supprim)
//    unsigned int createRGBSurface( std::string filename, const RGBColor & bgcolor );

    // Also allows you to specify a colorkey if your file doesnt allow alpha
    //unsigned int createRGBSurface( std::string filename, const RGBColor & bgcolor );
    //BROKEN ?!?

    //Handy method to clone a RGBSurface already in the Factory
    unsigned int clone(int index,int times = 1); // clone the one on index

    unsigned int cloneToDisplay(int index,int times = 1, bool alpha = false); // clone the one on index, optimized for display
    //access to RGBSurface created by the Factory
    inline RGBSurface* getSurface(unsigned int index) {return surfaceList.at(index);}
    //is that really usefull ??
    inline std::vector<RGBSurface*> getSurfaceList(void) { return surfaceList; }

};

//The factory manage cloning rgbSurfaces ( prototype may help for rgb surfaces ? )

}//namespace SDL

#endif
