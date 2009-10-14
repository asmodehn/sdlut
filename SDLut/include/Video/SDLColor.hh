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


/**
 * \class SDLRGBColor
 *
 * \ingroup Video
 *
 * \brief This class wraps SDL_Color (without alpha)
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */


//declaring SDL type for late binding
struct SDL_Color;
struct SDL_Palette;

namespace RAGE
{
namespace SDL
{

//to store pixel colors
typedef unsigned long PixelColor;

//TODO : Color constructor with string ("black", "yellow", "grey", etc. )
//TODO : Color operator, like + - = etc. (like a vector)
class RGBColor
{
    friend class SDLPalette;

protected:
    //the address of the SDL_Color struct should never change
    SDL_Color * const _color;

public:

    //Because NULL has no sense for function using colors, defaut constructor
    // just paint it black :)
    RGBColor(unsigned char r=0, unsigned char g=0, unsigned char b=0);
    RGBColor(const RGBColor & rgbcolor);
    RGBColor& operator=( const RGBColor & rgbcolor);
    virtual ~RGBColor();

    SDL_Color get_SDL() const;

    void setR(unsigned char nr);
    void setG(unsigned char ng);
    void setB(unsigned char nb);

    unsigned char getR() const;
    unsigned char getG() const;
    unsigned char getB() const;
    //TMP needed for OpenGL simple color handling
    // By the way WHY do we have 2 classes for color ??
    // Investigation needed
    unsigned char getA() const;

    bool operator==(const RGBColor& color) const;
    bool operator!=(const RGBColor& color) const;

    inline friend std::ostream& operator << (std::ostream& os, const RGBColor& c)
    {
        return os << "RGBColor : R=" << (int)c.getR() << " G=" << (int)c.getG() << " B=" << (int)c.getB() << " ";
    }

    inline virtual bool hasAlpha() const
    {
        return false;
    }

    //return a pixel color formatted as RGB(A), in that order, always...
    PixelColor getGLPixelColor() const;

};

//TODO : Why do we have two classes for color ? it would be much imple to have just one...
//We need to investigate to see if we really need two


/**
 * \class SDLRGBAColor (alias SDLColor)
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

class RGBAColor : public RGBColor
{
    //	explicit SDLRGBAColor(SDL_Color * color) : SDLRGBColor(color) {}

public:
    RGBAColor(unsigned char r=0, unsigned char g=0, unsigned char b=0, unsigned char a=255);
    RGBAColor(const RGBColor& color, unsigned char a=255);
    RGBAColor(const RGBAColor & rgbacolor);
    RGBAColor& operator=( const RGBAColor & rgbacolor );
    virtual ~RGBAColor();

    void setA(unsigned char na);

    unsigned char getA(void) const;

    inline friend std::ostream& operator << (std::ostream& os, const RGBAColor& c)
    {
        return os << "RGBAColor : R=" << (int)c.getR() << " G=" << (int)c.getG() << " B=" << (int)c.getB() << " A=" << (int)c.getA() << " " ;
    } //not sure how to derivate that properly... TODO

    bool operator==(const RGBAColor& color) const;
    bool operator!=(const RGBAColor& color) const;

    inline bool hasAlpha() const
    {
        return true;
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

//read-only access
class Palette
{
    friend class PixelFormat;

    bool pointerCopy;
protected:
    //the adress of the SLD_Palette struct should never change
    //read only_access
    const SDL_Palette * const _palette;
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
    RGBAColor getColors(int index) const;

};
}
}// namespace RAGE::SDL
#endif
