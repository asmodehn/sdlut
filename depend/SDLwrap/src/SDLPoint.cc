#include "SDLPoint.hh"
SDLPoint& SDLPoint::operator=(const SDLPoint& p)
{
	_rect->x=p.getx();
	_rect->y=p.gety();
	_rect->w=0;
	_rect->h=0;
	return *this;
}
