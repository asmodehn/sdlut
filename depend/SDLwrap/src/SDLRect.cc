#include "SDLRect.hh"
#define min( a , b ) a>b?b:a
#define max( a , b ) a>b?a:b
#define ifpositive( a ) a>0?a:0

namespace SDL
{

    Rect Rect::inf(const Rect & r)
    {
        Rect result;
        result.setx( max (getx(),r.getx()) );
        result.sety( max (gety(),r.gety()) );
        result.setw(ifpositive(min (getx()+getw(),r.getx()+r.getw()) - result.getx()));
        result.seth(ifpositive(min (gety()+geth(),r.gety()+r.geth()) - result.gety()));
        return result;
    }
    
    Rect Rect::sup(const Rect & r)
    {
        Rect result;
        result.setx( min (getx(),r.getx()) );
        result.sety( min (gety(),r.gety()) );
        result.setw( max (getx()+getw(),r.getx()+r.getw()) - result.getx() );
        result.seth( max (gety()+geth(),r.gety()+r.geth()) - result.gety() );
        return result;
    }
    
} //namespace SDL
