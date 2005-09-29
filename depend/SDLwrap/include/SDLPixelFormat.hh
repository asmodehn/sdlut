#ifndef SDLPIXELFORMAT_HH
#define SDLPIXELFORMAT_HH

#include "SDLConfig.hh"
#include "SDLColor.hh"

//to store pixel colors
typedef Uint32 SDLPixelColor;

class SDLPixelFormat
{
	//because SDLPixelColor needs to access actual SDL_PixelFormat
	friend class SDLVideoInfo;
	friend class SDLSurfaceFactory;
	friend class SDLRGBSurface;
	friend class SDLBaseSurface;
	
	bool pointerCopy;
	
protected:
	//read-only access
	//the address of the SDL_PixelFormat struct should never change
	const SDL_PixelFormat* const _pformat;
	
	
	//Copy Constructor from SDL_PixelFormat
	//This handle explicit casts
	explicit SDLPixelFormat(const SDL_PixelFormat* pf) : _pformat(pf)
	{
		pointerCopy = true;
	}
	//DEVELOPER BEWARE ! Don't free the original pixelformat.
	//The user should never be able to free the original pixelformat
	//nor to use SDL directly.
	
public:
	
	//default Constructor
	//SDLPixelFormat(void) { _pformat= new SDL_PixelFormat; }
	//TODO : To avoid using uninitialized PixelFormat , put default constructor on protected
	//Really Usefull ??
		
	~SDLPixelFormat(void) { if (!pointerCopy) delete _pformat; }
	
	int getBitsPerPixel() const { return _pformat->BitsPerPixel; }
	int getBytesPerPixel() const { return _pformat->BytesPerPixel; }
	int getRshift() const { return _pformat->Rshift; }
	int getGshift() const { return _pformat->Gshift; }
	int getBshift() const { return _pformat->Bshift; }
	int getAshift() const { return _pformat->Ashift; }
	
	int getRloss() const { return _pformat->Rloss; }
	int getGloss() const { return _pformat->Gloss; }
	int getBloss() const { return _pformat->Bloss; }
	int getAloss() const { return _pformat->Aloss; }
	
	//BEWARE ! sometimes this has no sense, because only the palette is set...
	//TODO : Handle this...
	unsigned long getRmask() const { return _pformat->Rmask; }
	unsigned long getGmask() const { return _pformat->Gmask; }
	unsigned long getBmask() const { return _pformat->Bmask; }
	unsigned long getAmask() const { return _pformat->Amask; }
	
	SDLPixelColor getColorKey() const { return _pformat->colorkey; }
	int getAlpha() const { return _pformat->alpha; }
	SDLPalette getPalette() const { return SDLPalette(_pformat->palette); }
	
	//display all detected informations about pixelformat
	void debug(void) const;
	
	//methods for Color conversion : 
	SDLPixelColor getValueFromRGB(const SDLRGBColor& val) const ;
	SDLPixelColor getValueFromRGBA(const SDLRGBAColor& val) const ;
	SDLRGBColor getRGBValue(const SDLPixelColor& color) const ;
	SDLRGBAColor getRGBAValue(const SDLPixelColor& color) const ;

};

#endif
