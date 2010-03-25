#include "Video/Color.hh"
#include "SDLConfig.hh"

namespace SDLut
{
namespace video
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


Color & Color::blendover(const Color & c)
{
    *this = blend(*this,c);
    return *this;
}

Color & Color::blendunder(const Color &c )
{
    *this = blend(c,*this);
    return *this;
}


PixelColor Color::getGLPixelColor() const
{

    //TOFIX :
    //We need to use pixel format to get these....
#if (SDL_BYTE_ORDER == SDL_BIG_ENDIAN)
    unsigned int glColor = ptm_sdl_color->unused | ptm_sdl_color->b << 8 | ptm_sdl_color->g << 16 | ptm_sdl_color->r << 24;
#else
    unsigned int glColor = ptm_sdl_color->r | ptm_sdl_color->g << 8 | ptm_sdl_color->b << 16 | ptm_sdl_color->unused << 24;
#endif
    return glColor;
}

bool Color::isSimilarTo(const Color& c) const
{
    bool res = true;
    res = res && abs(c.getR() -  ptm_sdl_color->r ) <= 1;
    res = res && abs(c.getG() -  ptm_sdl_color->g ) <= 1;
    res = res && abs(c.getB() -  ptm_sdl_color->b ) <= 1;
    res = res && abs(c.getA() -  ptm_sdl_color->unused ) <= 1;
    return res;

}

bool Color::operator==(const Color& color) const
{
    return ptm_sdl_color->r == color.getR() && ptm_sdl_color->g == color.getG() && ptm_sdl_color->b == color.getB() && ptm_sdl_color->unused == color.getA();
}

bool Color::operator!=(const Color& color) const
{
    return !(ptm_sdl_color->r == color.getR() && ptm_sdl_color->g == color.getG() && ptm_sdl_color->b == color.getB() && ptm_sdl_color->unused == color.getA());
}



Color blend(const Color & cover, const Color & cunder)
{ //  alpha = aover // proper alpha value.
    // compo = alpha * cover + ( 1 - alpha) * cunder   ==>  compo = cunder + alpha ( cover - cunder )
    // and acompo = aover + aunder * ( 1 - aover ) <==> acompo = aunder + aover ( 1 - aunder )
    Color compo;
    compo.setR( cunder.getR() + float(cover.getA())/255.0f * ( cover.getR() - cunder.getR() ) );
    compo.setG( cunder.getG() + float(cover.getA())/255.0f * ( cover.getG() - cunder.getG() ) );
    compo.setB( cunder.getB() + float(cover.getA())/255.0f * ( cover.getB() - cunder.getB() ) );
    compo.setA( cunder.getA() + cover.getA() * float( 255 - cunder.getA() )/255.0f );
    return compo;
}
}
}
