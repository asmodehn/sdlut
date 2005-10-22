#ifndef SDL_RECT_HH
#define SDL_RECT_HH


/**
 * \class Rect
 *
 * \ingroup Video
 *
 * \brief This class is a Rectangle
 *
 * This class wraps SDL_Rect as a Rectangle (width and height are always used, by opposition to SDLPoint)
 *
 * \note The origin point can sometimes be ignored
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

#include "SDLConfig.hh"
#include "SDLPoint.hh"

namespace SDL {

class Rect : public Point
{
	//Because some functions of SDLBaseSurface needs access to SDL_Rect directly
	//And because SDLBaseSurface includes SDLRect.hh, we cannot specify the functions
	//here.
	friend class BaseSurface;
	friend class DisplaySurface;
	friend class Overlay;

protected :
	
public:

	//also used to convert point for main methods use...
	Rect(const Point& p , unsigned int nw=0, unsigned int nh=0) : Point(p.getx(),p.gety())
	{
		_rect->w=nw;
		_rect->h=nh;
	}

	Rect(int x, int y , unsigned int nw, unsigned int nh) : Point(x,y)
	{
		_rect->w=nw;
		_rect->h=nh;
	}

	//2 parameter define only a rectangular zone
	Rect( unsigned int nw=0, unsigned int nh=0) : Point(0,0)
	{
		_rect->w=nw;
		_rect->h=nh;
	}
	
	//Copy Constructor
	Rect( const Rect& r) : Point(r.getx(),r.gety())
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
	Rect inf(const Rect & r);
	//Return the shorter Rect containing the both Rects
	Rect sup(const Rect & r);

  //scalar operations
  inline Rect& operator*=(int s)
  { _rect->w *= s; _rect->h *= s; return *this; }

  inline Rect& operator/=(int s)
  { _rect->w /= s; _rect->h /= s;	return *this; }

  inline friend Rect operator*(int s, const Rect& u)
  {	return Rect ( u._rect->w * s, u._rect->h * s ); }

	inline friend Rect operator*(const Rect& u, int s)
  {	return Rect ( u._rect->w * s, u._rect->h * s ); }

  inline friend Rect operator/(const Rect& u, int s)
  { return Rect ( u._rect->w / s, u._rect->h / s ); }
	
	//TODO growCenter, growCorner, rotate90, rotate180, rotate270
	
	//TODO tests operators :  != == <= < >= > (about size of the area only)
	
	inline friend std::ostream& operator << (std::ostream& os, const Rect& r)
		{ return os << "Rect : ( " << r.getx() << ", " << r.gety() << ") W= " << r.getw() << " H= " << r.geth(); } 
};

} //namespace SDL

#endif
