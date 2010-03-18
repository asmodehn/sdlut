#include "SDLMixerExtend.hh"
#include "SDLConfig.hh"

using namespace RAGE;

namespace SDLut
{
namespace audio
{
#ifdef WK_SDLMIXER_FOUND

MixerExtend::MixerExtend(int frequency = MIX_DEFAULT_FREQUENCY,unsigned short channels = 2 ,unsigned short samples = 512) throw (std::logic_error)
try
{
    if ( Mix_OpenAudio(frequency,/*AUDIO_S16SYS*/MIX_DEFAULT_FORMAT,channels, samples) != 0 )
    {
        //TODO : use Mix_GetError() to fetch the actual error
        throw std::logic_error( "Mix_OpenAudio returned Error: " + (std::string)Mix_GetError() );
    }
    QuerySpec();
}
catch (std::exception & e)
{
    Log << nl << "Exception caught in MixerExtend::MixerExtend()";
    Log << nl << e.what();
    Log << nl << Optional::GetError(Optional::Mixer);
}

MixerExtend::~MixerExtend()
{
    Mix_CloseAudio();
}

bool MixerExtend::QuerySpec()
{
    numtimesopened=Mix_QuerySpec(&frequency, &format, &channels);
    return ( numtimesopened != 0 ) ;
}


int MixerExtend::GetFrequencyUsed()
{
    QuerySpec();
    return frequency;
}

int MixerExtend::GetChannelsUsed()
{
    QuerySpec();
    return channels;
}

int MixerExtend::GetTimesDevOpen()
{
    QuerySpec();
    return numtimesopened;
}

std::string MixerExtend::getDriverName()
{
    char name[32];
    SDL_AudioDriverName(name,32);
    return std::string(name);
//printf("Using audio driver: %s\n", SDL_AudioDriverName(name, 32));
}

int MixerExtend::NbrChannelsPlaying()
{
    return Mix_Playing(-1);
}

int MixerExtend::NbrChannelsPaused()
{
    return Mix_Paused(-1);
}

bool MixerExtend::isPlaying(int whichchannel)
{
    return Mix_Playing(whichchannel) == 1;
}

bool MixerExtend::isPaused(int whichchannel)
{
    return Mix_Paused(whichchannel) == 1;
}

bool MixerExtend::isFadingIn(int whichchannel)
{
    if (Mix_Fading(whichchannel) != MIX_FADING_IN ) return false;
    return true;
}

bool MixerExtend::isFadingOut(int whichchannel)
{
    if (Mix_Fading(whichchannel) != MIX_FADING_OUT ) return false;
    return true;
}

int MixerExtend::playChannel(const SoundIf& sound, int volumepct, int loops, int fadeintime, int index)
{
    int chanplayed = -1;
    const SoundExtend & sndext = static_cast<const SoundExtend&>(sound);
    Mix_VolumeChunk(&sndext.get_rMIX(),volumepct * MIX_MAX_VOLUME / 100);
    if (fadeintime != 0)
    {
        chanplayed = Mix_FadeInChannel(index,&sndext.get_rMIX(),loops,fadeintime);
    }
    else
    {
        chanplayed = Mix_PlayChannel(index,&sndext.get_rMIX(),loops);
    }
    if (chanplayed == -1)
    {
        Log << nl << "MixerExtend::playChannel(" << &sound << ", " << volumepct << ", " << loops << ", " << fadeintime << ", " << index << ") returned an Error :";
        Log << nl << Optional::GetError(Optional::Mixer);
    }
    return chanplayed;
}

void MixerExtend::pauseChannel(int index)
{
    Mix_Pause(-1);
}

void MixerExtend::resumeChannel(int index)
{
    Mix_Resume(-1);
}

int MixerExtend::stopChannel(int index, int fadeouttime)
{
    int numchanstopped = 0;
    if ( fadeouttime != 0 )
    {
        numchanstopped=Mix_FadeOutChannel(index,fadeouttime);
    }
    else
    {
        Mix_HaltChannel(index);
        numchanstopped = 1;
    }
    return numchanstopped;
}

int MixerExtend::setChannelsNumber(int n)
{
    return Mix_AllocateChannels(n);
}

bool MixerExtend::playMusic(const MusicIf& music, int volumepct, int loops, int fadeintime, int index)
{
    int res = -1;
    const MusicExtend & musext = static_cast<const MusicExtend&>(music);
    Mix_VolumeMusic(volumepct * MIX_MAX_VOLUME / 100);
    if (fadeintime != 0)
    {
        res = Mix_FadeInMusic(&musext.get_rMIX(),loops,fadeintime);
    }
    else
    {
        res = Mix_PlayMusic(&musext.get_rMIX(),loops);
    }
    if (res == -1)
    {
        Log << nl << "MixerExtend::playMusic(" << &music << ", " << volumepct << ", " << loops << ", " << fadeintime << ", " << index << ") returned an Error :";
        Log << nl << Optional::GetError(Optional::Mixer);
    }
    return res == 0;

}

void MixerExtend::pauseMusic()
{
    Mix_PauseMusic();
}

void MixerExtend::resumeMusic()
{
    Mix_ResumeMusic();
}

void MixerExtend::rewindMusic()
{
    Mix_RewindMusic();
}

bool MixerExtend::setMusicPosition(double pos)
{
    return Mix_SetMusicPosition(pos) == 0;
}

int MixerExtend::setMusicVolume( int volumepct )
{
    return Mix_VolumeMusic(volumepct * MIX_MAX_VOLUME / 100);
}

/*
void MixerExtend::setMusicCMD()
{
}
*/

bool MixerExtend::stopMusic(int fadeouttime )
{
    if ( fadeouttime != 0 )
    {
        return Mix_FadeOutMusic(fadeouttime) == 1;
    }
    else
    {
        return Mix_HaltMusic() == 0;
    }
}


#endif

}
}
