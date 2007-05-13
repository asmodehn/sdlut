#include "Audio/SDLMixer.hh"
#include "SDLConfig.hh"

#ifndef min
#define min(a,b) (a<b)?a:b;
#endif

namespace RAGE
{
	namespace SDL
	{

		std::vector<const Sound*> Mixer::_channels;
		std::vector<unsigned long> Mixer::_channelscursor;
		std::vector<bool> Mixer::_activechannels;
		std::vector<bool> Mixer::_loopchannels;
		std::vector<int> Mixer::_channelsvolume;
		
		// This function is called when the audio device needs more data
		void Mixer::callback(void *userdata, Uint8 *stream, int len)
		{
			Uint8 *waveptr;
			int    waveleft;

			unsigned int i;
			//Going throw channels list to find out the active ones
			for (i = 0; i < _activechannels.size(); i++)
			{
			if (_activechannels[i])
			{
				//TODO : replace mixaudio with my own mix function, in case there is no SDL_mixer
				//hint : from http://www.libsdl.org/cgi/docwiki.cgi/Audio_20Examples
				waveptr = _channels[i]->_buf + _channelscursor[i] ;
				waveleft = min(_channels[i]->_length - _channelscursor[i],static_cast<unsigned int>(len));//test end of sound buffer

				SDL_MixAudio(stream, waveptr, waveleft, _channelsvolume[i]);
				_channelscursor[i] += waveleft;
				if (_channelscursor[i] >= _channels[i]->_length)
				{
					_channelscursor[i]=0;
							
					//in case of loop
					if (_loopchannels[i])
					{
						stream += waveleft;
						len -= waveleft;
						waveleft = min(static_cast<unsigned int>(len),_channels[i]->_length);
						SDL_MixAudio(stream, _channels[i]->_buf, waveleft, _channelsvolume[i]);
						_channelscursor[i] += waveleft;
					}
					else
					{
						_activechannels[i] = false;
					}
					
				}
			}
			//	Log << nl <<" Channel "<< i<<" after callback at " << _channelscursor[i] << " in [0 .. "<< _channels[i]->_length << "]";
			}

		}
		
		Mixer::Mixer(int frequency,unsigned short channels,unsigned short samples)  throw (std::logic_error)
		try : _hwspec(frequency, static_cast<Uint8>(channels), samples, Mixer::callback )
		{
#ifdef DEBUG
		Log << nl << "Mixer::Mixer(" << frequency << ", " << channels << ", " << samples << ") called";
#endif

			//TODO : if possible use the userdata field to optimize output with mixer... problem : qualitative measure by hearing the sound...
			//ID : time measure and compare with frequency and samples number ?
			
			Log << nl << "Using Audio Driver : " << getDriverName();

			PlayAll();	

#ifdef DEBUG
		Log << nl << "Mixer::Mixer(" << frequency << ", " << channels << ", " << samples << ") done";
#endif
		}
		catch (std::exception& e)
		{
			Log << nl << "Exception caught in Mixer::Mixer() : " << e.what();
		}

		
		Mixer::Mixer(const Mixer& m) : _hwspec ( m._hwspec )
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
	PauseAll();
			
#ifdef DEBUG
			Log << nl << "Mixer::~Mixer() called";
#endif
			//delete all remaining channels
			for (unsigned int i= 0 ; i< _activechannels.size();i++)
			{
				freeChannel(i);
			}
			SDL_CloseAudio();
#ifdef DEBUG
			Log << nl << "Mixer::~Mixer() done";
#endif
}

		

		Mixer::Status Mixer::GetStatus()
{
	switch (SDL_GetAudioStatus())
	{
		case SDL_AUDIO_PLAYING : return Playing;
		case SDL_AUDIO_STOPPED : return Stopped;
		case SDL_AUDIO_PAUSED : return Paused;
	}
	//4 warnings
	return Stopped;
}

		
	int Mixer::mixSound(const Sound& sound,bool loop, bool autoplay )
{
#ifdef DEBUG
			Log << nl << "Mixer::mixSound("<<&sound<< ", " << autoplay <<") called";
#endif

	//_originals.push_back(&sound);
	Sound* cvtsound = new Sound(sound);
	
	//is the test the other way around ?
	if (!cvtsound->Convert(static_cast<unsigned short>(_hwspec.format()),static_cast<unsigned short>( _hwspec.channels()), _hwspec.frequency()))
	    {
		    Log << nl << "Erreur lors de la conversion du fichier audio:" << GetError();
		    delete cvtsound;
	    } else
	    {
		    SDL_LockAudio();
		    _channels.push_back(cvtsound);
		    _activechannels.push_back(autoplay);
		    _channelscursor.push_back(0);
		    _loopchannels.push_back(loop);
		    _channelsvolume.push_back(SDL_MIX_MAXVOLUME);
		    SDL_UnlockAudio();
	    }

#ifdef DEBUG
			Log << nl << "Mixer::mixSound("<<&sound<< ", " << autoplay <<") done";
#endif
	return _activechannels.size()-1;
}

int Mixer::freeChannel(int index)
{
	if ( _channels.at(index) != NULL)
		delete _channels.at(index), _channels.at(index) = NULL;

	//dont erase channel from vector, else the vector size will disminuish from 1
	//and so all channels numbers currently in use will be false !!

	/*_channels.erase(_channels.begin()+index, _channels.begin()+index+1);
	_activechannels.erase(_activechannels.begin()+index, _activechannels.begin()+index+1);
	_channelscursor.erase(_channelscursor.begin()+index, _channelscursor.begin()+index+1);
	_loopchannels.erase(_loopchannels.begin()+index, _loopchannels.begin()+index+1);*/
	
	//to know which channel was deleted
	return index;
}

	std::string Mixer::getDriverName()
	{
		char name[32];
		SDL_AudioDriverName(name,32);
		return std::string(name);
		//printf("Using audio driver: %s\n", SDL_AudioDriverName(name, 32));
	}

	
	void Mixer::PauseAll(void) { SDL_PauseAudio(1); }
	void Mixer::PlayAll(void) { SDL_PauseAudio(0); }
		
		void Mixer::stopChannel(int index)
{
	_activechannels[index] = false;
	_channelscursor[index] = 0;
}
		void Mixer::playChannel(int index)
{
	_activechannels[index] = true;
}
		void Mixer::pauseChannel(int index)
{
	_activechannels[index] = false;
}
		int Mixer::setvolumeChannel(int vol, int index)
{
	int res = _channelsvolume[index];
	_channelsvolume[index] = vol * SDL_MIX_MAXVOLUME / 100;
	return res;
}

		int Mixer::setChannelsNumber(int n)
{
	SDL_LockAudio();
	_channels.resize(n);//TODO : if needed, fill the new channels with default sound (silence?)
	_activechannels.resize(n); //TODO : turn off the new channels
	_channelscursor.resize(n); //TODO : turn off the new channels
	_loopchannels.resize(n);
	_channelsvolume.resize(n);
	SDL_UnlockAudio();
	return n; //TODO : return the actuall allocated number of channels
}
}
}
