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



    typedef enum
    {
        Main,
        Image,
        TTF,
        Mixer,
        Net
    }Component;

    Version(Component c);
    ~Version();

    int getcompiledmajor() const;
    int getcompiledminor() const;
    int getcompiledpatch() const;
    int getlinkedmajor() const;
    int getlinkedminor() const;
    int getlinkedpatch() const;

    //check if link and compiled matches
    bool check() const;

    friend RAGE::Logger & operator << (RAGE::Logger& log, const Version & v);
};

}

#endif
