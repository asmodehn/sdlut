#include "SDLFont.hh"

#include "SDLResources.inc"

namespace RAGE
{
namespace SDL
{



	//a simple bridge to uses SDL_ttf structures if available , without having the client of RAGE::SDL worrying about it
	class TTFFont
	{
	public :

#ifdef HAVE_SDLTTF


		int _ref;
		TTF_Font * _ttfstruct;
		
		//explicit TTFFont(TTF_Font* ttfstruct) : _ttfstruct(ttfstruct) {};

		TTFFont(std::string filename, int ptsize) throw (std::logic_error)
		try : _ttfstruct(TTF_OpenFont(filename.c_str(),ptsize)), _ref(1)
		{
			if(_ttfstruct==NULL) {
				throw std::logic_error("TTF_OpenFont Error : " + GetError(TTF));
			}
		}
		catch (std::exception& e)
		{
			Log << nl << "Exception catched in internal TTFFont Constructor :"  << nl <<
					e.what() << std::endl;
		            //TODO : much more explicit error message...
		};


		//Copy constructor (carefull not full copy, the TTF structure is shared)
		TTFFont(const TTFFont & font)
		{
			++_ref;
			_ttfstruct = font._ttfstruct;
		}


		//to load default font if any error happens...
		//TTFFont(){};

		~TTFFont()
		{
			--_ref;
			if (_ref == 0)
				TTF_CloseFont(_ttfstruct), _ttfstruct=NULL;
		}

#else //HAVE_SDLTTF

		TTFFont(std::string filename, int ptsize) throw (std::logic_error)
		{
			Log <<"Cannot load "<< filename <<"SDL_ttf not detected. Loading default Font...";
			//TODO
		}
#endif //HAVE_SDLTTF
		
		TTFFont(int ptsize) throw (std::logic_error)
		{
			Log <<" Loading default Font...";
			//TODO
		}

	};





	Font::Font(std::string filename, int ptsize) throw (std::logic_error)
try : _font(new TTFFont(filename,ptsize))
{
	if(_font==NULL) {// might be useless... ???
		Log << "Error Loading Font from " << filename;
    }
}
catch (std::exception& e)
{
	Log << nl << "Exception catched in Font Constructor :"  << nl <<
            e.what() << std::endl;
            //TODO : much more explicit error message...
};


Font::Font(const RAGE::SDL::Font &font)
: _font(font._font)
{}


	Font::~Font()
{
	delete _font, _font=NULL;
}


	#ifdef HAVE_SDLTTF

SDL_Surface* Font::render(std::string text, Color c, RenderMode mode, Color bgc) const
{
	SDL_Surface * surf;
	switch ( mode )
	{
	case Blended : surf=TTF_RenderText_Blended(_font->_ttfstruct,text.c_str(), c.get_SDL()); break;
	case Shaded : surf=TTF_RenderText_Shaded(_font->_ttfstruct,text.c_str(),c.get_SDL(), bgc.get_SDL()); break;
		case Solid :
		default: surf=TTF_RenderText_Solid(_font->_ttfstruct,text.c_str(), c.get_SDL());
	}

	return surf;
}
#else //HAVE_SDL_TTF

#warning "RAGE::SDL default Font not implemented yet"


SDL_Surface* Font::render(std::string text, Color c, RenderMode mode, Color bgc) const
{
	SDL_Surface * surf;
	switch ( mode )
	{
	case Blended : surf=NULL break;
	case Shaded : surf=NULL break;
		case Solid :
		default: surf=NULL ;
	}

	return surf;
}



#endif//HAVE_SDLTTF



}
}
