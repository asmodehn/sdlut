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
		RGBSurface _fontsurf;

		//all the rectangles become {0,0,0,0} on render for some reason
		std::vector<Rect> alphalookup;
		
		public :
			
		 //image 16x14 character, 225x225 pixels (all start at 0, not 1)
			FontImpl()  throw (std::logic_error);
			FontImpl(const FontImpl & font);
			virtual ~FontImpl();
		
			virtual Rect getSize(const std::string & text) const;

			virtual Font::Style getStyle() { return Font::Default;}
			virtual void setStyle(Font::Style s) { } //does nothing only one style available in default mode.

			virtual bool isTTFImpl() const { return false; }
			//Rendering
			//bgc is used only if mode == shaded. Otherwise it s transparent
			virtual std::auto_ptr<SDL_Surface> render(const std::string & text,Color c, Color bgc = Color(), Font::RenderMode mode = Font::Solid ) const;
		
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
			}

			Rect FontImpl::getSize(const std::string & text) const
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

			std::auto_ptr<SDL_Surface> FontImpl::render(const std::string & text,Color c, Color bgc, Font::RenderMode mode) const
			{

				std::auto_ptr<SDL_Surface> result(SDL_CreateRGBSurface(SDL_SWSURFACE, getSize(text).getw(), getSize(text).geth(), 16, BaseSurface::r_default_mask, BaseSurface::g_default_mask, BaseSurface::b_default_mask, BaseSurface::a_default_mask));
				for (unsigned int i= 0; i< text.size(); i++)
				{
					SDL_BlitSurface(const_cast<SDL_Surface*>(&_fontsurf.get_rSDL()),const_cast<SDL_Rect*>(alphalookup[text[i]].get_pSDL()),result.get(),const_cast<SDL_Rect*>(Rect(0,i*14,14,16).get_pSDL()));
				}
				return result;//beware : ownership transferred for auto_ptr
			}


			
	/////////////////////////////
	// TTF FONT IMPLEMENTATION //
	/////////////////////////////
	
//if SDL_TTF used, provide a class to be used as a bridge.
//this way the client doesnt have to take care of which function is available
#ifdef HAVE_SDLTTF

	class FontExtend : public FontImpl
	{
		int ptsize;
		long index;
		std::auto_ptr<RWOps> pvm_OriginalData;
		TTF_Font * _ttfstruct;
		
		public:
			//Constructor
			FontExtend(std::string filename, int ptsize = 16, long index = 0) throw (std::logic_error);
			
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

			bool isTTFImpl() const { return true; }
			
			int height();
			int ascent();
			int descent();
			int lineskip();
			long faces();
			bool faceIsFixedWidth();
			std::string faceFamilyName();
			std::string faceStyleName();
			
			Rect getSize(const std::string& text) const;

			//The Background color is used only if RenderMode = Shaded otherwise the background is transparent.
			std::auto_ptr<SDL_Surface> render(const std::string& text, Color c, Color bgc = Color(), Font::RenderMode mode = Font::Solid) const;
	};

//Implementation of class Font
	FontExtend::FontExtend(std::string filename, int ptsize, long index) throw (std::logic_error)
		try : FontImpl(), ptsize(ptsize), index(index),pvm_OriginalData(new RWOps(filename.c_str(), "rb")),_ttfstruct(TTF_OpenFontIndexRW(pvm_OriginalData->get_pSDL(),0,ptsize,index))
		{
			if(_ttfstruct == NULL) {
				throw std::logic_error("TTF_OpenFont Error : " + Optional::GetError(Optional::TTF));
			}
			pvm_OriginalData->seek(0,RWOps::Set);
		}
		catch (std::exception& e)
		{
			Log << nl << "Exception catched in internal FontExtent Constructor :"  << nl <<
					e.what() << std::endl;
		            //TODO : much more explicit error message...
		}

		FontExtend::FontExtend(const FontExtend & font)
		try : FontImpl(font), ptsize(font.ptsize), index(font.index), pvm_OriginalData(font.pvm_OriginalData.get() !=0 ? new RWOps(*font.pvm_OriginalData) : 0),_ttfstruct(0)
		{
			_ttfstruct = TTF_OpenFontIndexRW(pvm_OriginalData->get_pSDL(),0,ptsize,index);
			if(_ttfstruct == 0) {
				throw std::logic_error("TTF_OpenFont Error : " + Optional::GetError(Optional::TTF));
			}
			pvm_OriginalData->seek(0,RWOps::Set);
		}
		catch (std::exception& e)
		{
			Log << nl << "Exception catched in internal FontExtent Copy Constructor :"  << nl <<
					e.what() << std::endl;
		            //TODO : much more explicit error message...
		}

		FontExtend::~FontExtend()
		{
			TTF_CloseFont(_ttfstruct);
		}

		std::auto_ptr<SDL_Surface> FontExtend::render(const std::string& text, Color c, Color bgc, Font::RenderMode mode) const
		{
			std::auto_ptr<SDL_Surface> surf;
			switch ( mode )
			{
				case Font::Blended : surf.reset(TTF_RenderText_Blended(_ttfstruct,text.c_str(), c.get_SDL())); break;
				case Font::Shaded : surf.reset(TTF_RenderText_Shaded(_ttfstruct,text.c_str(),c.get_SDL(), bgc.get_SDL())); break;
				case Font::Solid :
				default: surf.reset(TTF_RenderText_Solid(_ttfstruct,text.c_str(), c.get_SDL())); break;
			}
			return surf;//beware : auto_ptr ownership transferred ;)
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

			Rect FontExtend::getSize(const std::string & text) const
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

Font::Font() throw (std::logic_error)
try : _font( new FontImpl())
{
	if(!_font.get())
	{
		throw std::logic_error("Font Support not available");
	}
}
catch (std::exception& e)
{
	Log << nl << "Exception catched in Font Constructor :"  << nl <<
            e.what() << std::endl;
            //TODO : much more explicit error message...
}

Font::Font(std::string filename , int ptsize )
try : _font(0)
{
	bool ttfavailable = setTTF( filename, ptsize);
	if(!ttfavailable || !_font.get())
	{
		throw std::logic_error("Font Support not available");
	}
}
catch (std::exception& e)
{
	Log << nl << "Exception catched in Font Constructor :"  << nl <<
			e.what() << std::endl;
            //TODO : much more explicit error message...
}
		

//Copy Constructor
Font::Font(const Font &font)
	: _font(0)
{
	if (font._font.get() != 0 ) // should always be the case, just need to make sure with default and other constructors
	{
		if ( font.isTTFAvailable() )
		{
			//duplicated
			_font.reset(new FontExtend(static_cast<const FontExtend&>(*font._font)));
		}
		else
		{
			//duplicated
			_font.reset(new FontImpl(*font._font));
		}
	}
	
}


Font::~Font()
{
}


std::auto_ptr<RGBSurface> Font::render(std::string text, Color c, RenderMode mode, Color bgc) const
{
	return std::auto_ptr<RGBSurface>(new RGBSurface(_font->render(text,c,bgc,mode)));
}

	bool Font::setTTF(std::string filename, int ptsize)
	{
		bool changed = false;
#ifdef HAVE_SDLTTF
		try
		{
			_font.reset( new FontExtend(filename,ptsize) );
		}
		catch (std::exception& e)
		{
			Log << nl << "Error in TTF File Loading :"  << nl <<
					e.what() << std::endl;
		};

		changed = (_font.get() != 0);
#else
		Log << nl << "Feature not enabled. TTF loading is disabled.";
#endif
		return changed;
	}

	bool Font::isTTFAvailable() const
	{
		return _font->isTTFImpl();
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
