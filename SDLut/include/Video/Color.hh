#ifndef SDL_COLOR_HH
#define SDL_COLOR_HH

#include <iostream>
//#include "SDLPixelFormat.hh"
//#include "SDLVideoInfo.hh"

/*******************************************************************************
 * Handle RGBA Colors.
 * Alpha is ignored and set to 0xff (opaque by default)
 * unused can be used to store alpha component :)
 * 2 classes defined here, since there are 2 set of functions in SDL : RGB ones,
 * and RGBA ones too... perhaps this is a bit useless with Object programming,
 * but optimisation with alpha can be done in SDL though.
 ******************************************************************************/


//declaring SDL type for late binding
struct SDL_Color;
struct SDL_Palette;


namespace SDLut {
    namespace video {


//should be 32 bits color. needs to match pixel format...
typedef unsigned long PixelColor;


/**
 * \class Color
 *
 * \ingroup SDLut_Video
 *
 * \brief This class wraps SDL_Color with alpha
 *
 * \author Alex, XorfacX
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

class Color
{

    friend class SDLPalette;

protected:
    //the address of the SDL_Color struct should never change
    SDL_Color * const ptm_sdl_color;

public:

    //Because NULL has no sense for function using colors, defaut constructor
    // just paint it black :)
    Color(unsigned char r=0, unsigned char g=0, unsigned char b=0, unsigned char a=255);
    Color(const Color & rgbacolor);
    Color& operator=( const Color & rgbacolor );
    virtual ~Color();

    SDL_Color get_SDL() const;

    void setR(unsigned char nr);
    void setG(unsigned char ng);
    void setB(unsigned char nb);
    void setA(unsigned char na);

    unsigned char getR() const;
    unsigned char getG() const;
    unsigned char getB() const;
    unsigned char getA() const;


    friend Color blend(const Color & cover, const Color & cunder);

    Color & blendover(const Color & c);
    Color & blendunder(const Color &c );


    //return a pixel color formatted as RGB(A), in that order, always...
    PixelColor getGLPixelColor() const;

    inline friend std::ostream& operator << (std::ostream& os, const Color& c)
    {
        return os << "RGBAColor : R=" << (int)c.getR() << " G=" << (int)c.getG() << " B=" << (int)c.getB() << " A=" << (int)c.getA() << " " ;
    } //not sure how to derivate that properly... TODO

    bool isSimilarTo(const Color& color) const;
    bool operator==(const Color& color) const;
    bool operator!=(const Color& color) const;

    inline bool hasAlpha() const
    {
        return ( getA() < 255 ) ;
    }
};


}//namespace video
}// namespace SDLut
#endif
