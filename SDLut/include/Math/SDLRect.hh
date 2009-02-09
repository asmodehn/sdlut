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

#include "SDLPoint.hh"

namespace RAGE
{
    namespace SDL {

class Rect : public Point
{
	//Because some functions of SDLBaseSurface needs access to SDL_Rect directly
	//And because SDLBaseSurface includes SDLRect.hh, we cannot specify the functions
	//here.
	friend class BaseSurface;
	friend class VideoSurface;
	friend class Overlay;

protected :

public:

	//also used to convert point for main methods use...
	Rect(const Point& p , unsigned int nw=0, unsigned int nh=0);
	Rect(int x, int y , unsigned int nw, unsigned int nh);

	//2 parameter define only a rectangular zone
	Rect( unsigned int nw=0, unsigned int nh=0);

	//Copy Constructor
	Rect( const Rect& r);

	//Destructor
	~Rect();
	
    Rect& operator=(const Rect& p);

    void setw(unsigned int nw );
    void seth(unsigned int nh );

    unsigned int getw() const;
    unsigned int geth() const;

	//Methods
	//
	//Return the bigger Rect contained in both Rects
	Rect inf(const Rect & r);
	//Return the shorter Rect containing the both Rects
	Rect sup(const Rect & r);

  //scalar operations
		Rect& operator*=(unsigned int s);
		Rect& operator/=(unsigned int s);
		friend Rect operator*(unsigned int s, const Rect& u);
		friend Rect operator*(const Rect& u, unsigned int s);
		friend Rect operator/(const Rect& u, unsigned int s);
		
	//TODO growCenter, growCorner, rotate90, rotate180, rotate270

	//TODO tests operators :  != == <= < >= > (about size of the area only)
		bool operator==(const Rect & r);

		bool operator!=(const Rect& r);


	inline friend std::ostream& operator << (std::ostream& os, const Rect& r)
		{ return os << "Rect : ( " << r.getx() << ", " << r.gety() << ") W= " << r.getw() << " H= " << r.geth(); }
};
    }
} //namespace RAGE::SDL

#endif
