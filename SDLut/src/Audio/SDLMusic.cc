#include "Audio/SDLMusic.hh"

#include "SDLConfig.hh"

#include "Default/SDLMusicImpl.hh"
#include "MIX/SDLMusicExtend.hh"

namespace RAGE
{
	namespace SDL
	{


MusicIf::MusicIf(std::string filename, bool loop_status) throw (std::logic_error)
//try : pvm_OriginalData(new RWOps(filename.c_str(), "rb"))
try : pvm_OriginalFilename(filename)
{
// 	if ( !pvm_OriginalData.get() )
// 	{
// 		throw std::logic_error(" Unable to access the sound file !");
// 	}
// 	pvm_OriginalData->seek(0,RWOps::Set);
}
catch (std::exception &e )
{
	Log << nl << " Exception caught in MusicIf::MusicIf()";
	Log << nl << e.what();
}

MusicIf::MusicIf(const MusicIf & m) throw (std::logic_error)
//try : pvm_OriginalData(s.pvm_OriginalData.get() !=0 ? new RWOps(*s.pvm_OriginalData) : 0)
try : pvm_OriginalFilename(m.pvm_OriginalFilename)
{
// 	if ( ! pvm_OriginalData.get() )
// 	{
// 		throw std::logic_error(" Unable to access the sound in memory !");
// 	}
// 	pvm_OriginalData->seek(0,RWOps::Set);
}
catch (std::exception &e )
{
	Log << nl << " Exception caught in MusicIf::MusicIf( " << &m << " )";
	Log << nl << e.what();
}

		
		
	Music::Music(std::string filename, bool loop_status /* = false */) throw (std::logic_error)
	try : pvm_musicimpl(0)
	{
#ifdef HAVE_SDLMIXER
		pvm_musicimpl.reset( new MusicExtend(filename, loop_status) );
#else
		pvm_musicimpl.reset( new MusicImpl(filename, loop_status) );
#endif

	}
	catch (std::exception & e)
	{
		Log << nl << e.what();
	}
	
	Music::Music(const Music & s) throw (std::logic_error)
	try : pvm_musicimpl(0)
	{
		if ( s.pvm_musicimpl.get() )
		{
			if (s.pvm_musicimpl->isMIXImpl() )
			{
				pvm_musicimpl.reset(new MusicExtend(static_cast<MusicExtend&>(*s.pvm_musicimpl)));
			}
			else
			{
				pvm_musicimpl.reset(new MusicImpl(static_cast<MusicImpl&>(*s.pvm_musicimpl)));
			}
		}
	}
	catch (std::exception & e)
	{
		Log << nl << e.what();
	}
	
	Music::~Music()
	{
	}

	bool Music::Convert (unsigned short DestinationFormat,unsigned short DestinationChannels,int DestinationFrequency)
	{
		return pvm_musicimpl->Convert(DestinationFormat, DestinationChannels, DestinationFrequency);
	}

	}
}
