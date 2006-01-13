#include "SDLPixelFormat.hh"

namespace RAGE
{
    namespace SDL
    {

        Logger & operator << (Logger & log, const PixelFormat & pformat)
        {
            log << nl << "PixelFormat::debug()" << nl <<
            "- Bits Per Pixel = " << pformat.getBitsPerPixel() << nl <<
            "- Bytes Per Pixel = " << pformat.getBytesPerPixel() << nl <<
            "- Red shift = " << pformat.getRshift() << nl <<
            "- Green shift = " << pformat.getGshift() << nl <<
            "- Blue shift = " << pformat.getBshift() << nl <<
            "- Alpha shift = " << pformat.getAshift() << nl <<
            "- Red loss = " << pformat.getRloss() << nl <<
            "- Green loss = " << pformat.getGloss() << nl <<
            "- Blue loss = " << pformat.getBloss() << nl <<
            "- Alpha loss = " << pformat.getAloss() << nl <<
            std::hex << std::showbase <<
            "- Red mask = " << pformat.getRmask() << nl <<
            "- Green mask = " << pformat.getGmask() << nl <<
            "- Blue mask = " << pformat.getBmask() << nl <<
            "- Alpha mask = " << pformat.getAmask() << nl <<
            std::dec<<
            "- Color Key = " << pformat.getColorKey() << nl <<
            "- Alpha = " << pformat.getAlpha() << nl <<
            "- Palette = " << pformat.getPalette() ;
            return log;
        }

        PixelColor PixelFormat::getValueFromRGB(const RGBColor& val) const
        {
            //copy the format because we don't want it to be modified...
            SDL_PixelFormat * fmt = new SDL_PixelFormat(*_pformat);
            return SDL_MapRGB(fmt, val.getR(), val.getG(), val.getB());
        }

        PixelColor PixelFormat::getValueFromRGBA(const RGBAColor& val) const
        {
            //copy the format because we don't want it to be modified...
            SDL_PixelFormat * fmt = new SDL_PixelFormat(*_pformat);
            return SDL_MapRGBA(fmt, val.getR(), val.getG(), val.getB(), val.getA());
        }

        RGBColor PixelFormat::getRGBValue(const PixelColor& color) const
        {
            Uint8 r, g, b;
            //copy the format because we don't want it to be modified...
            SDL_PixelFormat * fmt = new SDL_PixelFormat(*_pformat);
            SDL_GetRGB(color, fmt, &r, &b, &g);
            return RGBColor(r, g, b);
        }

        RGBAColor PixelFormat::getRGBAValue(const PixelColor& color) const
        {

            Uint8 r, g, b, a;
            //copy the format because we don't want it to be modified...
            SDL_PixelFormat * fmt = new SDL_PixelFormat(*_pformat);
            SDL_GetRGBA(color, fmt, &r, &b, &g, &a);
            return RGBAColor(r, g, b, a);
        }
    }
} //namespace RAGE::SDL
