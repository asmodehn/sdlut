#ifndef SDLMUSICEXTEND_HH
#define SDLMUSICEXTEND_HH

#include "Audio/SDLMusic.hh"
#include "SDLConfig.hh"

typedef struct _Mix_Music Mix_Music;

namespace SDLut
{
namespace audio
{

//if SDL_Mixer is used, provide a class to be used as a bridge.
//this way the client doesnt have to take care of which function is available
#ifdef WK_SDLMIXER_FOUND

class MusicExtend : public MusicIf
{
    Mix_Music * pvm_music;

public:
    MusicExtend(std::string filename) throw (std::logic_error);
    MusicExtend(const MusicExtend &) throw (std::logic_error);
    ~MusicExtend();

    bool isMusic()
    {
        return true;
    }
    bool isMIXImpl()
    {
        return true;
    }
    bool Convert( short unsigned int, short unsigned int, int )
    {
        return true;
    };

    Mix_Music& get_rMIX() const;
};
#endif
}
}
#endif
