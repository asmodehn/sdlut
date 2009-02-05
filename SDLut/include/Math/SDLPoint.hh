#ifndef SDL_POINT_HH
#define SDL_POINT_HH

#include <iostream>
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

//declaring SDL_type for late binding
struct SDL_Rect;

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
			Point(int nx=0, int ny=0);

			Point( const Point& p );

			virtual ~Point();

				//Accessors

			void setx(int nx );
			void sety(int ny );
			int getx() const;
			int gety() const;

			//usefull to get the SDL rect without any risk of modification
			SDL_Rect get_SDL() const;
			//usefull to get the SDL rect
			const SDL_Rect * get_pSDL() const;

				//Methods

			void translate(int x ,int y);

				Point& operator=(const Point&);

				//and others like + - etc...
			Point operator+(const Point &p) const;
			Point operator-(const Point &p) const;
			Point& operator+=(const Point &p);
			Point& operator-=(const Point &p);
		    
		//TODO : tests operators == , X< X> Y< Y> ( cf old vector operator overloading for example...)
			bool operator==(const Point & p);

			bool operator!=(const Point & p);

            inline friend std::ostream& operator << (std::ostream& os, const Point& p)
            {
                return os << "Point : ( " << p.getx() << ", " << p.gety() << " )";
            }

        };
    }
} //namespace RAGE::SDL

#endif // SDL_POINT_HH
