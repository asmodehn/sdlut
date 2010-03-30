#ifndef SDL_RECT_HH
#define SDL_RECT_HH


#include <iostream>

//further definition
struct SDL_Rect;

namespace SDLut
{
namespace video
{

namespace internal
{
class BaseSurface;
}



/**
 * \class Rect
 *
 * \ingroup SDLut_Video
 *
 * \brief This class is a Rectangle
 *
 * This class wraps SDL_Rect as a Rectangle. Width and Height are 0 if it actually represent a point
 *
 * \note The origin point can sometimes be ignored
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

class Rect
{
    //Because some functions of SDLBaseSurface needs access to SDL_Rect directly
    //And because SDLBaseSurface includes SDLRect.hh, we cannot specify the functions
    //here.
    friend class internal::BaseSurface;
    friend class VideoSurface;
    friend class Overlay;

private:
    //the address of the SDL_Rect struct should never change...
    SDL_Rect * const pvm_rect;


protected :

    //usefull to get the SDL rect without any risk of modification
    SDL_Rect get_SDL() const;
    //usefull to get the SDL rect
    SDL_Rect * get_pSDL() const;


public:

    //CAreful with default values.
    //size and position tends to be confused

    //Default Constructor ( needed for conatiners )
    //construct rect(0,0,0,0)
    Rect();
    //Handy Constructor
    Rect(int x, int y, unsigned int nw, unsigned int nh);
    ///TOTHINK ABOUT : One constructor with 0,0,1,1 as default. pixelsized rect.



    //Copy Constructor
    Rect( const Rect& r);

    //Destructor
    ~Rect();

    Rect& operator=(const Rect& p);


    void resetx(int nx = 0);
    void resety(int ny = 0);
    void resetw(unsigned int nw = 0);
    void reseth(unsigned int nh = 0);

    int getx() const;
    int gety() const;
    unsigned int getw() const;
    unsigned int geth() const;

//Methods
    //Return the bigger Rect contained in both Rects
    Rect inf(const Rect & r);
    //Return the shorter Rect containing the both Rects
    Rect sup(const Rect & r);

    //move from (x,y) to (nx,ny) wo impacting w & h
    void moveto(int nx, int ny);
    //move from (x,y) to (x+dx,y+dy) wo impacting w & h
    void translate(int dx, int dy);

//scalar operations
    Rect& operator*=(unsigned int s);
    Rect& operator/=(unsigned int s);
    friend Rect operator*(unsigned int s, const Rect& u);
    friend Rect operator*(const Rect& u, unsigned int s);
    friend Rect operator/(const Rect& u, unsigned int s);


//TODO growCenter, growCorner, rotate90, rotate180, rotate270

//TODO tests operators :  != == <= < >= > (about size of the area only)
    bool operator==(const Rect & r);

    bool operator!=(const Rect& r);


    inline friend std::ostream& operator << (std::ostream& os, const Rect& r)
    {
        return os << std::dec << "Rect : ( " << r.getx() << ", " << r.gety() << ") W= " << r.getw() << " H= " << r.geth();
    }
};

}
} //namespace SDLut::SDL

#endif
