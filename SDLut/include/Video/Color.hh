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
 * \class SDLColor
 *
 * \ingroup Video
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

    //return a pixel color formatted as RGB(A), in that order, always...
    PixelColor getGLPixelColor() const;

    inline friend std::ostream& operator << (std::ostream& os, const Color& c)
    {
        return os << "RGBAColor : R=" << (int)c.getR() << " G=" << (int)c.getG() << " B=" << (int)c.getB() << " A=" << (int)c.getA() << " " ;
    } //not sure how to derivate that properly... TODO

    bool operator==(const Color& color) const;
    bool operator!=(const Color& color) const;

    inline bool hasAlpha() const
    {
        return ( getA() < 255 ) ;
    }
};

/**
 * \class Palette
 *
 * \ingroup Video
 *
 * \brief This class wraps SDL_Palette
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

namespace internal { class PixelFormat;}

//read-only access
class Palette
{
    friend class internal::PixelFormat;

    bool pointerCopy;
protected:
    //the adress of the SLD_Palette struct should never change
    //read only_access
    const SDL_Palette * const ptm_sdl_palette;
    // protected to prevent manual creation of palette
    //maybe completely useless...
    // default : one black color
    /*Palette(int ncolors = 1) : _palette(new SDL_Palette)
    {
    	_palette->ncolors = ncolors;
    	_palette->colors = (new Color[ncolors])->_color;
    	pointerCopy = false;
    }*/
    //idem for the copy contructor
    /*Palette(const Palette & p ) : _palette(new SDL_Palette)
    {
    	_palette->ncolors = p.getNColors();
    	for (int i=0; i<_palette->ncolors ; i++)
    		_palette->colors[i] = p._palette->colors[i];
    	pointerCopy = false;
    }*/
    //to handle explicit cast from SDL
    //beware : store only a pointer...
    //so the original should not be destroyed !
    explicit Palette(const SDL_Palette* palette);

public:

    ~Palette(void);

    int getNColors(void) const;
    Color getColors(int index) const;

};


}//namespace video
}// namespace SDLut
#endif
