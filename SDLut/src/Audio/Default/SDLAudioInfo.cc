#include "SDLAudioInfo.hh"
#include "SDLConfig.hh"

namespace RAGE
{
namespace SDL
{

//class AudioInfo

bool AudioInfo::autoConvert = false;

//This handle explicit casts


AudioInfo::AudioInfo(int frequency, unsigned char channels, unsigned short samples, void (*callback)(void *userdata, unsigned char *stream, int len), void* userdata) throw (std::logic_error)
try :
    _spec(new SDL_AudioSpec())
{
#ifdef DEBUG
    Log << nl << "AudioInfo::AudioInfo( "<< frequency << ", " << channels << ", " << samples << ", " << callback << ", " << userdata <<") called";
#endif
    _spec->freq = frequency;		// DSP frequency -- samples per second
    _spec->format = AUDIO_S16SYS;		// Audio data format
    //WARNING : as for SDL_MixAudio in V 1.2.11, AUDIO_U16 is unknown...
    _spec->channels = channels;	// Number of channels: 1 mono, 2 stereo
    _spec->samples = samples;		// Audio buffer size in samples (power of 2)
    _spec->callback = callback;
    _spec->userdata = userdata;

    if (autoConvert)
    {
        if (SDL_OpenAudio(_spec.get(), NULL)!=0)
        {
            Log << nl << "Error Initialising Audio";
            throw std::logic_error("Error initializing Audio");
        }
    }
    else //if no autoconvert, the valid _spec is filled by OpenAudio
    {
        SDL_AudioSpec * _newspec = new SDL_AudioSpec();
        if (SDL_OpenAudio(_spec.get(),_newspec)!=0)
        {
            Log << nl << "Error Initialising Audio";
            throw std::logic_error("Error initializing Audio");
        }
        _spec.reset(_newspec);
    }

#ifdef DEBUG
    Log << nl << "AudioInfo::AudioInfo( "<< frequency << ", " << channels << ", " << samples << ", " << callback << ", " << userdata <<") done.";
#endif
}
catch (std::exception& e)
{
    Log << nl << "Exception caught in AudioInfo::AudioInfo() : " << e.what();
}


AudioInfo::AudioInfo(SDL_AudioSpec* as): _spec(as)
{
#ifdef DEBUG
    Log << nl << "AudioInfo::AudioInfo( "<< as << ") called";
#endif

#ifdef DEBUG
    Log << nl << "AudioInfo::AudioInfo( "<< as << ") done.";
#endif
}

AudioInfo::AudioInfo(const AudioInfo & ai)
        : _spec( new SDL_AudioSpec() )
{
#ifdef DEBUG
    Log << nl << "AudioInfo::AudioInfo( "<< &ai << ") called";
#endif
    //duplicated
    *_spec = *(ai._spec);
    /*_spec->freq = ai._spec->freq;
    _spec->format = ai._spec->format;
    _spec->channels = ai._spec->channels;
    _spec->silence = ai._spec->silence;
    _spec->samples = ai._spec->samples;
    _spec->size = ai._spec->size;
    _spec->callback = ai._spec->callback;
    _spec->userdata = ai._spec->userdata;*/
#ifdef DEBUG
    Log << nl << "AudioInfo::AudioInfo( "<< &ai << ") done.";
#endif
}

AudioInfo::~AudioInfo(void)
{
}


int AudioInfo::frequency() const
{
    return _spec->freq;
}

unsigned int AudioInfo::format() const
{
    return _spec->format;
}

unsigned int AudioInfo::channels() const
{
    return _spec->channels;
}

unsigned long AudioInfo::samples() const
{
    return _spec->samples;
}

void* AudioInfo::userdata() const
{
    return _spec->userdata;
}

SDL_AudioSpec AudioInfo::get_SDL()
{
    return *_spec;
}


Logger & operator << (Logger & log, const AudioInfo & ai)
{
    log << nl << "AudioInfo::" << nl
    << " - Frequency = " << ai.frequency() << nl
    << " - Format = " << ai.format() << nl
    << " - Channels = " << ai.channels() << nl
    << " - Samples = " << ai.samples();
    return log;
}




} //namespace SDL
}//namespace RAGE

