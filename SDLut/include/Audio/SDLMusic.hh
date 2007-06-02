#ifndef SDLMUSIC_HH
#define SDLMUSIC_HH

#include <memory>
#include <string>
#include <stdexcept>

#include "System/SDLRWOps.hh"

namespace RAGE
{
    namespace SDL
    {

/**
 * \class MusicIf
 *
 * \ingroup Audio
 *
 * \brief This class may interface different Music Implementations
 *
 * This class if an interface for different implementation of Music.
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
class MusicIf
{
	protected:
	//std::auto_ptr<RWOps> pvm_OriginalData;
	std::string pvm_OriginalFilename;
	
	public:
	//Sound Loader
	MusicIf(std::string filename, bool loop_status = false) throw (std::logic_error);
	//Sound Copy ( careful with conversion )
	MusicIf( const MusicIf & s)  throw (std::logic_error);
		
	virtual bool isMIXImpl() = 0 ;
	//careful here, the convert behavior of different implementation must match ( mixer convert on construction it seems...)
	virtual bool Convert (unsigned short DestinationFormat,unsigned short DestinationChannels,int DestinationFrequency) = 0 ;
	
	virtual ~MusicIf() {};
};

/**
 * \class Music
 *
 * \ingroup Audio
 *
 * \brief This class handles Music
 *
 * This class wraps Music from SDL_mixer if present, or implements a fallback behavior if using only SDL
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

class Music
{
	friend class Mixer;
	
private :
	std::auto_ptr<MusicIf> pvm_musicimpl;
	
	public:
	Music(std::string filename, bool loop_status = false) throw (std::logic_error);
	Music(const Music &) throw (std::logic_error);
	~Music();

	bool Convert (unsigned short DestinationFormat,unsigned short DestinationChannels,int DestinationFrequency);
};

	}
}
#endif
