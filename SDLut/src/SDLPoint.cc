#include "Math/SDLPoint.hh"
#include "SDLConfig.hh"

namespace RAGE
{
    namespace SDL
{
	Point::Point(int nx, int ny) : _rect(new SDL_Rect)
	{
		_rect->x=(Sint16) nx;
		_rect->y=(Sint16) ny;
		_rect->w=0;
		_rect->h=0;
	}

	Point::Point( const Point& p ) : _rect(new SDL_Rect)
	{
		_rect->x=(Sint16) p.getx();
		_rect->y=(Sint16) p.gety();
		_rect->w=0;
		_rect->h=0;
	}

	Point::~Point()
	{
		//always true
		//if (_rect!=NULL)
			delete _rect;
	}

	//usefull to get the SDL rect without any risk of modification
	SDL_Rect Point::get_SDL() const
	{
		return *_rect;
	}
	//usefull to get the SDL rect
	const SDL_Rect * Point::get_pSDL() const
	{
		return _rect;
	}
	
	void Point::setx(int nx )
	{
		_rect->x=(Sint16) nx;
	}
	void Point::sety(int ny )
	{
		_rect->y=(Sint16) ny;
	}

	int Point::getx() const
	{
		return _rect->x;
	}
	int Point::gety() const
	{
		return _rect->y;
	}

	
	void Point::translate(int x ,int y)
	{
		_rect->x=(Sint16)(_rect->x + x);
		_rect->y=(Sint16)(_rect->y + y);
	}


	
	Point Point::operator+(const Point &p) const
	{
		return Point(_rect->x + p.getx(), _rect->y + p.gety());
	}
	Point Point::operator-(const Point &p) const
	{
		return Point(_rect->x - p.getx(), _rect->y - p.gety());
	}
	Point& Point::operator+=(const Point &p)
	{
		_rect->x =(Sint16) (_rect->x + p.getx());
		_rect->y =(Sint16) (_rect->y + p.gety());
		return *this;
	}
	Point& Point::operator-=(const Point &p)
	{
		_rect->x =(Sint16) (_rect->x - p.getx());
		_rect->y =(Sint16) (_rect->y - p.gety());
		return *this;
	}
	
	//TODO : tests operators == , X< X> Y< Y> ( cf old vector operator overloading for example...)
	bool Point::operator==(const Point & p)
	{
		return _rect->x == p.getx() && _rect->y == p.gety();
	}


	
    Point& Point::operator=(const Point& p)
    {
        _rect->x=(Sint16) p.getx();
        _rect->y=(Sint16) p.gety();
        _rect->w=0;
        _rect->h=0;
        return *this;
    }
}
} //namespace RAGE::SDL
