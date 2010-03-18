#include "SDLSoundImpl.hh"
#include "SDLConfig.hh"

using namespace RAGE;

namespace SDLut
{
namespace audio
{

//class SoundImpl

SoundImpl::SoundImpl(std::string filename, bool loop_status) throw ( std::logic_error)
try :
    SoundIf(filename, loop_status), _aInfo( new SDL_AudioSpec() ), converted (false)
{
#ifdef DEBUG
    Log << nl << "SoundImpl::SoundImpl(" << filename << ") called";
#endif
    Uint32 len;

    //SDL_LoadWAV_RW(,1, _aInfo.get_pSDL(),&_buf,&len);
    if ( SDL_LoadWAV_RW(pvm_OriginalData->get_pSDL(),0,_aInfo.get_pSDL(),&_buf,&len) == NULL)
    {
        throw std::logic_error(" Unable to open the sound file !");
    }
    pvm_OriginalData->seek(0,system::RWOps::Set);

    _length = static_cast<unsigned long>(len);

    _loop_status = loop_status;
#ifdef DEBUG
    Log << nl << "SoundImpl::SoundImpl(" << filename << ") done";
#endif
}
catch (std::exception &e)
{
    Log << e.what();
    Log<< GetError();
}

//copy original sound data ( should be shared for optimisation later on maybe... )
SoundImpl::SoundImpl( const SoundImpl & s) throw (std::logic_error)
try :
    SoundIf(s), _aInfo ( s._aInfo ), converted(s.converted)
{
    //m_info( page.m_info.get( ) != 0 ? new CInfo( *page.m_info ) : 0 ),

#ifdef DEBUG
    Log << nl << "SoundImpl::SoundImpl(" << &s << ") called";
#endif
    //*pvm_OriginalData = *(s.pvm_OriginalData);

    Uint32 len;
    //DOING :use of SDL_LoadWAV_RW (RWops) if possible to have only one way to free the memory allocated for a sound...
    if ( SDL_LoadWAV_RW(pvm_OriginalData->get_pSDL(),0,_aInfo.get_pSDL(),&_buf,&len) == NULL)
    {
        throw std::logic_error(" Unable to read the sound in memory !");
    }
    pvm_OriginalData->seek(0,system::RWOps::Set);

    _length = static_cast<unsigned long>(len);

    _loop_status=s._loop_status;

#ifdef DEBUG
    Log << nl << "SoundImpl::SoundImpl(" << &s << ") done";
#endif
}
catch (std::exception &e)
{
    Log << e.what();
    Log<< GetError();
}

bool SoundImpl::Convert (unsigned short DestinationFormat,unsigned short DestinationChannels,int DestinationFrequency)
{
#ifdef DEBUG
    Log << nl << "SoundImpl::Convert(" << DestinationFormat << " , " << DestinationChannels<< " , " << DestinationFrequency << ") called";
#endif


    //AudioConvert cvt = new AudioConvert(_aInfo->_spec->format, _aInfo->_spec->channels, _aInfo->_spec->freq, DestinationFormat,DestinationChannels,DestinationFrequency);
    std::auto_ptr<SDL_AudioCVT> _convertTable( new SDL_AudioCVT() );

    if (SDL_BuildAudioCVT(_convertTable.get(), static_cast<Uint16>(_aInfo.format()), static_cast<Uint8>(_aInfo.channels()), _aInfo.frequency(),
                          static_cast<Uint16>(DestinationFormat), static_cast<Uint8>(DestinationChannels), DestinationFrequency) < 0)
    {
        throw std::logic_error("Error constructing the Audio Convertor !");
    }

    _convertTable->len = _length;
    _convertTable->buf = new Uint8[_convertTable->len*_convertTable->len_mult];

    for (unsigned int i=0; i< _length; i++)
    {
        _convertTable->buf[i] = _buf[i];
    }

    //return cvt.convert();
    int res = SDL_ConvertAudio(_convertTable.get());

    if (res == 0) //convert successful
    {
        converted = true;
        SDL_LockAudio();
        SDL_FreeWAV(_buf);

        _aInfo.get_pSDL()->freq = static_cast<Uint16>(DestinationFrequency);
        _aInfo.get_pSDL()->channels = static_cast<Uint8>(DestinationChannels);
        _aInfo.get_pSDL()->format = DestinationFormat;

        _length = _convertTable->len_cvt;
        _buf = _convertTable->buf;

        SDL_UnlockAudio();
    }
    else
    {
        delete[] _convertTable->buf;
    }

#ifdef DEBUG
    Log << nl << "SoundImpl::Convert(" << DestinationFormat << " , " << DestinationChannels<< " , " << DestinationFrequency << ") done";
#endif

    return res == 0;

}

SoundImpl::~SoundImpl()
{

#ifdef DEBUG
    Log << nl << "SoundImpl::~SoundImpl() called";
#endif
    if ( converted )
    {
        delete[] _buf;
    }
    else
    {
        SDL_FreeWAV(_buf);
    }
#ifdef DEBUG
    Log << nl << "SoundImpl::~SoundImpl() done";
#endif
}
}
}
