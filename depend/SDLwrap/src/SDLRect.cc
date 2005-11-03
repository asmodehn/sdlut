#include "SDLRect.hh"
#define min( a , b ) a>b?b:a
#define max( a , b ) a>b?a:b
#define ifpositive( a ) a>0?a:0

namespace SDL
{

    //this computes the intersection of 2 rects, that if the greatest rect contained in both of them
    Rect Rect::inf(const Rect & r)
    {
        Rect result;

        //just doesnt work... TODO
        result.setx( max (getx(),r.getx()) );
        result.sety( max (gety(),r.gety()) );
        result.setw(ifpositive(min (getx()+getw(),r.getx()+r.getw()) - result.getx()));
        result.seth(ifpositive(min (gety()+geth(),r.gety()+r.geth()) - result.gety()));

        //if ( result.getw()!=0 && result.geth()!=0 )


        return result;
    }

    //this computes the smallest rect containing both of them
    Rect Rect::sup(const Rect & r)
    {
        Rect result;

        //just doesnt work... TODO
        result.setx( min (getx(),r.getx()) );
        result.sety( min (gety(),r.gety()) );
        result.setw( max (getx()+getw(),r.getx()+r.getw()) - result.getx() );
        result.seth( max (gety()+geth(),r.gety()+r.geth()) - result.gety() );
        return result;
    }

} //namespace SDL
