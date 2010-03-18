#ifndef SDLUT_SOUND_HH
#define SDLUT_SOUND_HH

#include <memory>
#include <string>
#include <stdexcept>

#include "System/SDLRWOps.hh"

namespace SDLut
{
namespace audio
{

/**
 * \class SoundIf
 *
 * \ingroup audio
 *
 * \brief This class may interface different Sound Implementations
 *
 * This class if an interface for different implementation of Sound.
 *
 * \note
 *
 * \author Alex
 *
 * \date 2007/05/24
 *
 * Contact: asmodehn@gna.org
 *
 */


//using Pimpl idiom to hide use of optional dependencies or fallback behaviour
class SoundIf
{
protected:
    std::auto_ptr<system::RWOps> pvm_OriginalData;

public:
    //Sound Loader
    SoundIf(std::string filename, bool loop_status = false) throw (std::logic_error);
    //Sound Copy ( careful with conversion )
    SoundIf( const SoundIf & s)  throw (std::logic_error);

    virtual bool isMIXImpl() = 0 ;
    //careful here, the convert behavior of different implementation must match ( mixer convert on construction it seems...)
    virtual bool Convert (unsigned short DestinationFormat,unsigned short DestinationChannels,int DestinationFrequency) = 0 ;

    virtual ~SoundIf() {};
};

/**
 * \class Sound
 *
 * \ingroup audio
 *
 * \brief This class handles Sound
 *
 * This class wraps Sounds (as set of chunks ) from SDL_mixer if present, or implements a fallback behavior if using only SDL
 *
 * \note
 *
 * \author Alex
 *
 * \date 2007/05/15
 *
 * Contact: asmodehn@gna.org
 *
 */

class Sound
{
    friend class Mixer;

private :
    std::auto_ptr<SoundIf> pvm_soundimpl;

public:
    Sound(std::string filename, bool loop_status = false) throw (std::logic_error);
    Sound(const Sound &) throw (std::logic_error);
    ~Sound();

    bool Convert (unsigned short DestinationFormat,unsigned short DestinationChannels,int DestinationFrequency);
};

}
}
#endif
