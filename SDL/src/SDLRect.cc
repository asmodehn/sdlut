#include "SDLRect.hh"
#define min( a , b )  ( (a)>(b) )?(b):(a)
#define max( a , b ) ((a)>(b))?(a):(b)
//#define ifpositive( a ) a>0?a:0

namespace RAGE
{
    namespace SDL
{

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
          int cornerx = min (getx()+getw(),r.getx()+r.getw());
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
