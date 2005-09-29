#ifndef SDLRECT_HH
#define SDLRECT_HH

/******************************************************************************
 * Handle a Rect
 * A Rect is a SDLRect where width and Height are always used( by opposition to
 * Point) but the origin point can be sometimes ignored...
 *****************************************************************************/

#include "SDLConfig.hh"
#include "SDLPoint.hh"

class SDLRect : public SDLPoint
{
	//Because some functions of SDLBaseSurface needs access to SDL_Rect directly
	//And because SDLBaseSurface includes SDLRect.hh, we cannot specify the functions
	//here.
	friend class SDLBaseSurface;
	friend class SDLDisplaySurface;
	friend class SDLOverlay;

protected :
	
public:

	//also used to convert point for main methods use...
	SDLRect(const SDLPoint& p , unsigned int nw=0, unsigned int nh=0) : SDLPoint(p.getx(),p.gety())
	{
		_rect->w=nw;
		_rect->h=nh;
	}

	SDLRect(int x, int y , unsigned int nw, unsigned int nh) : SDLPoint(x,y)
	{
		_rect->w=nw;
		_rect->h=nh;
	}

	//2 parameter define only a rectangular zone
	SDLRect( unsigned int nw=0, unsigned int nh=0) : SDLPoint(0,0)
	{
		_rect->w=nw;
		_rect->h=nh;
	}
	
	//Copy Constructor
	SDLRect( const SDLRect& r) : SDLPoint(r.getx(),r.gety())
	{
		_rect->w=r.getw();
		_rect->h=r.geth();
	}
	
	void setw(unsigned int nw ) { _rect->w=nw; }
	void seth(unsigned int nh ) { _rect->h=nh; }

	unsigned int getw() const { return _rect->w; }
	unsigned int geth() const { return _rect->h; }
		
	//Methods
	//
	//Return the bigger Rect contained in both Rects
	SDLRect inf(const SDLRect & r);
	//Return the shorter Rect containing the both Rects
	SDLRect sup(const SDLRect & r);
	
	//TODO growCenter, growCorner, rotate90, rotate180, rotate270
	
	//TODO tests operators :  != == <= < >= > (about size of the area only)
	
	inline friend std::ostream& operator << (std::ostream& os, const SDLRect& r)
		{ return os << "Rect : ( " << r.getx() << ", " << r.gety() << ") W= " << r.getw() << " H= " << r.geth(); } 
};

#endif
