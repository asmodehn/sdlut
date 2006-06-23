#include "SDLFont.hh"

#include "SDLResources.inc"

namespace RAGE
{
namespace SDL
{

//if SDL_TTF used, provide a class to be used as a bridge.
//this way the client doesnt have to take care of which function is available
#ifdef HAVE_SDLTTF

namespace TTF
{
	class Font
	{
		//shared between copies of the same instance
		TTF_Font * _ttfstruct;
		int _ref;

		public:
			//Constructor
			Font(std::string filename, int ptsize) throw (std::logic_error);
			
			//Copy Constructor
			//copy completely the content of *_ttfstruct
			Font(const Font & );
			//Assignement operator
			Font & operator=(const Font &);

			//Destructor
			~Font();


			//Attributes Access
			static void byteSwapUNICODE(bool swapped);

			typedef enum { Normal = TTF_STYLE_NORMAL, Bold = TTF_STYLE_BOLD, Italic = TTF_STYLE_ITALIC, Underline = TTF_STYLE_UNDERLINE }Style;

			Style getStyle();
			void setStyle(Style s);
			
			int height();
			int ascent();
			int descent();
			int lineskip();
			long faces();
			bool faceIsFixedWidth();
			std::string faceFamilyName();
			std::string faceStyleName();
			Rect size(std::string text);

			//Rendering
			typedef enum { Solid, Shaded, Blended } RenderMode;

			//The Background color is used only if RenderMode = Shaded otherwise the background is transparent.
			RGBSurface * render(std::string text, Color c, RenderMode mode, Color bgc = Color()) const;



	};


//Implementation of class Font
		Font::Font(std::string filename, int ptsize) throw (std::logic_error)
		try : _ttfstruct(TTF_OpenFont(filename.c_str(),ptsize)), _ref(1)
		{
			if(_ttfstruct==NULL) {
				throw std::logic_error("TTF_OpenFont Error : " + GetError());
			}
		}
		catch (std::exception& e)
		{
			Log << nl << "Exception catched in internal TTFFont Constructor :"  << nl <<
					e.what() << std::endl;
		            //TODO : much more explicit error message...
		};

		Font::Font(const Font & font)
		{
			++_ref;
			_ttfstruct = font._ttfstruct;
		}

		Font::~Font()
		{
			--_ref;
			if (_ref == 0)
				TTF_CloseFont(_ttfstruct), _ttfstruct=NULL;
		}

		RGBSurface * Font::render(std::string text, Color c, RenderMode mode, Color bgc) const
		{
			SDL_Surface * surf;
			switch ( mode )
			{
				case Blended : surf=TTF_RenderText_Blended(_ttfstruct,text.c_str(), c.get_SDL()); break;
				case Shaded : surf=TTF_RenderText_Shaded(_ttfstruct,text.c_str(),c.get_SDL(), bgc.get_SDL()); break;
				case Solid :
				default: surf=TTF_RenderText_Solid(_ttfstruct,text.c_str(), c.get_SDL());
			}
			return new RGBSurface(surf);
		}

		//Attributes Access
		void Font::byteSwapUNICODE(bool swapped)
		{
			TTF_ByteSwappedUNICODE(swapped);
		}

		Font::Style Font::getStyle()
		{
			return Style(TTF_GetFontStyle(_ttfstruct));
		}

			void Font::setStyle(Style s)
			{
				TTF_SetFontStyle(_ttfstruct,s);
			}

			
			int Font::height()
			{
				return TTF_FontHeight(_ttfstruct);
			}

			int Font::ascent()
			{
				return TTF_FontAscent(_ttfstruct);
			}

			int Font::descent()
			{
				return TTF_FontDescent(_ttfstruct);
			}

			int Font::lineskip()
			{
				return TTF_FontLineSkip(_ttfstruct);
			}

			long Font::faces()
			{
				return TTF_FontFaces(_ttfstruct);
			}

			bool Font::faceIsFixedWidth()
			{
				return TTF_FontFaceIsFixedWidth(_ttfstruct) != 0 ;
			}

			std::string Font::faceFamilyName()
			{
				return std::string( TTF_FontFaceFamilyName(_ttfstruct) );
			}

			std::string Font::faceStyleName()
			{
				return std::string( TTF_FontFaceStyleName(_ttfstruct) );
			}

			Rect Font::size(std::string text)
			{
				int w,h;
				int test = TTF_SizeText(_ttfstruct,text.c_str(),&w,&h);
				if (!test) //success
					return Rect(w,h);
				//failure
				Log << nl << GetError();
				return Rect(0,0);
			}

}//namespace TTF

#else //HAVE_SDLTTF

	//dummy class (maybe not needed ?)
	//the implementation of the fallback code, has to be done in the calling class
	//not yet sure this is the best choice...
	class TTF {};

#endif //HAVE_SDLTTF

	



