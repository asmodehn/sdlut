#include "Video/SDLColor.hh"
#include "SDLConfig.hh"

namespace RAGE
{
	namespace SDL
	{

		RGBColor::RGBColor(unsigned char r, unsigned char g, unsigned char b)
			: _color(new SDL_Color)
		{
			_color->r=r;
			_color->g=g;
			_color->b=b;
			_color->unused = 255;
			pointerCopy = false;
		}
		RGBColor::RGBColor(const RGBColor & rgbcolor)
			:_color(new SDL_Color)
		{
			_color->r=rgbcolor.getR();
			_color->g=rgbcolor.getG();
			;
			_color->b=rgbcolor.getB();
			;
			_color->unused=255;
			pointerCopy = false;
		}
		RGBColor& RGBColor::operator=( const RGBColor & rgbcolor)
		{
			_color->r=rgbcolor.getR();
			_color->g=rgbcolor.getG();
			;
			_color->b=rgbcolor.getB();
			;
			pointerCopy = false;
			return *this;
		}
		RGBColor::~RGBColor()
		{
			if (!pointerCopy)
				delete _color;
		}

		SDL_Color RGBColor::get_SDL() const
		{
			return *_color;
		}

		void RGBColor::setR(unsigned char nr)
		{
			_color->r=nr ;
		}
		void RGBColor::setG(unsigned char ng)
		{
			_color->g=ng ;
		}
		void RGBColor::setB(unsigned char nb)
		{
			_color->b=nb ;
		}

		unsigned char RGBColor::getR(void) const
		{
			return _color->r;
		}
		unsigned char RGBColor::getG(void) const
		{
			return _color->g;
		}
		unsigned char RGBColor::getB(void) const
		{
			return _color->b;
		}

		RGBAColor::RGBAColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
			: RGBColor(r, g, b)
		{
			_color->unused=a;
		}
		RGBAColor::RGBAColor(const RGBAColor & rgbacolor)
			: RGBColor(rgbacolor.getR(), rgbacolor.getG(), rgbacolor.getB())
		{
			_color->unused=rgbacolor.getA();
		}
		RGBAColor& RGBAColor::operator=( const RGBAColor & rgbacolor )
		{
			_color->r=rgbacolor.getR();
			_color->g=rgbacolor.getG();
			;
			_color->b=rgbacolor.getB();
			;
			_color->unused=rgbacolor.getA();
			return *this;
		}
		RGBAColor::~RGBAColor()
		{}

		void RGBAColor::setA(unsigned char na)
		{
			_color->unused=na ;
		}

		unsigned char RGBAColor::getA(void) const
		{
			return _color->unused;
		}

		bool RGBAColor::operator==(const RGBAColor& color) const
		{
			return _color->r == color.getR() && _color->g == color.getG() && _color->b == color.getB() && _color->unused == color.getA();
		}

		bool RGBAColor::operator!=(const RGBAColor& color) const
		{
			return !(_color->r == color.getR() && _color->g == color.getG() && _color->b == color.getB() && _color->unused == color.getA());
		}

		Palette::Palette(const SDL_Palette* palette) : _palette(palette)
		{
			pointerCopy = true;
		}

		Palette::~Palette(void)
			{
				if (!pointerCopy)
					delete _palette;
			}

			int Palette::getNColors(void) const
			{
				return _palette->ncolors;
			}
			RGBAColor Palette::getColors(int index) const
			{
                //creates a new color to protects color in Palette...
                //maybe using const would be better ??
				return RGBAColor(	_palette->colors[index].r,
						_palette->colors[index].g,
						_palette->colors[index].b,
						_palette->colors[index].unused
						);
			}


	}
}
