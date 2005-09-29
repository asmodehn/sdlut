#ifndef SDLCOLOR_HH
#define SDLCOLOR_HH

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

//TODO : Color constructor with string ("black", "yellow", "grey", etc. )
class SDLRGBColor
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
	SDLRGBColor(Uint8 r=0, Uint8 g=0, Uint8 b=0) : _color(new SDL_Color)
	{
		_color->r=r;
		_color->g=g;
		_color->b=b;
		pointerCopy = false;
	}
	virtual ~SDLRGBColor() { if (!pointerCopy) delete _color;}
	
	void setR(Uint8 nr) { _color->r=nr ;}
	void setG(Uint8 ng) { _color->g=ng ;}
	void setB(Uint8 nb) { _color->b=nb ;}
	
	Uint8 getR(void) const { return _color->r;}
	Uint8 getG(void) const { return _color->g;}
	Uint8 getB(void) const { return _color->b;}
	
	inline friend std::ostream& operator << (std::ostream& os, const SDLRGBColor& c)
		{ return os << "RGBColor : R=" << c.getR() << " G=" << c.getG() << " B=" << c.getB() << " "; } 

	
};

class SDLRGBAColor : public SDLRGBColor
{
//	explicit SDLRGBAColor(SDL_Color * color) : SDLRGBColor(color) {}

public:
	SDLRGBAColor(Uint8 r=0, Uint8 g=0, Uint8 b=0, Uint8 a=0)
	: SDLRGBColor(r, g, b)
	{
		_color->unused=a;
	}
	virtual ~SDLRGBAColor() {}

	void setA(Uint8 na) { _color->unused=na ;}
	
	Uint8 getA(void) const {return _color->unused;}

	inline friend std::ostream& operator << (std::ostream& os, const SDLRGBAColor& c)
		{ return os << "RGBColor : R=" << c.getR() << " G=" << c.getG() << " B=" << c.getB() << " A=" << c.getA() << " " ; } //not sure how to derivate that properly... TODO
};

//defining an alias. Could be usefull.
#define SDLColor SDLRGBColor

//read-only access
class SDLPalette
{
	friend class SDLPixelFormat;
	
	bool pointerCopy;
protected:
	//the adress of the SLD_Palette struct should never change
	//read only_access
	const SDL_Palette * const _palette;
	// protected to prevent manual creation of palette
	//maybe completely useless...
	// default : one black color
	/*SDLPalette(int ncolors = 1) : _palette(new SDL_Palette)
	{
		_palette->ncolors = ncolors;
		_palette->colors = (new SDLColor[ncolors])->_color;
		pointerCopy = false;
	}*/
	//idem for the copy contructor
	/*SDLPalette(const SDLPalette & p ) : _palette(new SDL_Palette)
	{
		_palette->ncolors = p.getNColors();
		for (int i=0; i<_palette->ncolors ; i++)
			_palette->colors[i] = p._palette->colors[i];
		pointerCopy = false;
	}*/
	//to handle explicit cast from SDL
	//beware : store only a pointer...
	//so the original should not be destroyed !
	explicit SDLPalette(const SDL_Palette* palette) : _palette(palette)
	{
		pointerCopy = true;
	}
public:
	
	~SDLPalette(void) { if (!pointerCopy) delete _palette; }
	
	inline int getNColors(void) const { return _palette->ncolors; }
	inline SDLRGBAColor getColors(int index) const
	{
		//creates a new color to protects color in Palette...
		//maybe using const would be better ??
		return SDLRGBAColor(	_palette->colors[index].r,
							_palette->colors[index].g,
							_palette->colors[index].b,
							_palette->colors[index].unused
						);
	}
	
};
#endif
