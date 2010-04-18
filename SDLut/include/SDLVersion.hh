#ifndef SDL_VERSION_HH
#define SDL_VERSION_HH

/**
 * \class Version
 *
 * \ingroup SDLut
 *
 * \brief This class provides access to both linked and compiled SDL versions and specific CPU features check...
 *
 * \author Alex
 *
 * \date 2005/12/26
 *
 * Contact: asmodehn@gna.org
 *
 * TODO : Replace Version structure by the same stuff than SDL version ( macros )
 *
 */

#include "Logger.hh"

//declaring SDL_type for late binding
struct SDL_version;


namespace SDLut
{

class Version
{

    SDL_version* _compiled;
    SDL_version* _linked;

public:


    ///Enum types for different modules.
    ///Except Main, all other modules are optional, and provide additional features, but are not strictly required for SDLut to work.
    typedef enum
    {
        Main,
        Image,
        TTF,
        Mixer,
        Net
    }Component;

    ///Constructor
    Version(Component c);
    ///Destructor
    ~Version();

    ///Get Major component of the compiled version number Major.Minor.Patch
    int getcompiledmajor() const;
    ///Get Minor component of the compiled version number Major.Minor.Patch
    int getcompiledminor() const;
    ///Get Patch component of the compiled version number Major.Minor.Patch
    int getcompiledpatch() const;

    ///Get Major component of the linked version number Major.Minor.Patch
    int getlinkedmajor() const;
    ///Get Minor component of the linked version number Major.Minor.Patch
    int getlinkedminor() const;
    ///Get Patch component of the linked version number Major.Minor.Patch
    int getlinkedpatch() const;


    ///check if link and compiled matches
    bool check() const;

    ///Friend function to output to the Logger
    friend RAGE::Logger & operator << (RAGE::Logger& log, const Version & v);
};

}

#endif
