#include "Video/SDLColor.hh"
#include "SDLConfig.hh"

namespace RAGE
{
namespace SDL
{

RGBAColor::RGBAColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
        : _color(new SDL_Color)
{
    _color->r=r;
    _color->g=g;
    _color->b=b;
    _color->unused = a;
}

RGBAColor::RGBAColor(const RGBAColor & rgbcolor)
        :_color(new SDL_Color)
{
    _color->r=rgbcolor.getR();
    _color->g=rgbcolor.getG();
    ;
    _color->b=rgbcolor.getB();
    ;
    _color->unused=rgbcolor.getA();
}

RGBAColor& RGBAColor::operator=( const RGBAColor & rgbcolor)
{
    _color->r=rgbcolor.getR();
    _color->g=rgbcolor.getG();
    ;
    _color->b=rgbcolor.getB();
    ;
    _color->unused=rgbcolor.getA();
    return *this;
}
RGBAColor::~RGBAColor()
{
    delete _color;// SDL_Color is a simple SDL structure, no fancy delete needed AFAIK
}

SDL_Color RGBAColor::get_SDL() const
{
    return *_color;
}

void RGBAColor::setR(unsigned char nr)
{
    _color->r=nr ;
}
void RGBAColor::setG(unsigned char ng)
{
    _color->g=ng ;
}
void RGBAColor::setB(unsigned char nb)
{
    _color->b=nb ;
}
void RGBAColor::setA(unsigned char na)
{
    _color->unused=na ;
}

unsigned char RGBAColor::getR(void) const
{
    return _color->r;
}
unsigned char RGBAColor::getG(void) const
{
    return _color->g;
}
unsigned char RGBAColor::getB(void) const
{
    return _color->b;
}

unsigned char RGBAColor::getA(void) const
{
    return _color->unused;
}

PixelColor RGBAColor::getGLPixelColor() const
{
#if (SDL_BYTE_ORDER == SDL_BIG_ENDIAN)
    unsigned int glColor = _color->unused | _color->b << 8 | _color->g << 16 | _color->r << 24;
#else
    unsigned int glColor = _color->r | _color->g << 8 | _color->b << 16 | _color->unused << 24;
#endif
    return glColor;
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
