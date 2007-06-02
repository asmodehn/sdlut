#include "SDLFontImpl.hh"

#include "SDLConfig.hh"
#include "SDLResources.inc"

namespace RAGE
{
namespace SDL
{
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
}
}
