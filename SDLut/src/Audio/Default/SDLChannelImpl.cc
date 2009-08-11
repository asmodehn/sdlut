#include "SDLChannelImpl.hh"

#include "SDLConfig.hh"

namespace RAGE
{
namespace SDL
{

ChannelImpl::ChannelImpl(const SoundImpl * s, bool loop, bool autoplay, unsigned short volpct)
        : pvm_sound(s), pvm_cursor(0), pvm_playing(autoplay), pvm_loop(loop)
{
    setVolume(volpct);
}

ChannelImpl::~ChannelImpl()
{
    delete pvm_sound, pvm_sound = NULL;
}


void ChannelImpl::play()
{
    pvm_playing = true;
}

void ChannelImpl::pause()
{
    pvm_playing = false;
}

void ChannelImpl::stop()
{
    pvm_playing = false;
    pvm_cursor = 0;
}

int ChannelImpl::setVolume(unsigned short volpct)
{
    int res = pvm_volume;
    pvm_volume = static_cast<int>(volpct) * SDL_MIX_MAXVOLUME / 100;
    return res;
}

}
}
