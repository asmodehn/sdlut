#include "Audio/SDLSound.hh"
#include "SDLConfig.hh"

#include "Default/SDLSoundImpl.hh"
#include "MIX/SDLSoundExtend.hh"

using namespace Core;

namespace SDLut
{
namespace audio
{


SoundIf::SoundIf(std::string filename, bool loop_status) throw (std::logic_error)
try :
    pvm_OriginalData(new system::RWOps(filename.c_str(), "rb"))
{
    if ( !pvm_OriginalData.get() )
    {
        throw std::logic_error(" Unable to access the sound file !");
    }
    pvm_OriginalData->seek(0,system::RWOps::Set);
}
catch (std::exception &e )
{
    Log << nl << " Exception caught in SoundIf::SoundIf()";
    Log << nl << e.what();
}

SoundIf::SoundIf(const SoundIf & s) throw (std::logic_error)
try :
    pvm_OriginalData(s.pvm_OriginalData.get() !=0 ? new system::RWOps(*s.pvm_OriginalData) : 0)
{
    if ( ! pvm_OriginalData.get() )
    {
        throw std::logic_error(" Unable to access the sound in memory !");
    }
    pvm_OriginalData->seek(0,system::RWOps::Set);
}
catch (std::exception &e )
{
    Log << nl << " Exception caught in SoundIf::SoundIf( " << &s << " )";
    Log << nl << e.what();
}



Sound::Sound(std::string filename, bool loop_status /* = false */) throw (std::logic_error)
try :
    pvm_soundimpl(0)
{
#ifdef WK_SDLut_FOUND_SDLMIXER
    pvm_soundimpl.reset( new SoundExtend(filename, loop_status) );
#else
    pvm_soundimpl.reset( new SoundImpl(filename, loop_status) );
#endif

}
catch (std::exception & e)
{
    Log << nl << e.what();
}

Sound::Sound(const Sound & s) throw (std::logic_error)
try :
    pvm_soundimpl(0)
{
    if ( s.pvm_soundimpl.get() )
    {
#ifdef WK_SDLut_FOUND_SDLMIXER
        if (s.pvm_soundimpl->isMIXImpl() )
        {

            pvm_soundimpl.reset(new SoundExtend(static_cast<SoundExtend&>(*s.pvm_soundimpl)));
        }
        else
        {
#else
        pvm_soundimpl.reset(new SoundImpl(static_cast<SoundImpl&>(*s.pvm_soundimpl)));
#endif
        }
    }
}
catch (std::exception & e)
{
    Log << nl << e.what();
}

Sound::~Sound()
{
}

bool Sound::Convert (unsigned short DestinationFormat,unsigned short DestinationChannels,int DestinationFrequency)
{
    return pvm_soundimpl->Convert(DestinationFormat, DestinationChannels, DestinationFrequency);
}

}
}
