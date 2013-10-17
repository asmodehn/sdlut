#include "SDLFontImpl.hh"

#include "Video/internal/SDLRGBSurface.hh"
#include "Video/internal/OpenGL/SDLGLSurface.hh"

#include "SDLConfig.hh"
#include "SDLResources.inc"

using namespace Core;

namespace SDLut
{
namespace font
{
FontImpl::FontImpl()  throw (std::logic_error)
try:
    pvm_fontsurf(0)
{
    system::RWOps res(resources::_defaultFont,sizeof(resources::_defaultFont));
    pvm_fontsurf.reset(new video::internal::RGBSurface(res));
    //checking initialized font
    if ( ( pvm_fontsurf.get() == 0 ) || ( ! pvm_fontsurf->initialized() ) )
    {
        throw std::logic_error("Error initializing default Font !");
    }
}
catch (std::exception& e)
{
    Log << nl << "Exception caught in internal FontImpl constructor : " << e.what();
}

std::map<char, video::Rect> FontImpl::InitAlphaLookup()
{
    std::map<char, video::Rect> result;
#define ASSOCIATE( key, x, y ) result[key] = video::Rect( 14 * x, 16 * y, 14, 16 );
#include "SDLFontLookup.inl"
#undef ASSOCIATE

    return result;
}

std::map<char, video::Rect> FontImpl::alphalookup = FontImpl::InitAlphaLookup();

video::Rect FontImpl::getSize(const std::string & text) const
{
    //number of lines in text -> todo
    //number of character max per line
    video::Rect r(0,0,text.size() * 14,16);
    return r;
}

int FontImpl::height()
{
    return 16;
}

FontImpl::FontImpl(const FontImpl & font) throw (std::logic_error)
try :
    pvm_fontsurf(0)
{
    //deep copy of the RGB Surface
    pvm_fontsurf.reset( new video::internal::RGBSurface(*(font.pvm_fontsurf)) );
    if ( pvm_fontsurf.get() == 0 )
        throw std::logic_error("RGBSurface for fontsurf is NULL");
}
catch (std::exception& e)
{
    Log << nl << "Exception caught in internal FontImpl copy constructor : " << e.what();
}


FontImpl & FontImpl::operator=(const FontImpl & font) throw (std::logic_error)
{
    //deep copy of the RGB Surface
    pvm_fontsurf.reset( new video::internal::RGBSurface(*(font.pvm_fontsurf)) );
    if ( pvm_fontsurf.get() == 0 )
        throw std::logic_error("RGBSurface for fontsurf is NULL");

    return * this;
}

FontImpl::~FontImpl()
{

    //statically initialized, so we shouldnt clear here
    //alphalookup.clear();
}

std::auto_ptr<video::internal::RGBSurface> FontImpl::render(const std::string & text,video::Color c, video::Color bgc, Font::RenderMode mode) const
{

    std::auto_ptr<video::internal::RGBSurface> result( new video::internal::OGL::GLSurface( getSize(text).getw(), getSize(text).geth(), 16) );
    //std::auto_ptr<SDL_Surface> result(SDL_CreateRGBSurface(SDL_SWSURFACE, getSize(text).getw(), getSize(text).geth(), 16, BaseSurface::r_default_mask, BaseSurface::g_default_mask, BaseSurface::b_default_mask, BaseSurface::a_default_mask));
    //Log << getSize(text);
    for (unsigned int i= 0; i< text.size(); i++)
    {
        video::Rect src(i*14,0,14,16);
        result->blit(*pvm_fontsurf, src,alphalookup[text[i]]);
        //
        //TODO : better if we code that directly in SDL, as we wont be affected by other code parts changes...
        //
        //Rect txtrect = alphalookup[text[i]];
        //Log << nl << "Txtrect X : "<< txtrect.getx() << " Y : "<< txtrect.gety() << " W : " << txtrect.getw() << " H : " << txtrect.geth() ;
        //Log.flush();

        //Rect charrect(0,i*14,14,16);
        //Log << nl << "Charrect X : "<< charrect.getx() << " Y : "<< charrect.gety() << " W : " << charrect.getw() << " H : " << charrect.geth() ;
        //Log.flush();

        //BUG here : only first letter is blitted.. why ???
        //SDL_BlitSurface(const_cast<SDL_Surface*>(_fontsurf->get_pSDL()),
        //                const_cast<SDL_Rect*>(txtrect.get_pSDL()),
        //                const_cast<SDL_Surface*>(result->get_pSDL()),
        //                const_cast<SDL_Rect*>(charrect.get_pSDL()));

        //result->saveBMP( text + "_fimpl.bmp");

    }

    //beware : ownership transferred for auto_ptr
    return result;
}

}
}
