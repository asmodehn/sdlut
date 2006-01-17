#ifndef SDL_COLOR_HH
#define SDL_COLOR_HH

#include "SDLConfig.hh"
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

namespace RAGE
{
     namespace SDL {
//TODO : Color constructor with string ("black", "yellow", "grey", etc. )
//TODO : Color operator, like + - = etc. (like a vector)
class RGBColor
{
	friend class SDLPalette;

protected:
	//the address of the SDL_Color struct should never change
	SDL_Color * const _color;
	bool pointerCopy;

//Maybe useless ??
	/*explicit SDLRGBColor(SDL_Color * color) : _color(color)
	{
		pointerCopy = true;
	}*/

public:

	//Because NULL has no sense for function using colors, defaut constructor
	// just paint it black :)
	RGBColor(Uint8 r=0, Uint8 g=0, Uint8 b=0) : _color(new SDL_Color)
	{
		_color->r=r;
		_color->g=g;
		_color->b=b;
		pointerCopy = false;
	}
	RGBColor(const RGBColor & rgbcolor)
    :_color(new SDL_Color)
    {
	    _color->r=rgbcolor.getR();
		_color->g=rgbcolor.getG();;
		_color->b=rgbcolor.getB();;
		pointerCopy = false;
	}
	RGBColor& operator=( const RGBColor & rgbcolor)
	{
	    _color->r=rgbcolor.getR();
		_color->g=rgbcolor.getG();;
		_color->b=rgbcolor.getB();;
		pointerCopy = false;
		return *this;
	}
	virtual ~RGBColor() { if (!pointerCopy) delete _color;}

	void setR(Uint8 nr) { _color->r=nr ;}
	void setG(Uint8 ng) { _color->g=ng ;}
	void setB(Uint8 nb) { _color->b=nb ;}

	unsigned int getR(void) const { return _color->r;}
	unsigned int getG(void) const { return _color->g;}
	unsigned int getB(void) const { return _color->b;}

	inline friend std::ostream& operator << (std::ostream& os, const RGBColor& c)
		{ return os << "RGBColor : R=" << c.getR() << " G=" << c.getG() << " B=" << c.getB() << " "; }


};

/**
 * \class SDLRGBAColor (alias SDLColor)
 *
 * \ingroup Video
 *
 * \brief This class wraps SDL_Color with alpha
 *
 * \author Alex
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
	RGBAColor(Uint8 r=0, Uint8 g=0, Uint8 b=0, Uint8 a=0)
	: RGBColor(r, g, b)
	{
		_color->unused=a;
	}
	RGBAColor(const RGBAColor & rgbacolor)
	: RGBColor(rgbacolor.getR(), rgbacolor.getG(), rgbacolor.getB())
	{
	    _color->unused=rgbacolor.getA();
	}
	RGBAColor& operator=( const RGBAColor & rgbacolor )
	{
	    _color->r=rgbacolor.getR();
		_color->g=rgbacolor.getG();;
		_color->b=rgbacolor.getB();;
		_color->unused=rgbacolor.getA();
		return *this;
	}
	virtual ~RGBAColor() {}

	void setA(Uint8 na) { _color->unused=na ;}

	unsigned int     getA(void) const {return _color->unused;}

	inline friend std::ostream& operator << (std::ostream& os, const RGBAColor& c)
		{ return os << "RGBColor : R=" << c.getR() << " G=" << c.getG() << " B=" << c.getB() << " A=" << c.getA() << " " ; } //not sure how to derivate that properly... TODO
};

//defining an alias. Could be usefull.
#define Color RGBColor

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
	explicit Palette(const SDL_Palette* palette) : _palette(palette)
	{
		pointerCopy = true;
	}
public:

	~Palette(void) { if (!pointerCopy) delete _palette; }

	inline int getNColors(void) const { return _palette->ncolors; }
	inline RGBAColor getColors(int index) const
	{
		//creates a new color to protects color in Palette...
		//maybe using const would be better ??
		return RGBAColor(	_palette->colors[index].r,
							_palette->colors[index].g,
							_palette->colors[index].b,
							_palette->colors[index].unused
						);
	}

};
     }
}// namespace RAGE::SDL
#endif
