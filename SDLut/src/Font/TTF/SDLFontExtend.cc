#include "SDLFontExtend.hh"

#include "Video/SDLGLSurface.hh"

#include "SDLConfig.hh"

namespace RAGE
{
namespace SDL
{

//if SDL_TTF used, provide a class to be used as a bridge.
//this way the client doesnt have to take care of which function is available
#ifdef WK_SDLTTF_FOUND


FontExtend::FontExtend(std::string filename, int ptsize, long index) throw (std::logic_error)
try :
    FontImpl(), ptsize(ptsize), index(index),pvm_OriginalData(new RWOps(filename.c_str(), "rb")),_ttfstruct(TTF_OpenFontIndexRW(pvm_OriginalData->get_pSDL(),0,ptsize,index))
{
    if (_ttfstruct == NULL)
    {
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
try :
    FontImpl(font), ptsize(font.ptsize), index(font.index), pvm_OriginalData(font.pvm_OriginalData.get() !=0 ? new RWOps(*font.pvm_OriginalData) : 0),_ttfstruct(0)
{
    _ttfstruct = TTF_OpenFontIndexRW(pvm_OriginalData->get_pSDL(),0,ptsize,index);
    if (_ttfstruct == 0)
    {
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

std::auto_ptr<RGBSurface> FontExtend::render(const std::string& text, Color c, Color bgc, Font::RenderMode mode) const
{
    std::auto_ptr<SDL_Surface> surf;
    switch ( mode )
    {
    case Font::Blended :
        surf.reset(TTF_RenderText_Blended(_ttfstruct,text.c_str(), c.get_SDL()));
        break;
    case Font::Shaded :
        surf.reset(TTF_RenderText_Shaded(_ttfstruct,text.c_str(),c.get_SDL(), bgc.get_SDL()));
        break;
    case Font::Solid :
    default:
        surf.reset(TTF_RenderText_Solid(_ttfstruct,text.c_str(), c.get_SDL()));
        break;
    }


    GLSurface * glsurf = new GLSurface (surf);

    //glsurf->saveBMP( text + "_fext.bmp" );

    //beware : auto_ptr ownership transferred ;)
    std::auto_ptr<RGBSurface> result(glsurf );


    //result->saveBMP ( text + "_fextres.bmp");

    return result;
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
    case TTF_STYLE_NORMAL :
        return Font::Normal;
        break;
    case TTF_STYLE_BOLD :
        return Font::Bold;
        break;
    case TTF_STYLE_ITALIC :
        return Font::Italic;
        break;
    case TTF_STYLE_UNDERLINE :
        return Font::Underline;
        break;
    }
    return Font::Default;
}

void FontExtend::setStyle(Font::Style s)
{
    switch (s)
    {
    case Font::Normal :
        TTF_SetFontStyle(_ttfstruct,TTF_STYLE_NORMAL);
        break;
    case Font::Bold :
        TTF_SetFontStyle(_ttfstruct,TTF_STYLE_BOLD);
        break;
    case Font::Italic :
        TTF_SetFontStyle(_ttfstruct,TTF_STYLE_ITALIC);
        break;
    case Font::Underline :
        TTF_SetFontStyle(_ttfstruct,TTF_STYLE_UNDERLINE);
        break;
    case Font::Default : //TODO : Implement using parent class
    default :
        break;
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
        return Rect(0,0,w,h);
    //failure
    Log << nl << Optional::GetError(Optional::TTF);
    return Rect(0,0,0,0);
}

#endif //WK_SDLTTF_FOUND

}
}
