#ifndef SDL_POINT_HH
#define SDL_POINT_HH

#include "SDLConfig.hh"

/**
 * \class Point
 *
 * \ingroup Video
 *
 * \brief This class is a Point
 *
 * This class wraps SDL_Rect but width and height are never used
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

/******************************************************************************
 * Handle a Point
 * A Point is a SDL_Rect where width and height are never used.
 *****************************************************************************/

namespace RAGE
{
    namespace SDL
    {

        class Point
        {
        protected:
            //the address of the SDL_Rect struct should never change...
            SDL_Rect * const _rect;

        public:

            //2 parameters define only a point.
            Point(int nx=0, int ny=0) : _rect(new SDL_Rect)
            {
                _rect->x=nx;
                _rect->y=ny;
                _rect->w=0;
                _rect->h=0;
            }

            Point( const Point& p ) : _rect(new SDL_Rect)
            {
                _rect->x=p.getx();
                _rect->y=p.gety();
                _rect->w=0;
                _rect->h=0;
            }

            ~Point()
            {
                if (_rect!=NULL)
                    delete _rect;
            };

            //Accessors

            void setx(int nx )
            {
                _rect->x=nx;
            }
            void sety(int ny )
            {
                _rect->y=ny;
            }

            int getx() const
            {
                return _rect->x;
            }
            int gety() const
            {
                return _rect->y;
            }


            //Methods

            void translate(int x ,int y)
            {
                _rect->x+=x;
                _rect->y+=y;
            };

            //TODO : tests operators == , X< X> Y< Y> ( cf old vector operator overloading...)

            //TODO : assignement operators if default doesnt work... (= copy)
            Point& operator=(const Point&);

            //and others like + - etc...
            inline Point operator+(const Point &p) const
            {
                return Point(_rect->x + p.getx(), _rect->y + p.gety());
            }
            inline Point operator-(const Point &p) const
            {
                return Point(_rect->x - p.getx(), _rect->y - p.gety());
            }
            inline Point& operator+=(const Point &p)
            {
                _rect->x += p.getx();
                _rect->y += p.gety();
                return *this;
            }
            inline Point& operator-=(const Point &p)
            {
                _rect->x -= p.getx();
                _rect->y -= p.gety();
                return *this;
            }

            inline friend std::ostream& operator << (std::ostream& os, const Point& p)
            {
                return os << "Point : ( " << p.getx() << ", " << p.gety() << " )";
            }

        };
    }
} //namespace RAGE::SDL

#endif // SDL_POINT_HH
