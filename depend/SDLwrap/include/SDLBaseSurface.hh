#ifndef SDLBASESURFACE_HH
#define SDLBASESURFACE_HH

/**
 * \class SDLBaseSurface
 *
 * \ingroup Video
 *
 * \brief Abstract Class to manage Surfaces
 *
 * Abstract Class to handle common behaviour between display surface 
 * and other surface types...
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */
 
#include "SDLConfig.hh"
#include "SDLRect.hh"
#include "SDLPixelFormat.hh"
#include <cassert>

//TODO : make this class pure virtual one (how then?)... and manage creation of _surf with exception
//in the derivating tree
//The goal is to have _surf and this really tied.
class SDLBaseSurface
{
	
protected:
	//TODO : improve wrapping with const SDL_Surface * // or maybe (const?) SDL_Surface & 
	//... look at SDL_video.h to access correctly to SDL_Surface like as for PixelFormat and everything else
	
	//the adress of SDL_Surface struct should never change 
	//SDL_Surface * const _surf;
	//except for resize...
	SDL_Surface * _surf; ///< the actual allocated surface
  
	/// This method return true if the surface is initialized, false otherwise.
	bool initialized() const { return _surf != NULL; }
	//could be useless if exception handle is well coded in the heriting tree
	
	//TODO : delete this, already in SDL_Surface structure
	//To manage locks
	unsigned int locks;
	inline bool locked(void) { return locks > 0; }
	inline bool unlocked(void) { return !locked(); }
	//
	
	///This method return true if all is OK,or if it doesn't need being locked/unlocked.
	///it return false only if this cannot be locked...
	bool lock(void);
	bool unlock(void);
	
	
	Uint32 getpixel(int x, int y);
	void setpixel(int x, int y, Uint32 pixel);
		
	///Conversion Constructor
	explicit SDLBaseSurface(SDL_Surface * s) : _surf(s),locks(0) {} ///< This one should be called only by subclasses
	
	//Copy Constructor
	//SDLBaseSurface( const SDLBaseSurface & s) : _surf(s._surf) {std::cerr << " === WARNING === SDLBaseSurface Copy Called !"<< std::endl;} //this one should never be called
	//must use the one of the subclasses
  
  // 25/08/2005
	/** \brief Copy constructor overload.
	  * Abstracted from RGBSurface to include display as input...
	  * by default this method copy the content in a quickly displayable format (no alpha)
	  */
	SDLBaseSurface(const SDLBaseSurface & s , bool cloning = true, bool toDisplay = true, bool alpha = false) throw (std::logic_error);
	
  
  inline Uint32 getFlags(void) const { return _surf->flags; } ///<usefull accessor for children only
  
public:
	
	/// Virtual Destructor
	virtual ~SDLBaseSurface() {if (_surf!=NULL) SDL_FreeSurface(_surf);}

	///Accessors
	inline int getHeight(void) const { return _surf->h; }
	inline int getWidth(void) const { return _surf->w; }
	inline int getBPP(void) const { return _surf->format->BitsPerPixel; }
	inline bool isSWset(void) const {return SDL_SWSURFACE & _surf->flags;}
	inline bool isHWset(void) const {return SDL_HWSURFACE & _surf->flags;}
	inline bool isHWAccelset(void) const {return SDL_HWACCEL & _surf->flags;}
	inline bool isRLEAccelset(void) const {return SDL_RLEACCEL & _surf->flags;}	
	inline bool isPreAllocset(void) const {return SDL_PREALLOC & _surf->flags;}
	
	///Accessor to pixelFormat
	inline SDLPixelFormat getPixelFormat(void) const {return SDLPixelFormat(_surf->format);}
	
   	//Set the clip rect
   	//Default Reset the clip rect to the full size of the surface
   	inline void setClipRect(void)
   	{
		return setClipRect(SDLRect(getWidth(),getHeight()));
	}
   	void setClipRect(const SDLRect& rect);
   	//get the clip rect
	SDLRect getClipRect(void) const; 

    //save the surface to a BMP file.
    bool saveBMP(std::string filename) const;
    //TODO : the same with other formats
    
    //Fill
   	inline bool fill (const SDLRGBColor& color)
	{
		return fill(SDLPixelFormat(_surf->format).getValueFromRGB(color));
	}
	inline bool fill (const SDLRGBAColor& color)
	{
		return fill(SDLPixelFormat(_surf->format).getValueFromRGBA(color));
	}
	inline bool fill (const SDLPixelColor& color)
	{
		SDLRect dest_rect(getWidth(), getHeight());
		return fill( color, dest_rect );
	}
	inline bool fill (const SDLRGBColor& color, SDLRect dest_rect)
	{
		return fill(SDLPixelFormat(_surf->format).getValueFromRGB(color), dest_rect);
	}
	inline bool fill (const SDLRGBAColor& color, SDLRect dest_rect)
	{
		return fill(SDLPixelFormat(_surf->format).getValueFromRGBA(color), dest_rect);
	}
	bool fill (const SDLPixelColor& color, SDLRect dest_rect);

	//Blit src surface into the current surface
	inline bool blit (const SDLBaseSurface& src, const SDLPoint& dest_pos=SDLPoint())
	{
		SDLRect dest_rect(dest_pos);
		return blit(src, dest_rect);
	}
	inline bool blit (const SDLBaseSurface& src, const SDLPoint& dest_pos, const SDLRect& src_rect)
	{
		SDLRect dest_rect(dest_pos);
		return blit(src, dest_rect, src_rect);
	}
	//Beware ! The final blitting rectangle is saved in dest_rect.
	inline bool blit (const SDLBaseSurface& src, SDLRect& dest_rect)
	{
		SDLRect src_rect(src.getWidth(), src.getHeight());
		return blit(src, dest_rect, src_rect);
	}
	//Blit src into the current surface.
	bool blit (const SDLBaseSurface& src, SDLRect& dest_rect, const SDLRect& src_rect);
    
    virtual void debug(void) const;
   	
};

#endif
