#include "SDLMusicExtend.hh"
#include "SDLConfig.hh"
using namespace Core;

namespace SDLut
{
namespace audio
{
#ifdef WK_SDLMIXER_FOUND
#pragma message ("SDL_Mixer Found. Compiling MusicExtend.")
MusicExtend::MusicExtend(std::string filename) throw (std::logic_error)
try :
    MusicIf(filename), pvm_music(Mix_LoadMUS(pvm_OriginalFilename.c_str()))
{
    if ( pvm_music == NULL )
    {
        throw std::logic_error(" Unable to open the sound file !");
    }

}
catch (std::exception &e )
{
    Log << nl << " Exception caught in MusicExtend::MusicExtend()";
    Log << nl << e.what();
}

MusicExtend::MusicExtend(const MusicExtend & s) throw (std::logic_error)
try :
    MusicIf(s), pvm_music(Mix_LoadMUS(pvm_OriginalFilename.c_str()))
{
    if ( pvm_music == NULL)
    {
        throw std::logic_error(" Unable to read the sound in memory !");
    }

}
catch (std::exception &e )
{
    Log << nl << " Exception caught in MusicExtend::MusicExtend( " << &s <<" )";
    Log << nl << e.what();
}

MusicExtend::~MusicExtend()
{
    Mix_FreeMusic(pvm_music);
}

Mix_Music& MusicExtend::get_rMIX() const
{
    return *pvm_music;
}

#endif
}
}
