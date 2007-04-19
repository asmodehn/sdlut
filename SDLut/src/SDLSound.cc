#include "SDLSound.hh"
#include "SDLConfig.hh"

namespace RAGE
{
	namespace SDL
	{

		std::map<AudioInfo*,int> Sound::airef;

		//class Sound
		
//		int Sound::resourcecount = 0;
		
		Sound::Sound(std::string filename, bool loop_status) throw ( std::logic_error)
			try : frommem(false)
		{
#ifdef DEBUG
			Log << nl << "Sound::Sound(" << filename << ") called";
#endif
			SDL_AudioSpec * _aspec = new SDL_AudioSpec();
			
			Uint32 len;
			if ( SDL_LoadWAV(filename.c_str(),_aspec,&_buf,&len) == NULL)
			{
				delete _aspec;
				throw std::logic_error(" Unable to open the sound file !");
			}

			_length = static_cast<unsigned long>(len);
			_aInfo = new AudioInfo(_aspec);

			//SDL_FreeWAV(_buf);
			//OK

			airef[_aInfo] = 1;

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
			//TODO :use of SDL_LoadWAV_RW (RWops) !!!
	
			_aInfo = s._aInfo;

			_length=s._length;
			_buf= new Uint8[s._length];
			for (unsigned int i=0; i<s._length; i++)
			{
				_buf[i] = s._buf[i];
			}
			//SDL_FreeWAV(s._buf);
			//SDL_FreeWAV(_buf); //crash

			_loop_status=s._loop_status;

			airef[_aInfo] ++;
			frommem=true;
#ifdef DEBUG
			Log << nl << "Sound::Sound(" << &s << ") done";
#endif
}
		
 bool Sound::Convert (int DestinationFormat,int DestinationChannels,int DestinationFrequency)
{
#ifdef DEBUG
	Log << nl << "Sound::Convert(" << DestinationFormat << " , " << DestinationChannels<< " , " << DestinationFrequency << ") called";
#endif


	//AudioConvert cvt = new AudioConvert(_aInfo->_spec->format, _aInfo->_spec->channels, _aInfo->_spec->freq, DestinationFormat,DestinationChannels,DestinationFrequency);
	SDL_AudioCVT * _convertTable = new SDL_AudioCVT();

				if (SDL_BuildAudioCVT(_convertTable, _aInfo->_spec->format, _aInfo->_spec->channels, _aInfo->_spec->freq,
				    (Uint16) DestinationFormat, (Uint8) DestinationChannels, DestinationFrequency) < 0)
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

	if (res !=-1)
	{
		_length = _convertTable->len_cvt;
		if (_buf!=NULL) delete[] _buf, _buf=NULL;
		_buf = _convertTable->buf;
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
	
	delete _convertTable;
	
	return res == 0;
	
}

		Sound::~Sound()
{
			
#ifdef DEBUG
			Log << nl << "Sound::~Sound() called";
#endif
			if ( --airef[_aInfo] == 0 ) 
			{
				delete _aInfo,_aInfo = NULL;
			}
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
