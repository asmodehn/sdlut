#include "SDLRect.hh"
#define min( a , b ) a>b?b:a
#define max( a , b ) a>b?a:b
#define ifpositive( a ) a>0?a:0

SDLRect SDLRect::inf(const SDLRect & r)
{
	SDLRect result;
	result.setx( max (getx(),r.getx()) );
	result.sety( max (gety(),r.gety()) );
	result.setw(ifpositive(min (getx()+getw(),r.getx()+r.getw()) - result.getx()));
	result.seth(ifpositive(min (gety()+geth(),r.gety()+r.geth()) - result.gety()));
	return result;
}

SDLRect SDLRect::sup(const SDLRect & r)
{
	SDLRect result;
	result.setx( min (getx(),r.getx()) );
	result.sety( min (gety(),r.gety()) );
	result.setw( max (getx()+getw(),r.getx()+r.getw()) - result.getx() );
	result.seth( max (gety()+geth(),r.gety()+r.geth()) - result.gety() );
	return result;
}
