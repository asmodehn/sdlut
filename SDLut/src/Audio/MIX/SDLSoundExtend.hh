#ifndef SDLSOUNDEXTEND_HH
#define SDLSOUNDEXTEND_HH

#include "Audio/SDLSound.hh"
#include "SDLConfig.hh"

typedef struct Mix_Chunk Mix_Chunk;

namespace SDLut
{
namespace audio
{

//if SDL_Mixer is used, provide a class to be used as a bridge.
//this way the client doesnt have to take care of which function is available
#ifdef WK_SDLut_FOUND_SDLMIXER

class SoundExtend : public SoundIf
{
    std::auto_ptr<Mix_Chunk> pvm_chunk;

public:
    SoundExtend(std::string filename, bool loop_status = false) throw (std::logic_error);
    SoundExtend(const SoundExtend &) throw (std::logic_error);
    ~SoundExtend();

    bool isMusic()
    {
        return false;
    }
    bool isMIXImpl()
    {
        return true;
    }
    bool Convert( short unsigned int, short unsigned int, int )
    {
        return true;
    };

    Mix_Chunk& get_rMIX() const;
};
#endif
}
}
#endif
