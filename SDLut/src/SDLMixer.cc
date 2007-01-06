#include "SDLMixer.hh"

namespace RAGE
{
	namespace SDL
	{

		std::vector<const Sound*> Mixer::_channels;
		std::vector<int> Mixer::_channelscursor;
		std::vector<bool> Mixer::_activechannels;
		
		//class Mixer
		void Mixer::callback(void *userdata, Uint8 *stream, int len)
		{
			Uint8 *waveptr;
			int    waveleft;

			int i;
			//Going throw channels list to find out the active ones
			for (i = 0; i < _activechannels.size() && _activechannels[i]; i++)
			{
// 					Log << nl <<" Channel " << i<<" at " << _channelscursor[i] << " in [0 .. "<< _channels[i]->_length << "]";


			/* Set up the pointers */
					waveptr = _channels[i]->_buf + _channelscursor[i] ;
					waveleft = _channels[i]->_length - _channelscursor[i];

			/* Go! */
					//in case the sound is smaller than the required number of samples
					//or maybe when the callback is not enough frequently called ???
					//just loop inserting few chunks of audio
					while ( waveleft <= len ) {
						SDL_MixAudio(stream, waveptr, waveleft, SDL_MIX_MAXVOLUME);
						stream += waveleft;
						len -= waveleft;
						waveptr = _channels[i]->_buf;
						waveleft = _channels[i]->_length;
						_channelscursor[i] = 0;
					}
					//just insert the usual full chunk
//To debug, because SDL_MixAudio doesnt know all possible audio formats
// 					for (int j=0; j< len; j++)
// 					{
// 						stream[j] = waveptr[j];
// 					}
					SDL_MixAudio(stream, waveptr, len, SDL_MIX_MAXVOLUME);
					_channelscursor[i] += len;
//					Log << nl <<" Channel "<< i<<" after callback at " << _channelscursor[i] << " in [0 .. "<< _channels[i]->_length << "]";
			}

		}
		
		Mixer::Mixer(int frequency,unsigned short channels,unsigned short samples, bool SDLemulated) : _autoConvert(SDLemulated)
		{
#ifdef DEBUG
		Log << nl << "Mixer::Mixer(" << frequency << ", " << channels << ", " << samples << ", " << SDLemulated << ") called";
#endif


			SDL_AudioSpec* desired = new SDL_AudioSpec();
			desired->freq = frequency;		// DSP frequency -- samples per second
			desired->format = AUDIO_S16SYS;		// Audio data format
			//WARNING : as for SDL_MixAudio in V 1.2.11, AUDIO_U16 is unknown...
			desired->channels = channels;	// Number of channels: 1 mono, 2 stereo
			desired->samples = samples;		// Audio buffer size in samples (power of 2)
	
			// This function is called when the audio device needs more data
			
			desired->callback = Mixer::callback;
			//TODO : if possible use this field to optimize output... problem : qualitative measure by hearing the sound...
			//ID : time measure and compare with frequency and samples number ?
			desired->userdata=NULL;
			
			SDL_AudioSpec * _spec = new SDL_AudioSpec();
			
			try
			{
				if (SDL_OpenAudio(desired, _autoConvert?NULL:_spec)!=0)
				{
					Log << "Error Initialising Audio";
					throw std::logic_error("Error initializing Audio");
				}
	
				if (_autoConvert)
				{
					_spec=desired;
				}
			}
			catch (std::exception& e)
			{
				Log << "Exception caught in Mixer::Mixer() : " << e.what();
			}

			_hwspec = new AudioInfo(_spec);

			Log << nl << "Using Driver : " << getDriverName();

			


#ifdef DEBUG
		Log << nl << "Mixer::Mixer(" << frequency << ", " << channels << ", " << samples << ", " << SDLemulated << ") done";
#endif
		}
		
		Mixer::Mixer(const Mixer& m)
{
			
#ifdef DEBUG
			Log << nl << "Mixer::Mixer("<<&m<<") called";
#endif
			
#ifdef DEBUG
			Log << nl << "Mixer::Mixer("<<&m<<") done";
#endif
}
		
		Mixer::~Mixer()
{
			
#ifdef DEBUG
			Log << nl << "Mixer::~Mixer() called";
#endif
			SDL_CloseAudio();
			delete _hwspec, _hwspec = NULL;
#ifdef DEBUG
			Log << nl << "Mixer::~Mixer() done";
#endif
}

		

		Mixer::Status Mixer::GetStatus()
{
	return static_cast<Status>(SDL_GetAudioStatus());
}

		
	int Mixer::mixSound(const Sound& sound, bool autoplay )
{
#ifdef DEBUG
			Log << nl << "Mixer::mixSound("<<&sound<< ", " << autoplay <<") called";
#endif

	//_originals.push_back(&sound);
	Sound* cvtsound = new Sound(sound);
	
	//is the test the other way around ?
	if (cvtsound->Convert(_hwspec->format(), _hwspec->channels(), _hwspec->frequency()))
	    {
		    Log << "Erreur lors de la conversion du fichier audio:" << GetError();
		    delete cvtsound;
	    } else
	    {
		    SDL_LockAudio();
		    _channels.push_back(cvtsound);
		    _activechannels.push_back(autoplay);
		    _channelscursor.push_back(0);
		    SDL_UnlockAudio();
	    }
	
#ifdef DEBUG
			Log << nl << "Mixer::mixSound("<<&sound<< ", " << autoplay <<") done";
#endif
	return _activechannels.size()-1;
}

	std::string Mixer::getDriverName()
	{
		char name[32];
		SDL_AudioDriverName(name,32);
		return std::string(name);
		//printf("Using audio driver: %s\n", SDL_AudioDriverName(name, 32));
	}

	void Mixer::toggleChannel(int index)
{
	_activechannels[index] = !_activechannels[index];
}

		int Mixer::setChannelsNumber(int n)
{
	SDL_LockAudio();
	_channels.resize(n);//TODO : if needed, fill the new channels with default sound (silence?)
	_activechannels.resize(n); //TODO : turn off the new channels
	_channelscursor.resize(n); //TODO : turn off the new channels
	SDL_UnlockAudio();
	return n; //TODO : return the actuall allocated number of channels
}
}
}
