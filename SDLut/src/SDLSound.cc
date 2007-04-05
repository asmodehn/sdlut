#include "SDLSound.hh"
#include "SDLConfig.hh"

namespace RAGE
{
	namespace SDL
	{


		//class Sound
		
//		int Sound::resourcecount = 0;
		
		Sound::Sound(std::string filename, bool loop_status) throw ( std::logic_error)
		try
		{
#ifdef DEBUG
			Log << nl << "Sound::Sound(" << filename << ") called";
#endif
			SDL_AudioSpec * _aspec = new SDL_AudioSpec();

			Uint32 len;
			if ( SDL_LoadWAV(filename.c_str(),_aspec,&_buf,&len) == NULL)
				throw std::logic_error(" Unable to open the sound file !");

			_length = static_cast<unsigned long>(len);
			_aInfo = new AudioInfo(_aspec);

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

		Sound::Sound( const Sound & s)
{
			
#ifdef DEBUG
			Log << nl << "Sound::Sound(" << &s << ") called";
#endif
			//TODO : manual allocation or use of SDL_LoadWAV_RW (RWops)
	
			_aInfo = new AudioInfo(s._aInfo->_spec);

			_length=s._length;
			_buf= new Uint8[s._length];
			for (unsigned int i=0; i<s._length; i++)
			{
				_buf[i] = s._buf[i];
			}
			
			_loop_status=s._loop_status;

#ifdef DEBUG
			Log << nl << "Sound::Sound(" << &s << ") done";
#endif
}
		
 int Sound::Convert (int DestinationFormat,int DestinationChannels,int DestinationFrequency)
{
#ifdef DEBUG
	Log << nl << "Sound::Convert(" << DestinationFormat << " , " << DestinationChannels<< " , " << DestinationFrequency << ") called";
#endif


	//AudioConvert cvt = new AudioConvert(_aInfo->_spec->format, _aInfo->_spec->channels, _aInfo->_spec->freq, DestinationFormat,DestinationChannels,DestinationFrequency);
	SDL_AudioCVT * _convertTable = new SDL_AudioCVT();

				if (SDL_BuildAudioCVT(_convertTable, _aInfo->_spec->format, _aInfo->_spec->channels, _aInfo->_spec->freq,
				    DestinationFormat, DestinationChannels, DestinationFrequency) < 0)
				{
					throw std::logic_error("Impossible de construire le convertisseur audio!");
				}
				
	//cvt.fillBuffer(_length, _buf);
				_convertTable->len = _length;
				_convertTable->buf = new Uint8[_convertTable->len*_convertTable->len_mult];
				for (unsigned int i=0; i< _length; i++)
				{
					_convertTable->buf[i] = _buf[i];
				}
	

#ifdef DEBUG
	Log << nl << "Sound::Convert(" << DestinationFormat << " , " << DestinationChannels<< " , " << DestinationFrequency << ") called";
#endif
	//return cvt.convert();
	int res = SDL_ConvertAudio(_convertTable);

	_length = _convertTable->len_cvt;
	_buf = _convertTable->buf;

// 	_aInfo->_spec->format = DestinationFormat;
// 	_aInfo->_spec->channels = DestinationChannels;
// 	_aInfo->_spec->freq = DestinationFrequency;
//

	//TODO : find a way to have an accurate AudioInfo after convert
	
	delete _convertTable;
	//TODO : change this to bool with a check
	return res;
	
}

		Sound::~Sound()
{
			
#ifdef DEBUG
			Log << nl << "Sound::~Sound() called";
#endif
			SDL_FreeWAV(_buf);
			
#ifdef DEBUG
			Log << nl << "Sound::~Sound() done";
#endif
}
	}
}
