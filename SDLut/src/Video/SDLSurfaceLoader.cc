#include "Video/SDLSurfaceLoader.hh"
#include "SDLConfig.hh"

#include "SDLResources.inc"

namespace RAGE
{
namespace SDL
{

SurfaceLoader::SurfaceLoader()
try :
    opengl(false),
    RGBFlags(SDL_SWSURFACE),
    errorContent(_defaultImage,sizeof(_defaultImage)),
    offset(errorContent.tell())
{

}
catch (std::exception &e)
{
    Log << nl << "Exception in SurfaceLoader Constructor !"  << nl <<
    e.what() << nl << GetError() << std::endl;
    //TODO : much more explicit error message...
}

SurfaceLoader::SurfaceLoader( const SurfaceLoader& sl)
try :
    opengl(sl.opengl),
    RGBFlags(sl.RGBFlags),
    errorContent(sl.errorContent),
    offset(sl.offset)
{

}
catch (std::exception &e)
{
    Log << nl << "Exception in SurfaceLoader Copy Constructor !"  << nl <<
    e.what() << nl << GetError() << std::endl;
    //TODO : much more explicit error message...
}

SurfaceLoader::~SurfaceLoader()
{
}

void SurfaceLoader::resetFlags(	bool SWSURFACE,
                                bool HWSURFACE,
                                bool SRCCOLORKEY,
                                bool SRCALPHA )
{
    if ( SWSURFACE )
        RGBFlags|= SDL_SWSURFACE;
    else
        RGBFlags&= (~SDL_SWSURFACE);
    if ( HWSURFACE )
        RGBFlags|= SDL_HWSURFACE;
    else
        RGBFlags&= (~SDL_HWSURFACE);
    if ( SRCCOLORKEY )
        RGBFlags|= SDL_SRCCOLORKEY;
    else
        RGBFlags&= (~SDL_SRCCOLORKEY);
    if ( SRCALPHA )
        RGBFlags|= SDL_SRCALPHA;
    else
        RGBFlags&= (~SDL_SRCALPHA);
}

void SurfaceLoader::resetOpengl(bool ogl )
{
    opengl = ogl;
}

//creates surface from file, copying its content...
std::auto_ptr<RGBSurface> SurfaceLoader::load(std::string filename , bool no_failure ) throw (std::logic_error)
{
    std::auto_ptr<RGBSurface> surf;
    try
    {
#ifdef WK_SDLIMAGE_FOUND
        SDL_Surface * sdlsurf = IMG_Load(filename.c_str());
#else
        SDL_Surface * sdlsurf = SDL_LoadBMP(filename.c_str());
#endif

        if ( opengl )
        {
            surf.reset(new GLSurface( sdlsurf ) );
        }
        else
        {
            surf.reset(new RGBSurface( sdlsurf ) );
        }

    }
    catch (std::exception &e)
    {
        Log << nl << "Exception catched in SurfaceLoader::Load() !"  << nl <<
        e.what() << nl << GetError();
        //TODO : much more explicit error message...

        if (no_failure) return load(errorContent);
        else throw;
    }
    return surf;
}


std::auto_ptr<RGBSurface> SurfaceLoader::load(std::string filename, const RGBAColor & colorKey, bool no_failure ) throw ( std::logic_error)
{
    std::auto_ptr<RGBSurface> surf;
    try
    {
#ifdef WK_SDLIMAGE_FOUND
        SDL_Surface * sdlsurf = IMG_Load(filename.c_str());
#else
        SDL_Surface * sdlsurf = SDL_LoadBMP(filename.c_str());
#endif

        if ( opengl )
        {
            surf.reset(new GLSurface( sdlsurf ) );
        }
        else
        {
            surf.reset(new RGBSurface( sdlsurf ) );
        }

        surf->setColorKeyAndAlpha(colorKey);

    }
    catch (std::exception &e)
    {
        Log << nl << "Exception catched in SurfaceLoader::Load() !" << nl <<
        e.what() << nl << GetError();
        //TODO : much more explicit error message...

        if (no_failure) return load(errorContent);
        else throw;
    }

    return surf;

}

//creates a surface from a RWOps containing a image.
std::auto_ptr<RGBSurface> SurfaceLoader::load(RWOps & rwops) throw(std::logic_error) //TODO : add optional format
{
    std::auto_ptr<RGBSurface> surf;
    try
    {
#ifdef WK_SDLIMAGE_FOUND
        SDL_Surface * sdlsurf = IMG_Load_RW(const_cast<SDL_RWops*>(rwops.get_pSDL()),0);

#else
        SDL_Surface * sdlsurf = SDL_LoadBMP_RW(const_cast<SDL_RWops*>(rwops.get_pSDL()),0);
#endif

        if ( opengl )
        {
            surf.reset(new GLSurface( sdlsurf ) );
        }
        else
        {
            surf.reset(new RGBSurface( sdlsurf ) );
        }


        //We put back the RWOps read cursor at the beginning ( needed after load... )
        offset = rwops.seek(0,RWOps::Set);

    }
    catch (std::exception &e)
    {
        Log << nl << "Exception catched in SurfaceLoader::Load() !" << nl <<
        e.what() << nl << GetError();
        //TODO : much more explicit error message...
        throw;
    }
    return surf;
}

//convert creates a new RGBSurface
std::auto_ptr<RGBSurface> SurfaceLoader::copyconvert(const RGBSurface & s, const PixelFormat & pfmt, bool no_failure ) throw (std::logic_error)
{
    std::auto_ptr<RGBSurface> surf;
    SDL_Surface * cvtsurf = SDL_ConvertSurface(const_cast<SDL_Surface *>(s.get_pSDL()),const_cast<SDL_PixelFormat *>( pfmt._pformat ),RGBFlags);

    if ( cvtsurf == NULL) // convert error
    {
        if (no_failure) return load(errorContent);
        else throw std::logic_error("Conversion error ! ");
    }

    if ( opengl )
    {
        surf.reset( new GLSurface(cvtsurf));
    }
    else
    {
        surf.reset( new RGBSurface(cvtsurf));
    }

    return surf;
}


} //SDL

} // RAGE
