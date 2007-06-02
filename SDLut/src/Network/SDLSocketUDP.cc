#include "Network/SDLSocketUDP.hh"

#include "SDLConfig.hh"

#include "Default/SDLSocketUDPImpl.hh"
#include "NET/SDLSocketUDPExtend.hh"

namespace RAGE
{
	namespace SDL
	{

	SocketUDPIf::SocketUDPIf() throw (std::logic_error)
	{
	}
	
	SocketUDPIf::SocketUDPIf( const SocketUDPIf & s)  throw (std::logic_error)
	{
	}



	SocketUDP::SocketUDP() throw (std::logic_error)
	{
	}
	
	SocketUDP::SocketUDP(const SocketUDP &) throw (std::logic_error)
	{
	}
	
	SocketUDP::~SocketUDP()
	{
	}

	
	}
}





