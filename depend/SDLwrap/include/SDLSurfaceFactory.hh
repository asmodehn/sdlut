#ifndef SDLSURFACEFACTORY_HH
#define SDLSURFACEFACTORY_HH

#include "SDLConfig.hh"

#include "SDLBaseSurface.hh"
#include "SDLDisplaySurface.hh"
#include "SDLRGBSurface.hh"
#include "SDLWindow.hh"
#include "SDLGLWindow.hh"

/*******************************************************************************
 * This is a Factory, used to manage creation of all SDLSurfaces.
 * Because there is only one display surface, the related functions are static
 ******************************************************************************/

class SDLSurfaceFactory
{
	
protected :
	static int displayWidth, displayHeight;
	static int displayBPP;
	static Uint32 displayFlags;
	static std::vector<int> availableDisplayWidth,availableDisplayHeight;	
	static SDLDisplaySurface* screen;
	
	int RGBWidth, RGBHeight;
	int RGBBPP;
	Uint32 RGBFlags;
	std::vector<SDLRGBSurface*> surfaceList;

	
public:
	
	//Access to current screen
	static inline SDLDisplaySurface* getScreen(void)
	{
		if (screen == NULL )
			return createDisplay();
		else
			return screen;
	}
	
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
    static SDLDisplaySurface* createDisplay(std::string title = DEFAULT_WINDOW_TITLE, std::string icon = DEFAULT_WINDOW_ICON );
	    
	//Check if there is any available display size for the current displayFlags
	//return false if there are none.
    //No PixelFormat means using the one from VideoInfo
    static bool checkAvailableDisplaySize(void);
    static bool checkAvailableDisplaySize(const SDLPixelFormat& fmt);
    
	//return 0 if the current mode is not supported under any depth,
	//otherwise return the bpp of the best suitable video mode
	static int checkVideoMode(void);
    
    //if the first element is -1, any size will be ok;
    static inline std::vector<int> getAvailableDisplayHeight() {return availableDisplayHeight;}
    static inline std::vector<int> getAvailableDisplayWidth() {return availableDisplayWidth;}    
    
    //Factory for RGBSurfaces
    SDLSurfaceFactory(int rgbWidth = DEFAULT_RGB_WIDTH, int rgbHeight = DEFAULT_RGB_HEIGHT, int rgbBPP = DEFAULT_RGB_BPP)
	{
		setRGBSize(rgbWidth,rgbHeight); setRGBBPP(rgbBPP); setRGBFlags();
	}
	~SDLSurfaceFactory()
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
	//returns NULL if the RGB Surface cannot be created
	SDLRGBSurface* createRGBSurface(void);
    SDLRGBSurface* createRGBSurface(int width , int height , SDLColor color = SDLColor() );
    SDLRGBSurface* createRGBSurface(void* pixeldata, int depth, int pitch);
    //creates surfaces from picture files.
    SDLRGBSurface* createRGBSurface( std::string filename );
    //same than above. Also allows you to specify a background if the picture file has some transparency
    SDLRGBSurface* createRGBSurface( std::string filename, SDLRGBColor bgcolor );
    //Handy method to clone the last created RGBSurface.
    inline bool clone(int times = 1) // clone the last
    {	return clone(surfaceList.size()-1,times); }
    bool clone(int index,int times = 1); // clone the one on index
    inline bool cloneToDisplay(int times = 1, bool alpha = false) // clone the last, optimized for display
    {	return cloneToDisplay(surfaceList.size()-1,times,alpha); }
    bool cloneToDisplay(int index,int times = 1, bool alpha = false); // clone the one on index, optimized for display
    //access to RGBSurface created by the Factory
    inline std::vector<SDLRGBSurface*> getSurfaceList(void) { return surfaceList; }
    
};

//The factory manage cloning rgbSurfaces ( prototype may help for rgb surfaces ? )

#endif
