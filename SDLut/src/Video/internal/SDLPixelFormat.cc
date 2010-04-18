#include "Video/internal/SDLPixelFormat.hh"
#include "SDLConfig.hh"

using namespace RAGE;

namespace SDLut
{
namespace video
{
namespace internal
{

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


PixelFormat::PixelFormat()
        : ptm_sdl_pformat( new SDL_PixelFormat )
{
    pointerCopy = false;
}

PixelFormat::PixelFormat(const SDL_PixelFormat* pf) : ptm_sdl_pformat(pf)
{
    pointerCopy = true;
}

PixelFormat::~PixelFormat(void)
{
    if (!pointerCopy) delete ptm_sdl_pformat;
}

int PixelFormat::getBitsPerPixel() const
{
    return ptm_sdl_pformat->BitsPerPixel;
}
int PixelFormat::getBytesPerPixel() const
{
    return ptm_sdl_pformat->BytesPerPixel;
}
int PixelFormat::getRshift() const
{
    return ptm_sdl_pformat->Rshift;
}
int PixelFormat::getGshift() const
{
    return ptm_sdl_pformat->Gshift;
}
int PixelFormat::getBshift() const
{
    return ptm_sdl_pformat->Bshift;
}
int PixelFormat::getAshift() const
{
    return ptm_sdl_pformat->Ashift;
}

int PixelFormat::getRloss() const
{
    return ptm_sdl_pformat->Rloss;
}
int PixelFormat::getGloss() const
{
    return ptm_sdl_pformat->Gloss;
}
int PixelFormat::getBloss() const
{
    return ptm_sdl_pformat->Bloss;
}
int PixelFormat::getAloss() const
{
    return ptm_sdl_pformat->Aloss;
}

//BEWARE ! sometimes this has no sense, because only the palette is set...
//TODO : Handle this...
unsigned long PixelFormat::getRmask() const
{
    return ptm_sdl_pformat->Rmask;
}
unsigned long PixelFormat::getGmask() const
{
    return ptm_sdl_pformat->Gmask;
}
unsigned long PixelFormat::getBmask() const
{
    return ptm_sdl_pformat->Bmask;
}
unsigned long PixelFormat::getAmask() const
{
    return ptm_sdl_pformat->Amask;
}

PixelColor PixelFormat::getColorKey() const
{
    return ptm_sdl_pformat->colorkey;
}
int PixelFormat::getAlpha() const
{
    return ptm_sdl_pformat->alpha;
}
Palette PixelFormat::getPalette() const
{
    return Palette(ptm_sdl_pformat->palette);
}


RAGE::Logger & operator << (RAGE::Logger & log, const PixelFormat & pformat)
{
    log << nl << "PixelFormat:" << nl <<
    std::dec <<
    " - Bits Per Pixel = " << pformat.getBitsPerPixel() << nl <<
    " - Bytes Per Pixel = " << pformat.getBytesPerPixel() << nl <<
    " - Red shift = " << pformat.getRshift() << nl <<
    " - Green shift = " << pformat.getGshift() << nl <<
    " - Blue shift = " << pformat.getBshift() << nl <<
    " - Alpha shift = " << pformat.getAshift() << nl <<
    " - Red loss = " << pformat.getRloss() << nl <<
    " - Green loss = " << pformat.getGloss() << nl <<
    " - Blue loss = " << pformat.getBloss() << nl <<
    " - Alpha loss = " << pformat.getAloss() << nl <<
    std::hex << std::showbase <<
    " - Red mask = " << pformat.getRmask() << nl <<
    " - Green mask = " << pformat.getGmask() << nl <<
    " - Blue mask = " << pformat.getBmask() << nl <<
    " - Alpha mask = " << pformat.getAmask() << nl <<
    std::dec<<
    " - Color Key = " << pformat.getColorKey() << nl <<
    " - Alpha = " << pformat.getAlpha() << nl <<
    " - Palette = " << &pformat.getPalette() ; //TODO: Palette debug display on stream...
    return log;
}

//For SDL Video. getPixelColor removes alpha value in the case of RGBA -> RGB blending (as on screen).
//Therefore, it is impossible to blend afterwards.
//However OpenGL supports alpha blending for setting pixels on screen ( since v???)
//TODO : GLPixelFormat must keep alpha value, but still using SDL Format
//TODO : SDL alpha blending should be done before (in facade)
PixelColor PixelFormat::getPixelColor(const Color& color) const
{
    PixelColor pc;
    if ( ! color.hasAlpha() )
    {
        pc = SDL_MapRGB(const_cast<SDL_PixelFormat*>(ptm_sdl_pformat), color.getR(), color.getG(), color.getB());

        //no alpha : setting last bits of PixelColor
        //TMP : TO make sure in case of color BUG
//if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
//    pc = pc | 0x000000ff;
//else
//    pc = pc | 0xff000000;

    }
    else
    {
        pc = SDL_MapRGBA(const_cast<SDL_PixelFormat*>(ptm_sdl_pformat),color.getR(),color.getG(),color.getB(), color.getA());
    }

    return pc;
}

Color PixelFormat::getColor(const PixelColor& val) const
{

    Uint8 r, g, b, a;
    //SDL_PixelFormat * fmt = new SDL_PixelFormat(*_pformat);
    SDL_GetRGBA(val, const_cast<SDL_PixelFormat*>(ptm_sdl_pformat), &r, &g, &b, &a);
    //BUG here : seems to ignore alpha ? ( found with SDLTestColor )
    return Color(r, g, b, a);
}

PixelColor PixelFormat::convert(PixelColor val, const PixelFormat & pf) const
{
    Uint8 r, g, b, a;
    //SDL_PixelFormat * fmt = new SDL_PixelFormat(*_pformat);
    SDL_GetRGBA(val, const_cast<SDL_PixelFormat*>(pf.ptm_sdl_pformat), &r, &g, &b, &a);

    PixelColor pc = SDL_MapRGBA(const_cast<SDL_PixelFormat*>(ptm_sdl_pformat),r,g,b,a);

    return pc;
}


}
}
} //namespace SDLut::SDL
