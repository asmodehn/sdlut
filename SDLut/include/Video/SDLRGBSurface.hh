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

	//To be able to construct RGBSurface from Loader :
	friend class SurfaceLoader;

protected:
	///Conversion Constructor
    	explicit RGBSurface(SDL_Surface * s); ///< This one should be called only by friends

	///Conversion Constructor with explicit ownership transfert
    	explicit RGBSurface(std::auto_ptr<SDL_Surface> s);

public :
				
	//Constructor
	//BPP should NEVER be == 0 !!!!
	RGBSurface( int width, int height, int bpp,
				bool hardware = false,
				bool colorkey = false,
				bool alpha = false,
				unsigned long r_mask = 0,
				unsigned long g_mask = 0,
				unsigned long b_mask = 0,
				unsigned long a_mask = 0
				) throw (std::logic_error);

	RGBSurface( void * pixeldata, int depth, int pitch, int width, int height,
				unsigned long r_mask = 0,
				unsigned long g_mask = 0,
				unsigned long b_mask = 0,
				unsigned long a_mask = 0
				) throw (std::logic_error);

public :
	//should be used as the copy constructor. But should also be able to get DisplaySurface as input...
    RGBSurface(const RGBSurface & s ) throw (std::logic_error);
    RGBSurface& operator=(const RGBSurface& s);
    //Conversion constructor
    //NB : will get called if the Surface is not RGB only.
    RGBSurface(const BaseSurface & s ) throw (std::logic_error);
    RGBSurface& operator=(const BaseSurface& s);


	//Destructor
	virtual ~RGBSurface() {}

	bool setColorKeyAndAlpha(const RGBAColor &, bool rleAccel = true);


	//Use Standard Colors here
	//setPixel();
	//getPixel();

/*	void setUpdateRect(int x, int y, int w, int h);
	int update(void);
*/

	bool resize(int width, int height, bool keepcontent = false);

	bool isSRCColorKeyset(void);
	bool isSRCAlphaset(void);

	RGBColor getColorKey();

	virtual bool convertToDisplayFormat();

	bool flip(bool vertical = true, bool horizontal = false);

    friend Logger & operator << (Logger & ostr, const RGBSurface & surf);

};
    }
} //namespace RAGE::SDL

#endif
