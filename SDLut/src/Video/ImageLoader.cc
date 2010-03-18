#include "Video/ImageLoader.hh"
#include "SDLConfig.hh"

#include "SDLResources.inc"

namespace RAGE
{
namespace SDL
{

ImageLoader::ImageLoader()
try :
    pvm_RGBFlags(SDL_SWSURFACE),
    pvm_errorContent(_defaultImage,sizeof(_defaultImage)),
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
    std::auto_ptr<RGBSurface> surf;
    try
    {
#ifdef WK_SDLIMAGE_FOUND
        SDL_Surface * sdlsurf = IMG_Load(filename.c_str());
#else
        SDL_Surface * sdlsurf = SDL_LoadBMP(filename.c_str());
#endif

#ifdef WK_OPENGL_FOUND
            surf.reset(new GLSurface( sdlsurf ) );
#else
            surf.reset(new RGBSurface( sdlsurf ) );
#endif

    }
    catch (std::exception &e)
    {
        Log << nl << "Exception catched in SurfaceLoader::Load() !"  << nl <<
        e.what() << nl << GetError();
        //TODO : much more explicit error message...

        if (no_failure)

#ifdef WK_SDLIMAGE_FOUND
        surf.reset(new GLSurface(pvm_errorContent));
#else
surf.reset(new RGBSurface(pvm_errorContent));
#endif
        else throw;
    }
    return std::auto_ptr<Image> (new Image(surf));
}


std::auto_ptr<Image> ImageLoader::load(std::string filename, const Color & colorKey, bool no_failure ) throw ( std::logic_error)
{
#ifdef WK_OPENGL_FOUND
    std::auto_ptr<GLSurface> surf;
#else
    std::auto_ptr<RGBSurface> surf;
#endif

    try
    {
#ifdef WK_SDLIMAGE_FOUND
        SDL_Surface * sdlsurf = IMG_Load(filename.c_str());
#else
        SDL_Surface * sdlsurf = SDL_LoadBMP(filename.c_str());
#endif

#ifdef WK_OPENGL_FOUND
            surf.reset(new GLSurface( sdlsurf ) );
#else
            surf.reset(new RGBSurface( sdlsurf ) );
#endif

        //TOFIX : makes all image transparent
        surf->setColorKey(surf->getPixelFormat().getPixelColor(colorKey));

    }
    catch (std::exception &e)
    {
        Log << nl << "Exception catched in SurfaceLoader::Load() !" << nl <<
        e.what() << nl << GetError();
        //TODO : much more explicit error message...

        if (no_failure)
        {
#ifdef WK_SDLIMAGE_FOUND
        surf.reset(new GLSurface(pvm_errorContent));
#else
surf.reset(new RGBSurface(pvm_errorContent));
#endif
        }
        else throw;
    }
    return std::auto_ptr<Image> (new Image(surf));
}

//convert creates a new RGBSurface
std::auto_ptr<Image> ImageLoader::copyconvert(const Image & s, const PixelFormat & pfmt, bool no_failure ) throw (std::logic_error)
{
    std::auto_ptr<RGBSurface> surf;
    SDL_Surface * cvtsurf = SDL_ConvertSurface(const_cast<SDL_Surface *>(s.m_img->get_pSDL()),const_cast<SDL_PixelFormat *>( pfmt.ptm_sdl_pformat ),pvm_RGBFlags);

    if ( cvtsurf == NULL) // convert error
    {
        if (no_failure)
        {

#ifdef WK_SDLIMAGE_FOUND
        surf.reset(new GLSurface(pvm_errorContent));
#else
surf.reset(new RGBSurface(pvm_errorContent));
#endif
            return std::auto_ptr<Image>(new Image(surf));
        }
        else throw std::logic_error("Conversion error ! ");
    }

#ifdef WK_OPENGL_FOUND
            surf.reset(new GLSurface( cvtsurf ) );
#else
            surf.reset(new RGBSurface( cvtsurf ) );
#endif

    return std::auto_ptr<Image> (new Image(surf));
}


} //SDL

} // RAGE

