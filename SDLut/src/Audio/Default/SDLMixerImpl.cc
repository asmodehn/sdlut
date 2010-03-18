#include "SDLMixerImpl.hh"
#include "SDLConfig.hh"

using namespace RAGE;

#ifndef min
#define min( a , b )  ( (a)>(b) )?(b):(a)
#endif

namespace SDLut
{
namespace audio
{

std::vector<ChannelImpl*> MixerImpl::pvm_channels;

// This function is called when the audio device needs more data
void MixerImpl::callback(void *userdata, Uint8 *stream, int len)
{
    Uint8 *waveptr;
    int    waveleft;

    unsigned int i;
    //Going throw channels list to find out the active ones
    for (i = 0; i < pvm_channels.size(); i++)
    {
        if (pvm_channels[i]->isPlaying())
        {
            //TODO : replace mixaudio with my own mix function, in case there is no SDL_mixer
            //hint : from http://www.libsdl.org/cgi/docwiki.cgi/Audio_20Examples
            waveptr = pvm_channels[i]->pvm_sound->_buf + pvm_channels[i]->pvm_cursor ;
            waveleft = min(pvm_channels[i]->pvm_sound->_length - pvm_channels[i]->pvm_cursor,static_cast<unsigned int>(len));//test end of sound buffer

            SDL_MixAudio(stream, waveptr, waveleft, pvm_channels[i]->pvm_volume);
            pvm_channels[i]->pvm_cursor += waveleft;
            if (pvm_channels[i]->pvm_cursor >= pvm_channels[i]->pvm_sound->_length)
            {
                pvm_channels[i]->pvm_cursor=0;

                //in case of loop
                if (pvm_channels[i]->pvm_loop)
                {
                    stream += waveleft;
                    len -= waveleft;
                    waveleft = min(static_cast<unsigned int>(len),pvm_channels[i]->pvm_sound->_length);
                    SDL_MixAudio(stream, pvm_channels[i]->pvm_sound->_buf, waveleft, pvm_channels[i]->pvm_volume);
                    pvm_channels[i]->pvm_cursor += waveleft;
                }
                else
                {
                    pvm_channels[i]->pause();
                }

            }
        }
        //	Log << nl <<" Channel "<< i<<" after callback at " << pvm_channels[i]->cursor << " in [0 .. "<< pvm_channels[i]->sound->_length << "]";
    }

}

MixerImpl::MixerImpl(int frequency,unsigned short channels,unsigned short samples)  throw (std::logic_error)
try :
    _hwspec(frequency, static_cast<Uint8>(channels), samples, MixerImpl::callback )
{
#ifdef DEBUG
    Log << nl << "MixerImpl::MixerImpl(" << frequency << ", " << channels << ", " << samples << ") called";
#endif

    //TODO : if possible use the userdata field to optimize output with mixer... problem : qualitative measure by hearing the sound...
    //ID : time measure and compare with frequency and samples number ?

    Log << nl << "Using Audio Driver : " << getDriverName();

    PlayAll();

#ifdef DEBUG
    Log << nl << "MixerImpl::MixerImpl(" << frequency << ", " << channels << ", " << samples << ") done";
#endif
}
catch (std::exception& e)
{
    Log << nl << "Exception caught in MixerImpl::MixerImpl() : " << e.what();
}


MixerImpl::MixerImpl(const MixerImpl& m) : _hwspec ( m._hwspec )
{

#ifdef DEBUG
    Log << nl << "MixerImpl::MixerImpl("<<&m<<") called";
#endif

#ifdef DEBUG
    Log << nl << "MixerImpl::MixerImpl("<<&m<<") done";
#endif
}

MixerImpl::~MixerImpl()
{
    PauseAll();

#ifdef DEBUG
    Log << nl << "MixerImpl::~MixerImpl() called";
#endif
    //delete all remaining channels
    for (unsigned int i= 0 ; i< pvm_channels.size();i++)
    {
        freeChannel(i);
    }
    SDL_CloseAudio();
#ifdef DEBUG
    Log << nl << "MixerImpl::~MixerImpl() done";
#endif
}



/*		MixerImpl::Status MixerImpl::GetStatus()
{
	switch (SDL_GetAudioStatus())
	{
		case SDL_AUDIO_PLAYING : return Playing;
		case SDL_AUDIO_STOPPED : return Stopped;
		case SDL_AUDIO_PAUSED : return Paused;
	}
	//4 warnings
	return Stopped;
}*/


int MixerImpl::mixSound(const SoundIf& sound, bool loop /*= true*/, bool autoplay /*= true*/, unsigned short volume /*= 100*/ )
{
#ifdef DEBUG
    Log << nl << "MixerImpl::mixSound("<<&sound<< ", " << autoplay <<") called";
#endif

    //_originals.push_back(&sound);
    SoundImpl* cvtsound = new SoundImpl(dynamic_cast<const SoundImpl &>(sound)); //downcasting

    //is the test the other way around ?
    if (!cvtsound->Convert(static_cast<unsigned short>(_hwspec.format()),static_cast<unsigned short>( _hwspec.channels()), _hwspec.frequency()))
    {
        Log << nl << "Erreur lors de la conversion du fichier audio:" << GetError();
        delete cvtsound;
    }
    else
    {
        ChannelImpl * c = new ChannelImpl(cvtsound, loop, autoplay, volume);
        SDL_LockAudio();
        pvm_channels.push_back(c);
        SDL_UnlockAudio();
    }

#ifdef DEBUG
    Log << nl << "MixerImpl::mixSound("<<&sound<< ", " << autoplay <<") done";
#endif
    return pvm_channels.size()-1;
}


ChannelImpl & MixerImpl::getChannel(int index)
{
    return *pvm_channels.at(index);
}

int MixerImpl::freeChannel(int index)
{
    if ( pvm_channels.at(index) != NULL)
        delete pvm_channels.at(index), pvm_channels.at(index) = NULL;

    //dont erase channel from vector, else the vector size will disminuish from 1
    //and so all channels numbers currently in use will be false !!

    /*_channels.erase(_channels.begin()+index, _channels.begin()+index+1);
    _activechannels.erase(_activechannels.begin()+index, _activechannels.begin()+index+1);
    _channelscursor.erase(_channelscursor.begin()+index, _channelscursor.begin()+index+1);
    _loopchannels.erase(_loopchannels.begin()+index, _loopchannels.begin()+index+1);*/

    //to know which channel was deleted
    return index;
}

std::string MixerImpl::getDriverName()
{
    char name[32];
    SDL_AudioDriverName(name,32);
    return std::string(name);
    //printf("Using audio driver: %s\n", SDL_AudioDriverName(name, 32));
}


void MixerImpl::PauseAll(void)
{
    SDL_PauseAudio(1);
}
void MixerImpl::PlayAll(void)
{
    SDL_PauseAudio(0);
}

int MixerImpl::setChannelsNumber(int n)
{
    SDL_LockAudio();
    pvm_channels.resize(n);
    SDL_UnlockAudio();
    return pvm_channels.size();
}
}
}
