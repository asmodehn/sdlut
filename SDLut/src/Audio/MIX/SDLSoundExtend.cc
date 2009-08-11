#include "SDLSoundExtend.hh"
#include "SDLConfig.hh"

namespace RAGE
{
namespace SDL
{
#ifdef WK_SDLMIXER_FOUND

SoundExtend::SoundExtend(std::string filename, bool loop_status) throw (std::logic_error)
try :
    SoundIf(filename, loop_status), pvm_chunk(Mix_LoadWAV_RW(pvm_OriginalData->get_pSDL(),0))
{
    if ( !pvm_chunk.get() )
    {
        throw std::logic_error(" Unable to open the sound file !");
    }
    pvm_OriginalData->seek(0,RWOps::Set);

}
catch (std::exception &e )
{
    Log << nl << " Exception caught in SoundExtend::SoundExtend()";
    Log << nl << e.what();
}

SoundExtend::SoundExtend(const SoundExtend & s) throw (std::logic_error)
try :
    SoundIf(s), pvm_chunk(Mix_LoadWAV_RW(pvm_OriginalData->get_pSDL(),0))
{
    if ( ! pvm_chunk.get() )
    {
        throw std::logic_error(" Unable to read the sound in memory !");
    }
    pvm_OriginalData->seek(0,RWOps::Set);

}
catch (std::exception &e )
{
    Log << nl << " Exception caught in SoundExtend::SoundExtend( " << &s <<" )";
    Log << nl << e.what();
}

SoundExtend::~SoundExtend()
{
    Mix_FreeChunk(pvm_chunk.release());
}

Mix_Chunk& SoundExtend::get_rMIX() const
{
    return *pvm_chunk;
}

#endif
}
}
