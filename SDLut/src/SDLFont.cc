#include "SDLFont.hh"

#include "SDLConfig.hh"
#include "SDLResources.inc"



namespace RAGE
{
namespace SDL
{
	/////////////////////////////////
	// DEFAULT FONT IMPLEMENTATION //
	/////////////////////////////////
	
//Class implementing the default font character render (with alpha masks)
	class FontImpl
	{

		//this version keeps the right value for render
		const RGBSurface _fontsurf;

		//all the rectangles become {0,0,0,0} on render for some reason
		std::vector<Rect> alphalookup;
		
		public :
			
		 //image 16x14 character, 225x225 pixels (all start at 0, not 1)
			FontImpl()  throw (std::logic_error);
			FontImpl(const FontImpl & font);
			virtual ~FontImpl();
		
			virtual Rect getSize(const std::string & text);

			virtual Font::Style getStyle() { return Font::Default;}
			virtual void setStyle(Font::Style s) { } //does nothing only one style available in default mode.
			
			//Rendering
			//bgc is used only if mode == shaded. Otherwise it s transparent
			virtual SDL_Surface * render(const std::string & text,Color c, Color bgc = Color(), Font::RenderMode mode = Font::Solid ) const;
		
	};

	FontImpl::FontImpl()  throw (std::logic_error)
			try: _fontsurf(RWOps(_defaultFont,sizeof(_defaultFont))), alphalookup()
			{
			//building alphalookup
				for (int line = 0; line < 14; line++)
				{
					for (int col = 0; col < 16; col++)
					{
						alphalookup.push_back(Rect(col * 14, line*16, 14,16));
					}
				}
			}
			catch (std::exception& e)
			{
				Log << nl << "Exception caught in internal FontImpl constructor : " << e.what();
			};

			Rect FontImpl::getSize(const std::string & text)
			{
			//number of lines in text -> todo

			//number of character max per line
				Rect r(text.size() * 14,16);
				return r;
			}

			FontImpl::FontImpl(const FontImpl & font) : _fontsurf(font._fontsurf)
			{
				alphalookup.assign(font.alphalookup.begin(),font.alphalookup.end());
			}

			FontImpl::~FontImpl()
			{
				alphalookup.clear();
			}

			SDL_Surface * FontImpl::render(const std::string & text,Color c, Color bgc, Font::RenderMode mode) const
			{
			//TODO
//  			SDL_Surface * result = SDL_CreateRGBSurface(RGBFlags, getSize(text).getw(), getSize(text).geth(), 16, r_default_mask, g_default_mask, b_default_mask, a_default_mask);
// 			for (unsigned int i= 0; i< text.size(); i++)
// 			{
// 				result->blit(_fontsurf,Rect(0,i*14,14,16),alphalookup[text[i]]);
// 				return NULL;
// 			}
// 			return result;
			}


			
	/////////////////////////////
	// TTF FONT IMPLEMENTATION //
	/////////////////////////////
	
//if SDL_TTF used, provide a class to be used as a bridge.
//this way the client doesnt have to take care of which function is available
#ifdef HAVE_SDLTTF

	class FontExtend : public FontImpl
	{
		//shared between copies of the same instance
		TTF_Font * _ttfstruct;
		int _ref;

		public:
			//Constructor
			FontExtend(std::string filename, int ptsize) throw (std::logic_error);
			
			//Copy Constructor
			//copy completely the content of *_ttfstruct
			FontExtend(const FontExtend & );
			//Assignement operator
			FontExtend & operator=(const FontExtend &);

			//Destructor
			~FontExtend();


			//Attributes Access
			static void byteSwapUNICODE(bool swapped);

			Font::Style getStyle();
			void setStyle(Font::Style s);
			
			int height();
			int ascent();
			int descent();
			int lineskip();
			long faces();
			bool faceIsFixedWidth();
			std::string faceFamilyName();
			std::string faceStyleName();
			
			Rect size(std::string text);

			//The Background color is used only if RenderMode = Shaded otherwise the background is transparent.
			SDL_Surface * render(const std::string& text, Color c, Color bgc = Color(), Font::RenderMode mode = Font::Solid) const;
	};


//Implementation of class Font
	FontExtend::FontExtend(std::string filename, int ptsize) throw (std::logic_error)
			try : FontImpl(),_ttfstruct(TTF_OpenFont(filename.c_str(),ptsize)), _ref(1)
		{
			if(_ttfstruct==NULL) {
				throw std::logic_error("TTF_OpenFont Error : " + Optional::GetError(Optional::TTF));
			}
		}
		catch (std::exception& e)
		{
			Log << nl << "Exception catched in internal FontExtent Constructor :"  << nl <<
					e.what() << std::endl;
		            //TODO : much more explicit error message...
		};

