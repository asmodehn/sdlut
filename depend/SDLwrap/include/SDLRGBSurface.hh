#ifndef SDLRGBSURFACE_HH
#define SDLRGBSURFACE_HH

/*******************************************************************************
 * Handle a Graphical Surface
 ******************************************************************************/

#include "SDLConfig.hh"
#include "SDLBaseSurface.hh"

namespace SDL {

class RGBSurface : public BaseSurface
{
	friend class SurfaceFactory;
	//friend class SDLDisplaySurface;

//SDL interprets each pixel as a 32-bit number, so our masks must depend
//on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    static const Uint32 r_default_mask = 0xff000000;
    static const Uint32 g_default_mask = 0x00ff0000;
    static const Uint32 b_default_mask = 0x0000ff00;
    static const Uint32 a_default_mask = 0x000000ff;
#else
    static const Uint32 r_default_mask = 0x000000ff;
    static const Uint32 g_default_mask = 0x0000ff00;
    static const Uint32 b_default_mask = 0x00ff0000;
    static const Uint32 a_default_mask = 0xff000000;
#endif

protected : //the client should not access to flags...

	//Constructor
	//Beware : the default flags should be the same than in Factory for consistency
	//BPP should NEVER be == 0 !!!!
	RGBSurface( int width, int height, int bpp,
					bool SWSURFACE = false, bool HWSURFACE = true, bool SRCCOLORKEY = false, bool SRCALPHA = false,
					Uint32 rmask = r_default_mask,
					Uint32 gmask = g_default_mask,
					Uint32 bmask = b_default_mask,
					Uint32 amask = a_default_mask ) throw (std::logic_error);
	RGBSurface( void * pixeldata, int depth, int pitch,
					int width, int height,
					Uint32 rmask = r_default_mask,
					Uint32 gmask = g_default_mask,
					Uint32 bmask = b_default_mask,
					Uint32 amask = a_default_mask ) throw (std::logic_error);
public :
	//creates surface from file, copying its content...
	RGBSurface( std::string filename )throw (std::logic_error);

protected : //the client should not access to flags...

	//Copy Constructor and cloning constructors...
	//RGBSurface(const RGBSurface &, bool cloneToDisplay = false, bool alpha = false) throw (std::logic_error);
	//Clone To display should be in Factory...
  RGBSurface(const RGBSurface & s , const SDL::PixelFormat & fmt, Uint32 flags, bool cloning = false) throw (std::logic_error);
	//no pixel format use the one from the surface
  RGBSurface(const RGBSurface & s , Uint32 flags, bool cloning = false) throw (std::logic_error);

public :
	//should be used as the default copy constructor. But should also be able to get DisplaySurface as input...
  RGBSurface(const BaseSurface & s , bool cloning = false, bool toDisplay = true, bool alpha = false) throw (std::logic_error);

	//not sure if this is useful or not, but the default copy constructor has to be properly overloaded
	//RGBSurface(const RGBSurface & s , bool cloning = false, bool toDisplay = true, bool alpha = false) throw (std::logic_error);

  bool setColorKey(const RGBColor &, const PixelFormat & pformat, bool rleAccel = true);


	//Use Standard Colors here
	//setPixel();
	//getPixel();

/*	void setUpdateRect(int x, int y, int w, int h);
	int update(void);
*/

	//Accesseurs - are they all really usefull ?
	inline bool isSRCColorKeyset(void) {return ( SDL_SRCCOLORKEY & _surf->flags ) != 0;}
	inline bool isSRCAlphaset(void) {return ( SDL_SRCALPHA & _surf->flags ) != 0;}


};

} //namespace SDL

#endif
