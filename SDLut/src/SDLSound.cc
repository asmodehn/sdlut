#include "SDLSound.hh"
#include "SDLConfig.hh"

namespace RAGE
{
	namespace SDL
	{

		//class Sound
		
		Sound::Sound(std::string filename, bool loop_status) throw ( std::logic_error)
		try : _aInfo( new SDL_AudioSpec() ), frommem(false)
		{
#ifdef DEBUG
			Log << nl << "Sound::Sound(" << filename << ") called";
#endif
			Uint32 len;
			if ( SDL_LoadWAV(filename.c_str(),_aInfo.get_pSDL(),&_buf,&len) == NULL)
			{
				throw std::logic_error(" Unable to open the sound file !");
			}

			_length = static_cast<unsigned long>(len);

			_loop_status = loop_status;
#ifdef DEBUG
			Log << nl << "Sound::Sound(" << filename << ") done";
#endif
		}
		catch (std::exception &e)
			{
				Log << e.what();
				Log<< GetError();
			}

		Sound::Sound( const Sound & s) : _aInfo ( s._aInfo )
{
			
#ifdef DEBUG
			Log << nl << "Sound::Sound(" << &s << ") called";
#endif
			//TODO :use of SDL_LoadWAV_RW (RWops) if possible to have only one way to free the memory allocated for a sound...
				
			_length=s._length;
			_buf= new Uint8[s._length];
			for (unsigned int i=0; i<s._length; i++)
			{
				_buf[i] = s._buf[i];
			}
			_loop_status=s._loop_status;

			frommem=true;
#ifdef DEBUG
			Log << nl << "Sound::Sound(" << &s << ") done";
#endif
}
		
 bool Sound::Convert (unsigned short DestinationFormat,unsigned short DestinationChannels,int DestinationFrequency)
{
#ifdef DEBUG
	Log << nl << "Sound::Convert(" << DestinationFormat << " , " << DestinationChannels<< " , " << DestinationFrequency << ") called";
#endif


	//AudioConvert cvt = new AudioConvert(_aInfo->_spec->format, _aInfo->_spec->channels, _aInfo->_spec->freq, DestinationFormat,DestinationChannels,DestinationFrequency);
	std::auto_ptr<SDL_AudioCVT> _convertTable( new SDL_AudioCVT() );

	if (SDL_BuildAudioCVT(_convertTable.get(), static_cast<Uint16>(_aInfo.format()), static_cast<Uint8>(_aInfo.channels()), _aInfo.frequency(),
	    (Uint16) DestinationFormat, (Uint8) DestinationChannels, DestinationFrequency) < 0)
	{
		throw std::logic_error("Error constructing the Audio Convertor !");
	}
		
	//cvt.fillBuffer(_length, _buf);
	_convertTable->len = _length;
	_convertTable->buf = new Uint8[_convertTable->len*_convertTable->len_mult];
	for (unsigned int i=0; i< _length; i++)
	{
		_convertTable->buf[i] = _buf[i];
	}
	
	//return cvt.convert();
	int res = SDL_ConvertAudio(_convertTable.get());

	if (res !=-1)
	{
		_length = _convertTable->len_cvt;
		if ( frommem )
		{
			delete[] _buf;
		}
		else
		{
			SDL_FreeWAV(_buf);
		}
		_buf = _convertTable->buf;
		frommem = true;
	}
	else
	{
		delete[] _convertTable->buf;
	}

// 	_aInfo->_spec->format = DestinationFormat;
// 	_aInfo->_spec->channels = DestinationChannels;
// 	_aInfo->_spec->freq = DestinationFrequency;
//

	//TODO : find a way to have an accurate AudioInfo after convert
	
#ifdef DEBUG
	Log << nl << "Sound::Convert(" << DestinationFormat << " , " << DestinationChannels<< " , " << DestinationFrequency << ") done";
#endif
	
	return res == 0;
	
}

		Sound::~Sound()
{
			
#ifdef DEBUG
			Log << nl << "Sound::~Sound() called";
#endif
			if ( frommem )
			{
				delete[] _buf;
			}
			else
			{
				SDL_FreeWAV(_buf);
			}
			
#ifdef DEBUG
			Log << nl << "Sound::~Sound() done";
#endif
}
	}
}
