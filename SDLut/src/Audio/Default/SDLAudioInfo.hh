#ifndef SDL_AUDIO_HH
#define SDL_AUDIO_HH

/**
 * \class Audio
 *
 * \ingroup Audio
 *
 * \brief handles AudioSpec
 *
 * \author Alex
 *
 * \date 2006/09/01
 *
 * Contact: asmodehn@gna.org
 *
 */

#include "Logger.hh"
#include <memory>
#include <stdexcept>

//declarign SDL_type for late binding
struct SDL_AudioSpec;

namespace SDLut
{
namespace audio
{

//classes interaction :
//Sound doesnt know Audio, or Mixer.
// 1 -
//Audio doesnt need to know Sound, and doesnt know Mixer either.
//Mixer knows them both to make them work together.
// 2 - better...
//Audio doesnt know Sound, but knows Mixer, and can send it the Specs on creation time.
//Mixer Doesnt know Audio, but knows Sound.

//TODO : Redesign to have the same design scheme as the Video : AudioInfo and Mixer like VideoInfo and Window... (callback in Mixer, but similar creation scheme)
//Might choose 1 instead of 2...




//This class handle the Audio Device.
//Only one instance of this class should be used.
class AudioInfo
{
    friend class SoundImpl;
    friend class MusicImpl;

protected :

    std::auto_ptr<SDL_AudioSpec> _spec;

    //This handle explicit casts
    explicit AudioInfo(SDL_AudioSpec* as);

public :

    //if autoConvert is true, then the constructed AudioInfo will be what has been asked for, and if the hardware is different, SDL will take care of conversion
    //if autoConvert is false, the constructed AudioInfo might be different from what has been asked for.
    //in everycase, the current AudioInfo values must be used for Conversion, and this is handled by Mixer. Default for this value not yet chosen.
    static bool autoConvert;

    AudioInfo(int frequency, unsigned char channels, unsigned short samples, void (*callback)(void *userdata, unsigned char *stream, int len), void* userdata = 0 ) throw (std::logic_error);
    AudioInfo(const AudioInfo &);
    ~AudioInfo(void);

    int frequency() const;
    unsigned int format() const;
    unsigned int channels() const;
    unsigned long samples() const;
    void* userdata() const;

    SDL_AudioSpec get_SDL();
    SDL_AudioSpec* get_pSDL()
    {
        return _spec.get();
    }

    friend RAGE::Logger & operator << (RAGE::Logger & ostr, const AudioInfo & ai);

}; //class Audio


} // namespace SDL
} // namespace SDLut



#endif