		FontExtend::FontExtend(const FontExtend & font)
		{
			++_ref;
			_ttfstruct = font._ttfstruct;
		}

		FontExtend::~FontExtend()
		{
			--_ref;
			if (_ref == 0)
				TTF_CloseFont(_ttfstruct), _ttfstruct=NULL;
		}

		SDL_Surface * FontExtend::render(const std::string& text, Color c, Color bgc, Font::RenderMode mode) const
		{
			SDL_Surface * surf;
			switch ( mode )
			{
				case Font::Blended : surf=TTF_RenderText_Blended(_ttfstruct,text.c_str(), c.get_SDL()); break;
				case Font::Shaded : surf=TTF_RenderText_Shaded(_ttfstruct,text.c_str(),c.get_SDL(), bgc.get_SDL()); break;
				case Font::Solid :
				default: surf=TTF_RenderText_Solid(_ttfstruct,text.c_str(), c.get_SDL()); break;
			}
			return surf;
		}

		//Attributes Access
		void FontExtend::byteSwapUNICODE(bool swapped)
		{
			TTF_ByteSwappedUNICODE(swapped);
		}

		Font::Style FontExtend::getStyle()
		{
			switch (TTF_GetFontStyle(_ttfstruct))
			{
				case TTF_STYLE_NORMAL : return Font::Normal; break;
				case TTF_STYLE_BOLD : return Font::Bold; break;
				case TTF_STYLE_ITALIC : return Font::Italic; break;
				case TTF_STYLE_UNDERLINE :return Font::Underline; break;
			}
			return Font::Default;
		}

		void FontExtend::setStyle(Font::Style s)
			{
				switch (s)
				{
					case Font::Normal : TTF_SetFontStyle(_ttfstruct,TTF_STYLE_NORMAL); break;
					case Font::Bold : TTF_SetFontStyle(_ttfstruct,TTF_STYLE_BOLD); break;
					case Font::Italic : TTF_SetFontStyle(_ttfstruct,TTF_STYLE_ITALIC); break;
					case Font::Underline : TTF_SetFontStyle(_ttfstruct,TTF_STYLE_UNDERLINE); break;
					case Font::Default : //TODO : Implement using parent class
						default : break;
				}
			}

			
			int FontExtend::height()
			{
				return TTF_FontHeight(_ttfstruct);
			}

			int FontExtend::ascent()
			{
				return TTF_FontAscent(_ttfstruct);
			}

			int FontExtend::descent()
			{
				return TTF_FontDescent(_ttfstruct);
			}

			int FontExtend::lineskip()
			{
				return TTF_FontLineSkip(_ttfstruct);
			}

			long FontExtend::faces()
			{
				return TTF_FontFaces(_ttfstruct);
			}

			bool FontExtend::faceIsFixedWidth()
			{
				return TTF_FontFaceIsFixedWidth(_ttfstruct) != 0 ;
			}

			std::string FontExtend::faceFamilyName()
			{
				return std::string( TTF_FontFaceFamilyName(_ttfstruct) );
			}

			std::string FontExtend::faceStyleName()
			{
				return std::string( TTF_FontFaceStyleName(_ttfstruct) );
			}

			Rect FontExtend::size(std::string text)
			{
				int w,h;
				int test = TTF_SizeText(_ttfstruct,text.c_str(),&w,&h);
				if (!test) //success
					return Rect(w,h);
				//failure
				Log << nl << Optional::GetError(Optional::TTF);
				return Rect(0,0);
			}


#endif //HAVE_SDLTTF


	///////////////////////////////////
	// INTERFACE FONT IMPLEMENTATION //
	///////////////////////////////////


	Font::Font(std::string filename, int ptsize) throw (std::logic_error)

#ifdef HAVE_SDLTTF
			try : _font( new FontExtend(filename,ptsize))
#else
			try : _font( new FontImpl(filename,ptsize))
#endif
{
	if(_font==NULL) {
		throw std::logic_error("Font Support not available");
    }
}
catch (std::exception& e)
{
	Log << nl << "Exception catched in Font Constructor :"  << nl <<
            e.what() << std::endl;
            //TODO : much more explicit error message...
};

//Copy Constructor
Font::Font(const Font &font)
: _font(font._font)
{
}


	Font::~Font()
{
	delete _font, _font=NULL;
}


RGBSurface * Font::render(std::string text, Color c, RenderMode mode, Color bgc) const
{
	return new RGBSurface(_font->render(text,c,bgc,mode));
}

	Font::Style Font::getStyle()
	{
		return _font->getStyle();
	}

	void Font::setStyle(Style s)
	{
		_font->setStyle(s);
	}
	



}
}
