#include "Video/Color.hh"
#include "SDLConfig.hh"

namespace RAGE
{
namespace SDL
{

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
        : ptm_sdl_color(new SDL_Color)
{
    ptm_sdl_color->r=r;
    ptm_sdl_color->g=g;
    ptm_sdl_color->b=b;
    ptm_sdl_color->unused = a;
}

Color::Color(const Color & rgbcolor)
        :ptm_sdl_color(new SDL_Color)
{
    ptm_sdl_color->r=rgbcolor.getR();
    ptm_sdl_color->g=rgbcolor.getG();
    ptm_sdl_color->b=rgbcolor.getB();
    ptm_sdl_color->unused=rgbcolor.getA();
}

Color& Color::operator=( const Color & rgbcolor)
{
    ptm_sdl_color->r=rgbcolor.getR();
    ptm_sdl_color->g=rgbcolor.getG();
    ptm_sdl_color->b=rgbcolor.getB();
    ptm_sdl_color->unused=rgbcolor.getA();
    return *this;
}
Color::~Color()
{
    delete ptm_sdl_color;// SDL_Color is a simple SDL structure, no fancy delete needed AFAIK
}

SDL_Color Color::get_SDL() const
{
    return *ptm_sdl_color;
}

void Color::setR(unsigned char nr)
{
    ptm_sdl_color->r=nr ;
}
void Color::setG(unsigned char ng)
{
    ptm_sdl_color->g=ng ;
}
void Color::setB(unsigned char nb)
{
    ptm_sdl_color->b=nb ;
}
void Color::setA(unsigned char na)
{
    ptm_sdl_color->unused=na ;
}

unsigned char Color::getR(void) const
{
    return ptm_sdl_color->r;
}
unsigned char Color::getG(void) const
{
    return ptm_sdl_color->g;
}
unsigned char Color::getB(void) const
{
    return ptm_sdl_color->b;
}

unsigned char Color::getA(void) const
{
    return ptm_sdl_color->unused;
}

PixelColor Color::getGLPixelColor() const
{
#if (SDL_BYTE_ORDER == SDL_BIG_ENDIAN)
    unsigned int glColor = ptm_sdl_color->unused | ptm_sdl_color->b << 8 | ptm_sdl_color->g << 16 | ptm_sdl_color->r << 24;
#else
    unsigned int glColor = ptm_sdl_color->r | ptm_sdl_color->g << 8 | ptm_sdl_color->b << 16 | ptm_sdl_color->unused << 24;
#endif
    return glColor;
}

bool Color::operator==(const Color& color) const
{
    return ptm_sdl_color->r == color.getR() && ptm_sdl_color->g == color.getG() && ptm_sdl_color->b == color.getB() && ptm_sdl_color->unused == color.getA();
}

bool Color::operator!=(const Color& color) const
{
    return !(ptm_sdl_color->r == color.getR() && ptm_sdl_color->g == color.getG() && ptm_sdl_color->b == color.getB() && ptm_sdl_color->unused == color.getA());
}



Palette::Palette(const SDL_Palette* palette) : ptm_sdl_palette(palette)
{
    pointerCopy = true;
}

Palette::~Palette(void)
{
    if (!pointerCopy)
        delete ptm_sdl_palette;
}

int Palette::getNColors(void) const
{
    return ptm_sdl_palette->ncolors;
}
Color Palette::getColors(int index) const
{
    //creates a new color to protects color in Palette...
    //maybe using const would be better ??
    return Color(	ptm_sdl_palette->colors[index].r,
                      ptm_sdl_palette->colors[index].g,
                      ptm_sdl_palette->colors[index].b,
                      ptm_sdl_palette->colors[index].unused
                    );
}


}
}
