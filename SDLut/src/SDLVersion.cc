#include "SDLVersion.hh"
#include "SDLConfig.hh"

using namespace Core;

namespace SDLut
{

#define NOVERSION _compiled->major = 0;_compiled->minor = 0;_compiled->patch = 0;_linked->major = 0;_linked->minor = 0;_linked->patch = 0;

Version::Version(Version::Component c)
{
#ifdef DEBUG
    Log << nl << "Version::Version() called ...";
#endif
    _compiled = new SDL_version();
    _linked = new SDL_version();

    switch (c)
    {
    case Main :
        SDL_VERSION(_compiled);
        _linked->major = SDL_Linked_Version()->major;
        _linked->minor = SDL_Linked_Version()->minor;
        _linked->patch = SDL_Linked_Version()->patch;
        break;
    case TTF :
#ifdef WK_SDLTTF_FOUND
        TTF_VERSION(_compiled);
        _linked->major = TTF_Linked_Version()->major;
        _linked->minor = TTF_Linked_Version()->minor;
        _linked->patch = TTF_Linked_Version()->patch;
#else
        NOVERSION
#endif
        break;
    case Image :
#ifdef WK_SDLIMAGE_FOUND
        SDL_IMAGE_VERSION(_compiled);
        _linked->major = IMG_Linked_Version()->major;
        _linked->minor = IMG_Linked_Version()->minor;
        _linked->patch = IMG_Linked_Version()->patch;
#else
        NOVERSION
#endif
        break;
    case Mixer :
#ifdef WK_SDLMIXER_FOUND
        SDL_MIXER_VERSION(_compiled);
        _linked->major = Mix_Linked_Version()->major;
        _linked->minor = Mix_Linked_Version()->minor;
        _linked->patch = Mix_Linked_Version()->patch;
#else
        NOVERSION
#endif
        break;

    case Net :
#ifdef WK_SDLNET_FOUND
        SDL_NET_VERSION(_compiled);
        _linked->major = SDLNet_Linked_Version()->major;
        _linked->minor = SDLNet_Linked_Version()->minor;
        _linked->patch = SDLNet_Linked_Version()->patch;
#else
        NOVERSION
#endif
        break;

    }

#ifdef DEBUG

    Log << nl << "Version::Version() done.";
#endif

}

Version::~Version()
{
#ifdef DEBUG
    Log << nl << "Version::~Version() called ...";
#endif

    delete _compiled;
    delete _linked;

#ifdef DEBUG

    Log << nl << "Version::~Version() done.";
#endif

}
int Version::getcompiledmajor() const
{
    return _compiled->major;
}
int Version::getcompiledminor() const
{
    return _compiled->minor;
}
int Version::getcompiledpatch() const
{
    return _compiled->patch;
}

int Version::getlinkedmajor() const
{
    return _linked->major;
}
int Version::getlinkedminor() const
{
    return _linked->minor;
}
int Version::getlinkedpatch() const
{
    return _linked->patch;
}

//check if link and compiled matches
bool Version::check() const
{
#if SDL_VERSION_ATLEAST(1, 2, 0)
    Log << nl << "Compiled with SDL 1.2 or newer" << std::endl;
#else

    Log << nl << "Compiled with SDL older than 1.2" << std::endl;
#endif

    return (_linked->major == _compiled->major) && (_linked->minor == _compiled->minor) && (_linked->patch == _compiled->patch);
}

Core::Logger & operator << (Core::Logger& log, const Version & v)
{
    log << nl <<"Compiled version: "<< v.getcompiledmajor() <<"."<< v.getcompiledminor() <<"."<< v.getcompiledpatch();
    log << nl << "Linked version: " << v.getcompiledmajor() <<"."<< v.getcompiledminor() <<"."<< v.getcompiledpatch();
    return log;
}



}
