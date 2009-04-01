#include "Video/SDLPixelFormat.hh"
#include "SDLConfig.hh"

namespace RAGE
{
    namespace SDL
    {

	    PixelFormat::PixelFormat(const SDL_PixelFormat* pf) : _pformat(pf)
	    {
		    pointerCopy = true;
	    }

	    PixelFormat::~PixelFormat(void)
	    {
		    if (!pointerCopy) delete _pformat;
	    }

	    int PixelFormat::getBitsPerPixel() const
	    {
		    return _pformat->BitsPerPixel;
	    }
	    int PixelFormat::getBytesPerPixel() const
	    {
		    return _pformat->BytesPerPixel;
	    }
	    int PixelFormat::getRshift() const
	    {
		    return _pformat->Rshift;
	    }
	    int PixelFormat::getGshift() const
	    {
		    return _pformat->Gshift;
	    }
	    int PixelFormat::getBshift() const
	    {
		    return _pformat->Bshift;
	    }
	    int PixelFormat::getAshift() const
	    {
		    return _pformat->Ashift;
	    }

	    int PixelFormat::getRloss() const
	    {
		    return _pformat->Rloss;
	    }
	    int PixelFormat::getGloss() const
	    {
		    return _pformat->Gloss;
	    }
	    int PixelFormat::getBloss() const
	    {
		    return _pformat->Bloss;
	    }
	    int PixelFormat::getAloss() const
	    {
		    return _pformat->Aloss;
	    }

	//BEWARE ! sometimes this has no sense, because only the palette is set...
	//TODO : Handle this...
	    unsigned long PixelFormat::getRmask() const
	    {
		    return _pformat->Rmask;
	    }
	    unsigned long PixelFormat::getGmask() const
	    {
		    return _pformat->Gmask;
	    }
	    unsigned long PixelFormat::getBmask() const
	    {
		    return _pformat->Bmask;
	    }
	    unsigned long PixelFormat::getAmask() const
	    {
		    return _pformat->Amask;
	    }

	    PixelColor PixelFormat::getColorKey() const
	    {
		    return _pformat->colorkey;
	    }
	    int PixelFormat::getAlpha() const
	    {
		    return _pformat->alpha;
	    }
	    Palette* PixelFormat::getPalette() const
	    {
		    return &Palette(_pformat->palette);
	    }

	    
        Logger & operator << (Logger & log, const PixelFormat & pformat)
        {
            log << nl << "PixelFormat:" << nl <<
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
            " - Palette = " << pformat.getPalette() ;
            return log;
        }

        PixelColor PixelFormat::getValueFromRGB(const RGBColor& val) const
        {
            
            //SDL_PixelFormat * fmt = new SDL_PixelFormat(*_pformat);
            return SDL_MapRGB(const_cast<SDL_PixelFormat*>(_pformat), val.getR(), val.getG(), val.getB());
			
        }

        PixelColor PixelFormat::getValueFromRGBA(const RGBAColor& val) const
        {
            //SDL_PixelFormat * fmt = new SDL_PixelFormat(*_pformat);
			return SDL_MapRGBA(const_cast<SDL_PixelFormat*>(_pformat), val.getR(), val.getG(), val.getB(), val.getA());
        }

        RGBColor PixelFormat::getRGBValue(const PixelColor& color) const
        {
            Uint8 r, g, b;
            //SDL_PixelFormat * fmt = new SDL_PixelFormat(*_pformat);
            SDL_GetRGB(color, const_cast<SDL_PixelFormat*>(_pformat), &r, &g, &b);
            return RGBColor(r, g, b);
        }

        RGBAColor PixelFormat::getRGBAValue(const PixelColor& color) const
        {

            Uint8 r, g, b, a;
            //SDL_PixelFormat * fmt = new SDL_PixelFormat(*_pformat);
            SDL_GetRGBA(color, const_cast<SDL_PixelFormat*>(_pformat), &r, &g, &b, &a);
			//BUG here : seems to ignore alpha ? ( found with SDLTestColor )
            return RGBAColor(r, g, b, a);
        }
    }
} //namespace RAGE::SDL
