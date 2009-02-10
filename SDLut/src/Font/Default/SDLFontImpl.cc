#include "SDLFontImpl.hh"

#include "SDLConfig.hh"
#include "SDLResources.inc"

namespace RAGE
{
namespace SDL
{
	FontImpl::FontImpl()  throw (std::logic_error)
			try: _fontsurf(RWOps(_defaultFont,sizeof(_defaultFont)))//, alphalookup()
			{
			//building alphalookup
			/*	for (int line = 0; line < 14; line++)
				{
					for (int col = 0; col < 16; col++)
					{
						alphalookup.push_back(Rect(col * 14, line*16, 14,16));
					}
				}
			*/
			}
			
			catch (std::exception& e)
			{
				Log << nl << "Exception caught in internal FontImpl constructor : " << e.what();
			}
			
			std::map<char, Rect> FontImpl::InitAlphaLookup()
			{
				std::map<char, Rect> result;

			#define ASSOCIATE( key, x, y ) result[key] = Rect( 14 * x, 16 * y, 14, 16 );
			#include "SDLFontLookup.inl"
			#undef ASSOCIATE
			
				return result;
			}

			std::map<char, Rect> FontImpl::alphalookup = FontImpl::InitAlphaLookup();

			Rect FontImpl::getSize(const std::string & text) const
			{
			//number of lines in text -> todo

			//number of character max per line
				Rect r(text.size() * 14,16);
				return r;
			}

			int FontImpl::height()
			{ 
				return 0;
			}

			FontImpl::FontImpl(const FontImpl & font) : _fontsurf(font._fontsurf)
			{
				
			}

			FontImpl::~FontImpl()
			{
				alphalookup.clear();
			}

			std::auto_ptr<RGBSurface> FontImpl::render(const std::string & text,Color c, Color bgc, Font::RenderMode mode) const
			{
				//TODO : redo using SDLut wrapper for surfaces...
				std::auto_ptr<RGBSurface> result( new RGBSurface( getSize(text).getw(), getSize(text).geth(), 16) );
				//std::auto_ptr<SDL_Surface> result(SDL_CreateRGBSurface(SDL_SWSURFACE, getSize(text).getw(), getSize(text).geth(), 16, BaseSurface::r_default_mask, BaseSurface::g_default_mask, BaseSurface::b_default_mask, BaseSurface::a_default_mask));
				//Log << getSize(text);
				for (unsigned int i= 0; i< text.size(); i++)
				{
					//TODO : fix the lookup
								
					result->blit(_fontsurf, Rect(i*14,0,14,16),alphalookup[text[i]]);
					//SDL_BlitSurface(const_cast<SDL_Surface*>(&_fontsurf.get_rSDL()),const_cast<SDL_Rect*>(alphalookup[text[i]].get_pSDL()),result.get(),const_cast<SDL_Rect*>(Rect(0,i*14,14,16).get_pSDL()));
				}
				return result;//beware : ownership transferred for auto_ptr
			}
}
}
