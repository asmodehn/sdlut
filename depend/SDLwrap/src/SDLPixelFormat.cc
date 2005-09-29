#include "SDLPixelFormat.hh"

void SDLPixelFormat::debug(void) const
{
	std::cout << "\nSDLPixelFormat::debug()" << "\n" <<
	"- Bits Per Pixel = " << getBitsPerPixel() << "\n" <<
	"- Bytes Per Pixel = " << getBytesPerPixel() << "\n" <<
	"- Red shift = " << getRshift() << "\n" <<
	"- Green shift = " << getGshift() << "\n" <<
	"- Blue shift = " << getBshift() << "\n" <<
	"- Alpha shift = " << getAshift() << "\n" <<
	"- Red loss = " << getRloss() << "\n" <<
	"- Green loss = " << getGloss() << "\n" <<
	"- Blue loss = " << getBloss() << "\n" <<
	"- Alpha loss = " << getAloss() << "\n" <<
	std::hex << std::showbase <<
	"- Red mask = " << getRmask() << "\n" <<
	"- Green mask = " << getGmask() << "\n" <<
	"- Blue mask = " << getBmask() << "\n" <<
	"- Alpha mask = " << getAmask() <<
	std::dec <<
	//To be continued
	std::endl;
}

SDLPixelColor SDLPixelFormat::getValueFromRGB(const SDLRGBColor& val) const
{
	//copy the format because we don't want it to be modified...
	SDL_PixelFormat * fmt = new SDL_PixelFormat(*_pformat);
	 return SDL_MapRGB(fmt, val.getR(), val.getG(), val.getB());
}

SDLPixelColor SDLPixelFormat::getValueFromRGBA(const SDLRGBAColor& val) const
{
	//copy the format because we don't want it to be modified...
	SDL_PixelFormat * fmt = new SDL_PixelFormat(*_pformat);
	return SDL_MapRGBA(fmt, val.getR(), val.getG(), val.getB(), val.getA());
}

SDLRGBColor SDLPixelFormat::getRGBValue(const SDLPixelColor& color) const
{
	Uint8 r, g, b;
	//copy the format because we don't want it to be modified...
	SDL_PixelFormat * fmt = new SDL_PixelFormat(*_pformat);
	SDL_GetRGB(color, fmt, &r, &b, &g);
	return SDLRGBColor(r, g, b);
}

SDLRGBAColor SDLPixelFormat::getRGBAValue(const SDLPixelColor& color) const
{
	
	Uint8 r, g, b, a;
	//copy the format because we don't want it to be modified...
	SDL_PixelFormat * fmt = new SDL_PixelFormat(*_pformat);
	SDL_GetRGBA(color, fmt, &r, &b, &g, &a);
	return SDLRGBAColor(r, g, b, a);
}

