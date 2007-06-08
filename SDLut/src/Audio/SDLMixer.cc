#include "Audio/SDLMixer.hh"

#include "SDLConfig.hh"

#include "Default/SDLMixerImpl.hh"
#include "MIX/SDLMixerExtend.hh"

namespace RAGE
{
	namespace SDL
	{
	
	Mixer::Mixer(int frequency /*= 44100*/,unsigned short channels /*= 2*/,unsigned short samples /*= 512*/) throw (std::logic_error)
	try : pvm_mixerimpl(0)
	{
#ifdef HAVE_SDLMIXER
		pvm_mixerimpl.reset( new MixerExtend(frequency, channels, samples) );
#else
		pvm_mixerimpl.reset( new MixerImpl(frequency,channels,samples) );
#endif

	}
	catch (std::exception & e)
	{
		Log << nl << e.what();
	}
	
	Mixer::Mixer(const Mixer & m)
	: pvm_mixerimpl( 0 )
	{
		if ( m.pvm_mixerimpl.get() )
		{
			if (m.pvm_mixerimpl->isMIXImpl() )
			{
				pvm_mixerimpl.reset(new MixerExtend(static_cast<MixerExtend&>(*m.pvm_mixerimpl)));
			}
			else
			{
				pvm_mixerimpl.reset(new MixerImpl(static_cast<MixerImpl&>(*m.pvm_mixerimpl)));
			}
		}
	}
	
	Mixer::~Mixer()
	{
	}


	//global Audio methods
	std::string Mixer::getDriverName()
	{
		return pvm_mixerimpl->getDriverName();
	}
	
	bool Mixer::isPlaying(int index)
	{
		return pvm_mixerimpl->isPlaying(index);
	}

	bool Mixer::isPaused(int index)
	{
		return pvm_mixerimpl->isPaused(index);
	}
	
	//To convert a Sound and store it internally.
	int Mixer::playChannel(const Sound& sound, int volumepct, int loops, int fadeintime, int index)
	{
		return pvm_mixerimpl->playChannel(*sound.pvm_soundimpl, volumepct, loops, fadeintime, index);
	}

	void Mixer::pauseChannel(int index)
	{
		pvm_mixerimpl->pauseChannel(index);
	}
	
	void Mixer::resumeChannel(int index)
	{
		pvm_mixerimpl->resumeChannel(index);
	}
	
	int Mixer::stopChannel(int index, int fadeouttime)
	{
		return pvm_mixerimpl->stopChannel(index,fadeouttime);
	}
	
	int Mixer::setChannelsNumber(int nbr)
	{
		return pvm_mixerimpl->setChannelsNumber(nbr);
	}
	

	bool Mixer::playMusic(const Music& music, int volumepct, int loops, int fadeintime, int index)
	{
		return pvm_mixerimpl->playMusic(*music.pvm_musicimpl,volumepct,loops,fadeintime,index);
	}

	void Mixer::pauseMusic()
	{
		pvm_mixerimpl->pauseMusic();
	}
	
	void Mixer::resumeMusic()
	{
		pvm_mixerimpl->resumeMusic();
	}

	void Mixer::rewindMusic()
	{
		pvm_mixerimpl->rewindMusic();
	}
	
	bool Mixer::setMusicPosition(double pos)
	{
		return pvm_mixerimpl->setMusicPosition(pos);
	}
	int Mixer::setMusicVolume( int volumepct )
	{
		return pvm_mixerimpl->setMusicVolume(volumepct);
	}
	
	bool Mixer::stopMusic(int fadeouttime)
	{
		return pvm_mixerimpl->stopMusic(fadeouttime);
	}
	
	}
}
