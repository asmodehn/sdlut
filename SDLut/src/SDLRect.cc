#include "Math/SDLRect.hh"
#include "SDLConfig.hh"
#define min( a , b )  ( (a)>(b) )?(b):(a)
#define max( a , b ) ((a)>(b))?(a):(b)
//#define ifpositive( a ) a>0?a:0

namespace RAGE
{
    namespace SDL
    {

	    //also used to convert point for main methods use...
	    Rect::Rect(const Point& p , unsigned int nw, unsigned int nh) : Point(p.getx(),p.gety())
	    {
		    _rect->w=(Uint16) nw;
		    _rect->h=(Uint16) nh;
	    }

	    Rect::Rect(int x, int y , unsigned int nw, unsigned int nh) : Point(x,y)
	    {
		    _rect->w=(Uint16) nw;
		    _rect->h=(Uint16) nh;
	    }

	//2 parameter define only a rectangular zone
	    Rect::Rect( unsigned int nw, unsigned int nh) : Point(0,0)
	    {
		    _rect->w=(Uint16) nw;
		    _rect->h=(Uint16) nh;
	    }

	//Copy Constructor
	    Rect::Rect( const Rect& r) : Point(r.getx(),r.gety())
	    {
		    _rect->w=(Uint16) r.getw();
		    _rect->h=(Uint16) r.geth();
	    }

	    Rect::~Rect()
	    {
	    }
	    
	    void Rect::setw(unsigned int nw )
	    {
		    _rect->w=(Uint16) nw;
	    }
	    void Rect::seth(unsigned int nh )
	    {
		    _rect->h=(Uint16) nh;
	    }

	    unsigned int Rect::getw() const
	    {
		    return _rect->w;
	    }
	    unsigned int Rect::geth() const
	    {
		    return _rect->h;
	    }

	    //scalar operations
	    //dont use -1 scalar right now (later for reverse maybe ??
	    Rect& Rect::operator*=(unsigned int s)
	    {
		    _rect->w = (Uint16) (_rect->w * s);
		    _rect->h = (Uint16) (_rect->h * s);
		    return *this;
	    }

	    Rect& Rect::operator/=(unsigned int s)
	    {
		    _rect->w = (Uint16) (_rect->w / s);
		    _rect->h = (Uint16) (_rect->h / s);
		    return *this;
	    }

	     Rect operator*(unsigned int s, const Rect& u)
	    {
		    return Rect ( u._rect->w * s, u._rect->h * s );
	    }

	     Rect operator*(const Rect& u,unsigned int s)
	    {
		    return Rect ( u._rect->w * s, u._rect->h * s );
	    }

		Rect operator/(const Rect& u,unsigned int s)
	    {
		    return Rect ( u._rect->w / s, u._rect->h / s );
	    }

	    
        Rect& Rect::operator=(const Rect& r)
        {
            Point::operator=(r);
            _rect->w=(Uint16)r.getw();
            _rect->h=(Uint16)r.geth();
            return *this;
        }

	bool Rect::operator==(const Rect & r)
	{
		return _rect->w == r.getw() && _rect->h == r.geth();
	}
	
        //this computes the intersection of 2 rects, that if the greatest rect contained in both of them
        Rect Rect::inf(const Rect & r)
        {
            Rect result;

            //getting the lower right corner
            result.setx( max (getx(),r.getx()) );
            result.sety( max (gety(),r.gety()) );

            //testing for actual intersection
            if ( (result.getx() == getx() && result.getx() < ( r.getx() + static_cast<int>(r.getw()) ))
                    || (result.getx() == r.getx() && result.getx() < ( getx() + static_cast<int>(getw()) )) //Xintersection
               )
                if ( (result.gety() == gety() && result.gety() < ( r.gety() + static_cast<int>(r.geth()) ))
                        || (result.gety() == r.gety() && result.gety() < ( gety() + static_cast<int>(geth()) )) //Yintersection
                   )
                {
                    //getting the size of it
                    int cornerx = min (getx()+getw(),r.getx()+r.getw())
                                  ;
                    int cornery = min (gety()+geth(),r.gety()+r.geth());
                    result.seth(cornery - result.gety());
                    result.setw(cornerx - result.getx());
                }
                else
                {
                    result.setw(0);
                    result.seth(0);
                }

            return result;
        }

        //this computes the smallest rect containing both of them
        Rect Rect::sup(const Rect & r)
        {
            Rect result;

            //getting the upper left corner
            result.setx( min (getx(),r.getx()) );
            result.sety( min (gety(),r.gety()) );

            //getting the size of it
            result.setw( max (getx()+getw(),r.getx()+r.getw()) - result.getx() );
            result.seth( max (gety()+geth(),r.gety()+r.geth()) - result.gety() );

            return result;
        }
    }
} //namespace RAGE::SDL
