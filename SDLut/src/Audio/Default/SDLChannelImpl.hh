#ifndef SDL_CHANNEL_HH
#define SDL_CHANNEL_HH

/**
 * \class Channel
 *
 * \ingroup Audio
 *
 * \brief Class handling a Channel in a mixer
 *
 * \author Alex
 *
 * \date 2006/09/01
 *
 * Contact: asmodehn@gna.org
 *
 */

#include "SDLSoundImpl.hh"

namespace RAGE
{
namespace SDL
{

class ChannelImpl
{

    const SoundImpl * pvm_sound;
    unsigned long pvm_cursor;
    int pvm_volume;
    bool pvm_playing;
    bool pvm_loop;

    friend class MixerImpl;

protected :
    ChannelImpl(const SoundImpl * s, bool loop, bool autoplay, unsigned short volpct);

public :

    virtual ~ChannelImpl();

    virtual bool isMIXImpl()
    {
        return false;
    }

    virtual void play();
    virtual void pause();
    virtual void stop();
    //returns old volume absolute value
    virtual int setVolume(unsigned short volpct);

    virtual bool isPlaying()
    {
        return pvm_playing;
    }



};

}
}

#endif // SDL_CHANNEL_HH
