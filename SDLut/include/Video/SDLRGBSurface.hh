#ifndef SDL_RGBSURFACE_HH
#define SDL_RGBSURFACE_HH

/*******************************************************************************
 * Handle a Graphical Surface
 ******************************************************************************/

#include "Video/SDLBaseSurface.hh"
#include "Video/SDLColor.hh"
#include "System/SDLRWOps.hh"

namespace RAGE
{
    namespace SDL {

class RGBSurface : public BaseSurface
{


	//To be able to construct RGBSurface from Font :
	friend class Font;
	friend class FontImpl;
	friend class FontExtend;
	
	///Conversion Constructor
    	explicit RGBSurface(SDL_Surface * s) : BaseSurface(s)
    	{} ///< This one should be called only by friends

	///Conversion Constructor with explicit ownership transfert
    	explicit RGBSurface(std::auto_ptr<SDL_Surface> s);


protected : //the client should not access to flags...

	static unsigned long RGBFlags;
	static RWOps defaultContent;
	static int offset;//usefull to debug RWOps
				
	//Constructor
	//Beware : the default flags should be the same than in Factory for consistency
	//BPP should NEVER be == 0 !!!!
	RGBSurface( int width, int height, int bpp) throw (std::logic_error);
	RGBSurface( void * pixeldata, int depth, int pitch, int width, int height ) throw (std::logic_error);

public :
	
	RGBSurface( const RGBAColor & color, int width , int height, int bpp )throw (std::logic_error);

    //creates surface from file, copying its content...
	RGBSurface( std::string filename )throw (std::logic_error);
	RGBSurface( std::string filename, const RGBAColor & colorKey )throw (std::logic_error);
	
	//creates a surface from a RWOps containing a image.
	RGBSurface (const RWOps & rwops)  throw (std::logic_error); //TODO : add optional format
	//default constructor
	//creates a surface from the embedded resources with a default image
	RGBSurface () throw (std::logic_error);

public :
	//should be used as the copy constructor. But should also be able to get DisplaySurface as input...
    RGBSurface(const RGBSurface & s ) throw (std::logic_error);
    RGBSurface& operator=(const RGBSurface& s);
    //Conversion constructor
    //NB : will get called if the Surface is not RGB only.
    RGBSurface(const BaseSurface & s ) throw (std::logic_error);
    RGBSurface& operator=(const BaseSurface& s);

	bool convert(const PixelFormat & pfmt, bool SWSURFACE = false, bool HWSURFACE = true, bool SRCCOLORKEY = false, bool SRCALPHA = false);
	
	static void resetFlags(bool SWSURFACE = true, bool HWSURFACE = false, bool SRCCOLORKEY = false, bool SRCALPHA = false);
	//Destructor
	~RGBSurface(){}

	bool setColorKeyAndAlpha(const RGBAColor &, bool rleAccel = true);


	//Use Standard Colors here
	//setPixel();
	//getPixel();

/*	void setUpdateRect(int x, int y, int w, int h);
	int update(void);
*/

	bool resize(int width, int height, bool keepcontent = false);

	//Accesseurs - are they all really usefull ?
	bool isSRCColorKeyset(void);
	bool isSRCAlphaset(void);

	bool optimise(bool alpha = false);
	bool flip(bool vertical = true, bool horizontal = false);

#ifdef HAVE_OPENGL
	//Check that the image's width is valid and then check that the image's width is a power of 2
	bool isGLvalid();
	//return a GL texture that you have to bind
	unsigned int generateTexture();
#endif


    friend Logger & operator << (Logger & ostr, const RGBSurface & surf);

};
    }
} //namespace RAGE::SDL

#endif
