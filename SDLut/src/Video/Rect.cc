#include "Video/Rect.hh"
#include "SDLConfig.hh"

#include <stdexcept>

#ifndef min
#define min( a , b )  ( (a)>(b) )?(b):(a)
#endif

#ifndef max
#define max( a , b ) ((a)>(b))?(a):(b)
#endif
//#define ifpositive( a ) a>0?a:0

namespace SDLut
{
namespace video
{

//usefull to get the SDL rect without any risk of modification
SDL_Rect Rect::get_SDL() const
{
    return *pvm_rect;
}
//usefull to get the SDL rect
SDL_Rect * Rect::get_pSDL() const
{
    return pvm_rect;
}


Rect::Rect()
try :
    pvm_rect(new SDL_Rect)
{
    pvm_rect->x= 0;
    pvm_rect->y= 0;
    pvm_rect->w= pvm_rect->h= 0;
}
catch (std::exception &e)
{
    //TODO : Log it ! Error it !
    delete pvm_rect;
}

Rect::Rect(int nx, int ny , unsigned int nw, unsigned int nh)
try :
    pvm_rect(new SDL_Rect)
{
    pvm_rect->x=(Sint16) nx;
    pvm_rect->y=(Sint16) ny;
    pvm_rect->w=(Uint16) nw;
    pvm_rect->h=(Uint16) nh;
}
catch (std::exception &e)
{
    //TODO : Log it ! Error it !
    delete pvm_rect;
}

//Copy Constructor
Rect::Rect( const Rect& r)
try :
    pvm_rect(new SDL_Rect)
{
    pvm_rect->x=(Sint16) r.getx();
    pvm_rect->y=(Sint16) r.gety();
    pvm_rect->w=(Uint16) r.getw();
    pvm_rect->h=(Uint16) r.geth();
}
catch (std::exception &e )
{
    //TODO : Log it ! error it !
    delete pvm_rect;
}

Rect::~Rect()
{
    delete pvm_rect;
}


void Rect::resetx(int nx )
{
    pvm_rect->x=(Sint16) nx;
}
void Rect::resety(int ny )
{
    pvm_rect->y=(Sint16) ny;
}

int Rect::getx() const
{
    return pvm_rect->x;
}
int Rect::gety() const
{
    return pvm_rect->y;
}


void Rect::resetw(unsigned int nw )
{
    pvm_rect->w=(Uint16) nw;
}
void Rect::reseth(unsigned int nh )
{
    pvm_rect->h=(Uint16) nh;
}

unsigned int Rect::getw() const
{
    return pvm_rect->w;
}
unsigned int Rect::geth() const
{
    return pvm_rect->h;
}

//scalar operations
//dont use -1 scalar right now (later for reverse maybe ??)
Rect& Rect::operator*=(unsigned int s)
{
    pvm_rect->w = (Uint16) (pvm_rect->w * s);
    pvm_rect->h = (Uint16) (pvm_rect->h * s);
    return *this;
}

Rect& Rect::operator/=(unsigned int s)
{
    pvm_rect->w = (Uint16) (pvm_rect->w / s);
    pvm_rect->h = (Uint16) (pvm_rect->h / s);
    return *this;
}

Rect operator*(unsigned int s, const Rect& u)
{
    return Rect ( u.pvm_rect->x, u.pvm_rect->y, u.pvm_rect->w * s, u.pvm_rect->h * s );
}

Rect operator*(const Rect& u,unsigned int s)
{
    return Rect ( u.pvm_rect->x, u.pvm_rect->y, u.pvm_rect->w * s, u.pvm_rect->h * s );
}

Rect operator/(const Rect& u,unsigned int s)
{
    return Rect ( u.pvm_rect->x, u.pvm_rect->y, u.pvm_rect->w / s, u.pvm_rect->h / s );
}


Rect& Rect::operator=(const Rect& r)
{
    pvm_rect->x=(Sint16) r.getx();
    pvm_rect->y=(Sint16) r.gety();
    pvm_rect->w=(Uint16) r.getw();
    pvm_rect->h=(Uint16) r.geth();
    return *this;
}


void Rect::moveto(int nx, int ny)
{
    pvm_rect->x=(Sint16)(nx);
    pvm_rect->y=(Sint16)(ny);
}


void Rect::translate(int dx, int dy)
{
    pvm_rect->x+=(Sint16)(dx);
    pvm_rect->y+=(Sint16)(dy);
}

bool Rect::operator==(const Rect & r)
{
    return pvm_rect->x == r.getx() && pvm_rect->y == r.gety() && pvm_rect->w == r.getw() && pvm_rect->h == r.geth();
}


bool Rect::operator!=(const Rect& r)
{
    return (pvm_rect->x != r.getx()) || (pvm_rect->y != r.gety()) || (pvm_rect->w != (Uint16)r.getw()) || (pvm_rect->h != (Uint16)r.geth());
}


//this computes the intersection of 2 rects, that is the greatest rect contained in both of them
Rect Rect::inf(const Rect & r)
{
    //getting the lower right corner
    Rect result( max (getx(),r.getx()), max (gety(),r.gety()),0,0 );

    //testing for actual intersection
    if ( (result.getx() == getx() && result.getx() < ( r.getx() + static_cast<int>(r.getw()) ))
            || (result.getx() == r.getx() && result.getx() < ( getx() + static_cast<int>(getw()) )) //Xintersection
       )
    {
        if ( (result.gety() == gety() && result.gety() < ( r.gety() + static_cast<int>(r.geth()) ))
                || (result.gety() == r.gety() && result.gety() < ( gety() + static_cast<int>(geth()) )) //Yintersection
           )
        {
            //getting the size of it
            int cornerx = min (getx()+getw(),r.getx()+r.getw())
                          ;
            int cornery = min (gety()+geth(),r.gety()+r.geth());
            result.reseth(cornery - result.gety());
            result.resetw(cornerx - result.getx());
        }
        else
        {
            result.resetw(0);
            result.reseth(0);
        }
    }
    return result;
}

//this computes the smallest rect containing both of them
Rect Rect::sup(const Rect & r)
{
    Rect result( min (getx(),r.getx()) , min (gety(),r.gety()),0,0 );

    //getting the size of it
    result.resetw( max (getx()+getw(),r.getx()+r.getw()) - result.getx() );
    result.reseth( max (gety()+geth(),r.gety()+r.geth()) - result.gety() );

    return result;
}


}
} //namespace SDLut::SDL
