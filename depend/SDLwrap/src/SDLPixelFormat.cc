#include "SDLPixelFormat.hh"

namespace SDL {

void PixelFormat::debug(void) const
{
	Log << nl << "PixelFormat::debug()" << nl <<
	"- Bits Per Pixel = " << getBitsPerPixel() << nl <<
	"- Bytes Per Pixel = " << getBytesPerPixel() << nl <<
	"- Red shift = " << getRshift() << nl <<
	"- Green shift = " << getGshift() << nl <<
	"- Blue shift = " << getBshift() << nl <<
	"- Alpha shift = " << getAshift() << nl <<
	"- Red loss = " << getRloss() << nl <<
	"- Green loss = " << getGloss() << nl <<
	"- Blue loss = " << getBloss() << nl <<
	"- Alpha loss = " << getAloss() << nl <<
	std::hex << std::showbase <<
	"- Red mask = " << getRmask() << nl <<
	"- Green mask = " << getGmask() << nl <<
	"- Blue mask = " << getBmask() << nl <<
	"- Alpha mask = " << getAmask() <<
	std::dec <<
	//To be continued
	std::endl;
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

} //namespace SDL
