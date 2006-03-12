#include "SDLFont.hh"



namespace RAGE
{
namespace SDL
{
Font::Font(std::string filename, int ptsize)
try : _font(TTF_OpenFont(filename.c_str(),ptsize))
{
	if(!_font) {
		throw("TTF_OpenFont: " + GetError(TTF));
    }
}
catch (std::exception& e)
{
	Log << nl << "Exception catched in Font Constructor :"  << nl <<
            e.what() << std::endl;
            //TODO : much more explicit error message...
};

Font::~Font()
{
	TTF_CloseFont(_font), _font=NULL;
}

SDL_Surface* Font::render(std::string text, Color c, RenderMode mode, Color bgc) const
{
	SDL_Surface * surf;
	switch ( mode )
	{
		case Blended : surf=TTF_RenderText_Blended(_font,text.c_str(), c.get_SDL()); break;
		case Shaded : surf=TTF_RenderText_Shaded(_font,text.c_str(),c.get_SDL(), bgc.get_SDL()); break;
		case Solid :
		default: surf=TTF_RenderText_Solid(_font,text.c_str(), c.get_SDL());
	}

	return surf;
}
}
}
