#include "SDLPoint.hh"

namespace SDL
{

    Point& Point::operator=(const Point& p)
    {
        _rect->x=p.getx();
        _rect->y=p.gety();
        _rect->w=0;
        _rect->h=0;
        return *this;
    }
    
} //namespace SDL