	Font::Font(std::string filename, int ptsize) throw (std::logic_error)
try :
#ifdef HAVE_SDLTTF
	_font(new TTF::Font(filename,ptsize))
#else
	_font(NULL)
#endif

{
	if(_font==NULL) {
		Log << "TTF Support not available" << filename;
    }
}
catch (std::exception& e)
{
	Log << nl << "Exception catched in Font Constructor :"  << nl <<
            e.what() << std::endl;
            //TODO : much more explicit error message...
};

//Copy Constructor
Font::Font(const RAGE::SDL::Font &font)
: _font(font._font)
{}


	Font::~Font()
{
	delete _font, _font=NULL;
}



RGBSurface * Font::render(std::string text, Color c, RenderMode mode, Color bgc) const
{
	if(_font !=NULL)
	{
		switch(mode)
		{
		case (Shaded) : return _font->render(text,c,TTF::Font::Shaded,bgc); break;
		case (Blended) : return _font->render(text,c,TTF::Font::Blended,bgc); break;
		case (Solid) : return _font->render(text,c,TTF::Font::Solid,bgc); break;
		default : Log << nl << " Font::render(...) => Rendermode not recognized, using Solid";
		}
		return _font->render(text,c,TTF::Font::Solid,bgc);
	}
	//Problem before if the if didnt returned...
	//TODO : rendering using defaultFont
	return new RGBSurface();
	
}

	//Attributes Access
void Font::byteSwapUNICODE(bool swapped)
	{
		//if TTF is linked, we try to call byteswapUNICODE...
		if (TTF::isLinked() )
			TTF::Font::byteSwapUNICODE(swapped);
		else
			Log << nl << "Warning : Font::byteSwapUNICODE => This TTF Feature is not available.";
	}

	Font::Style Font::getStyle()
	{
		if (_font != NULL )
		{
			switch (_font->getStyle())
			{
			case (TTF::Font::Normal) : return Normal; break;
			case (TTF::Font::Bold) : return Bold; break;
			case (TTF::Font::Italic) : return Italic; break;
			case (TTF::Font::Underline) : return Underline; break;
			default : Log << nl << "Font::getStyle() -> Internal TTF::Font::Style not identified. This shouldnt happen !!! -> returning 'Normal'";
			}
			return Normal;
		}
		
		//Default Style is normal
		Log << nl << "Warning : Font::getStyle => This TTF Feature is not available. Default Style is Normal";
		return Normal;
	}

	void Font::setStyle(Style s)
	{
		if (_font != NULL )
		{
			switch (s)
			{
			case (Normal) : _font->setStyle(TTF::Font::Normal); break;
			case (Bold) :  _font->setStyle(TTF::Font::Bold); break;
			case (Italic) : _font->setStyle(TTF::Font::Italic); break;
			case (Underline) : _font->setStyle(TTF::Font::Underline); break;
			default : Log << nl << "Font::setStyle(Font::Style) -> Font::Style passed not usable in TTF::Font. -> Ignoring call.";
			}
		}
			
		else
			Log << nl << "Warning : Font::setStyle => This TTF Feature is not available. Default Style is Normal";
	}
	
	int Font::height()
	{
		if (_font != NULL )
			return _font->height();
		Log << nl << "Warning : Font::height() => This TTF Feature is not available.";
		return 0;
	}

	int Font::ascent()
	{
		
		if (_font != NULL )
			return _font->ascent();
		Log << nl << "Warning : Font::ascent() => This TTF Feature is not available.";
		return 0;
	}

	int Font::descent()
	{
		
		if (_font != NULL )
			return _font->descent();
		Log << nl << "Warning : Font::descent() => This TTF Feature is not available.";
		return 0;
	}

	int Font::lineskip()
	{
		
		if (_font != NULL )
			return _font->lineskip();
		Log << nl << "Warning : Font::lineskip() => This TTF Feature is not available.";
		return 0;
	}

	long Font::faces()
	{
		
		if (_font != NULL )
			return _font->faces();
		Log << nl << "Warning : Font::faces() => This TTF Feature is not available.";
		return 0;
	}

	bool Font::faceIsFixedWidth()
	{
		
		if (_font != NULL )
			return _font->faceIsFixedWidth();
		Log << nl << "Warning : Font::faceIsFixedWidth() => This TTF Feature is not available.";
		return false;
	}

	std::string Font::faceFamilyName()
	{
		if (_font != NULL )
			return _font->faceFamilyName();
		Log << nl << "Warning : Font::faceFamilyName() => This TTF Feature is not available.";
		return "";
	}

	std::string Font::faceStyleName()
	{
		if (_font != NULL )
			return _font->faceStyleName();
		Log << nl << "Warning : Font::faceStyleName() => This TTF Feature is not available.";
		return "";
	}

	Rect Font::size(std::string text)
	{
		if (_font != NULL )
			return _font->size(text);
		Log << nl << "Warning : Font::size(string text) => This TTF Feature is not available.";
		return Rect();
	}



}
}
