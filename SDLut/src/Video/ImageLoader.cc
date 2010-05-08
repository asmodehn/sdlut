#include "Video/ImageLoader.hh"
#include "SDLConfig.hh"

#include "SDLResources.inc"

using namespace Core;


namespace SDLut
{
namespace video
{

ImageLoader::ImageLoader()
try :
    pvm_RGBFlags(SDL_SWSURFACE),
    pvm_errorContent(resources::_defaultImage,sizeof(resources::_defaultImage)),
    pvm_offset(pvm_errorContent.tell())
{

}
catch (std::exception &e)
{
    Log << nl << "Exception in ImageLoader Constructor !"  << nl <<
    e.what() << nl << GetError() << std::endl;
    //TODO : much more explicit error message...
}

ImageLoader::ImageLoader( const ImageLoader& sl)
try :
    pvm_RGBFlags(sl.pvm_RGBFlags),
    pvm_errorContent(sl.pvm_errorContent),
    pvm_offset(sl.pvm_offset)
{

}
catch (std::exception &e)
{
    Log << nl << "Exception in ImageLoader Copy Constructor !"  << nl <<
    e.what() << nl << GetError() << std::endl;
    //TODO : much more explicit error message...
}

ImageLoader::~ImageLoader()
{
}

void ImageLoader::resetFlags(	bool SWSURFACE,
                              bool HWSURFACE,
                              bool SRCCOLORKEY,
                              bool SRCALPHA )
{

    if ( SWSURFACE )
        pvm_RGBFlags|= SDL_SWSURFACE;
    else
        pvm_RGBFlags&= (~SDL_SWSURFACE);
    if ( HWSURFACE )
        pvm_RGBFlags|= SDL_HWSURFACE;
    else
        pvm_RGBFlags&= (~SDL_HWSURFACE);
    if ( SRCCOLORKEY )
        pvm_RGBFlags|= SDL_SRCCOLORKEY;
    else
        pvm_RGBFlags&= (~SDL_SRCCOLORKEY);
    if ( SRCALPHA )
        pvm_RGBFlags|= SDL_SRCALPHA;
    else
        pvm_RGBFlags&= (~SDL_SRCALPHA);
}


//creates surface from file, copying its content...
std::auto_ptr<Image> ImageLoader::load(std::string filename , bool no_failure ) throw (std::logic_error)
{

#ifdef WK_SDLut_FOUND_OPENGL
    std::auto_ptr<internal::OGL::GLSurface> surf;
#else
    std::auto_ptr<internal::RGBSurface> surf;
#endif

    try
    {
#ifdef WK_SDLut_FOUND_SDLIMAGE
        SDL_Surface * sdlsurf = IMG_Load(filename.c_str());
#else
        SDL_Surface * sdlsurf = SDL_LoadBMP(filename.c_str());
#endif

#ifdef WK_SDLut_FOUND_OPENGL
        surf.reset(new internal::OGL::GLSurface( sdlsurf ) );
#else
        surf.reset(new internal::RGBSurface( sdlsurf ) );
#endif

    }
    catch (std::exception &e)
    {
        Log << nl << "Exception catched in SurfaceLoader::Load() !"  << nl <<
        e.what() << nl << GetError();
        //TODO : much more explicit error message...

        if (no_failure)

#ifdef WK_SDLut_FOUND_SDLIMAGE
            surf.reset(new internal::OGL::GLSurface(pvm_errorContent));
#else
            surf.reset(new internal::RGBSurface(pvm_errorContent));
#endif
        else throw;
    }
    return std::auto_ptr<Image> (new Image(surf));
}


std::auto_ptr<Image> ImageLoader::load(std::string filename, const Color & colorKey, bool no_failure ) throw ( std::logic_error)
{
#ifdef WK_SDLut_FOUND_OPENGL
    std::auto_ptr<internal::OGL::GLSurface> surf;
#else
    std::auto_ptr<internal::RGBSurface> surf;
#endif

    try
    {
#ifdef WK_SDLut_FOUND_SDLIMAGE
        SDL_Surface * sdlsurf = IMG_Load(filename.c_str());
#else
        SDL_Surface * sdlsurf = SDL_LoadBMP(filename.c_str());
#endif

#ifdef WK_SDLut_FOUND_OPENGL
        surf.reset(new internal::OGL::GLSurface( sdlsurf ) );
#else
        surf.reset(new internal::RGBSurface( sdlsurf ) );
#endif


        surf->resetColorKey(true,surf->getPixelFormat().getPixelColor(colorKey));

    }
    catch (std::exception &e)
    {
        Log << nl << "Exception catched in SurfaceLoader::Load() !" << nl <<
        e.what() << nl << GetError();
        //TODO : much more explicit error message...

        if (no_failure)
        {
#ifdef WK_SDLut_FOUND_SDLIMAGE
            surf.reset(new internal::OGL::GLSurface(pvm_errorContent));
#else
            surf.reset(new internal::RGBSurface(pvm_errorContent));
#endif
        }
        else throw;
    }
    return std::auto_ptr<Image> (new Image(surf));
}

//convert creates a new RGBSurface
std::auto_ptr<Image> ImageLoader::copyconvert(const Image & s, const internal::PixelFormat & pfmt, bool no_failure ) throw (std::logic_error)
{
    std::auto_ptr<internal::RGBSurface> surf;
    SDL_Surface * cvtsurf = SDL_ConvertSurface(const_cast<SDL_Surface *>(s.m_img->get_pSDL()),const_cast<SDL_PixelFormat *>( pfmt.ptm_sdl_pformat ),pvm_RGBFlags);

    if ( cvtsurf == NULL) // convert error
    {
        if (no_failure)
        {

#ifdef WK_SDLut_FOUND_SDLIMAGE
            surf.reset(new internal::OGL::GLSurface(pvm_errorContent));
#else
            surf.reset(new internal::RGBSurface(pvm_errorContent));
#endif
            return std::auto_ptr<Image>(new Image(surf));
        }
        else throw std::logic_error("Conversion error ! ");
    }

#ifdef WK_SDLut_FOUND_OPENGL
    surf.reset(new internal::OGL::GLSurface( cvtsurf ) );
#else
    surf.reset(new internal::RGBSurface( cvtsurf ) );
#endif

    return std::auto_ptr<Image> (new Image(surf));
}


} //SDL

} // SDLut

