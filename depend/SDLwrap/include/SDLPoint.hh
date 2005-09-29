#ifndef SDLPOINT_HH
#define SDLPOINT_HH

#include "SDLConfig.hh"

/******************************************************************************
 * Handle a Point
 * A Point is a SDL_Rect where width and height are never used.
 *****************************************************************************/

class SDLPoint
{
protected:
	//the address of the SDL_Rect struct should never change...
	SDL_Rect * const _rect;
	
public:

	//2 parameters define only a point.
	SDLPoint(int nx=0, int ny=0) : _rect(new SDL_Rect)
	{
		_rect->x=nx;
		_rect->y=ny;
		_rect->w=0;
		_rect->h=0;
	}
	
	SDLPoint( const SDLPoint& p ) : _rect(new SDL_Rect)
	{
		_rect->x=p.getx();
		_rect->y=p.gety();
		_rect->w=0;
		_rect->h=0;
	}
	
	~SDLPoint() {if (_rect!=NULL) delete _rect; };

	//Accessors

	void setx(int nx ) { _rect->x=nx; }
	void sety(int ny ) { _rect->y=ny; }

	int getx() const { return _rect->x; }
	int gety() const { return _rect->y; }


	//Methods

	void translate(int x ,int y) { _rect->x+=x; _rect->y+=y; };
	
	//TODO : tests operators == , X< X> Y< Y> ( cf old vector operator overloading...)
	
	//TODO : assignement operators if default doesnt work... (= copy)
	SDLPoint& operator=(const SDLPoint&);
	
	//and others like + - etc...
	inline SDLPoint operator+(const SDLPoint &p) const
		{ return SDLPoint(_rect->x + p.getx(), _rect->y + p.gety()); }
	inline SDLPoint operator-(const SDLPoint &p) const
		{ return SDLPoint(_rect->x - p.getx(), _rect->y - p.gety()); }
	inline SDLPoint& operator+=(const SDLPoint &p)
		{ _rect->x += p.getx(); _rect->y += p.gety(); return *this; }
	inline SDLPoint& operator-=(const SDLPoint &p)
		{ _rect->x -= p.getx(); _rect->y -= p.gety(); return *this; }
	
	inline friend std::ostream& operator << (std::ostream& os, const SDLPoint& p)
		{ return os << "Point : ( " << p.getx() << ", " << p.gety() << " )"; } 
	
};

#endif // SDLPOINT_HH
