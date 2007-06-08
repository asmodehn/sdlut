#ifndef SDLMIXER_HH
#define SDLMIXER_HH

#include "SDLSound.hh"
#include "SDLMusic.hh"

#include <memory>
#include <map>

namespace RAGE
{
    namespace SDL
    {

/**
 * \class MixerIf
 *
 * \ingroup Audio
 *
 * \brief This class may interface different Mixer Implementations
 *
 * This class if an interface for different implementation of Mixer.
 *
 * \note
 *
 * \author Alex
 *
 * \date 2007/05/24
 *
 * Contact: asmodehn@gna.org
 *
 */


//using Pimpl idiom to hide use of optional dependencies or fallback behaviour
class MixerIf
{
	public :
	virtual bool isMIXImpl() = 0 ;
	virtual ~MixerIf() {} ;

	virtual std::string getDriverName() = 0;
	virtual bool isPlaying(int index) =0;
	virtual bool isPaused(int index) =0;

	//To play a sound on a channel
	virtual int playChannel(const SoundIf& sound, int volumepct = 100, int loops = 0, int fadeintime = 0, int index = -1) = 0;
	virtual void pauseChannel(int index) =0;
	virtual void resumeChannel(int index) =0;
	virtual int stopChannel(int index, int fadeouttime = 0) =0;
		
	virtual int setChannelsNumber(int nbr) =0;

	//To play a music on the specific channel
	virtual bool playMusic(const MusicIf& music, int volumepct = 100, int loops = 1, int fadeintime = 0, int index = -1) =0;

	virtual void pauseMusic() =0;
	virtual void resumeMusic()=0;
	virtual void rewindMusic()=0;
	virtual bool setMusicPosition(double pos)=0;
	virtual int setMusicVolume( int volumepct )=0;
	virtual bool stopMusic(int fadeouttime = 0) =0;
	
};


/**
 * \class Mixer
 *
 * \ingroup Audio
 *
 * \brief This class handles Audio Mixer
 *
 * This class wraps Mixer from SDL_mixer if present, or implements a fallback behavior if using only SDL
 *
 * \note
 *
 * \author Alex
 *
 * \date 2007/05/15
 *
 * Contact: asmodehn@gna.org
 *
 */

class Mixer
{
private :
	std::auto_ptr<MixerIf> pvm_mixerimpl;
	
public:

	Mixer(int frequency = 44100,unsigned short channels = 2,unsigned short samples = 512) throw (std::logic_error);
	Mixer(const Mixer& m);
	~Mixer();

		
	//global Audio methods
	std::string getDriverName();
	bool isPlaying(int index);
	bool isPaused(int index);
	
	
	//To convert a Sound and store it internally.
	int playChannel(const Sound& sound, int volumepct = 100, int loops = 0, int fadeintime = 0, int index = -1);
	void pauseChannel(int index);
	void resumeChannel(int index);
	int stopChannel(int index, int fadeouttime = 0);
	
	int setChannelsNumber(int nbr);

	//To play music
	bool playMusic(const Music& music, int volumepct = 100, int loops = 1, int fadeintime = 0, int index = -1);

	void pauseMusic();
	void resumeMusic();
	void rewindMusic();
	bool setMusicPosition(double pos);
	int setMusicVolume( int volumepct );
			
	bool stopMusic(int fadeouttime = 0);

};

	}
}
#endif
