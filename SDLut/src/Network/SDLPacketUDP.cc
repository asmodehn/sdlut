#include "Network/SDLPacketUDP.hh"

#include "SDLConfig.hh"

#include "Default/SDLPacketUDPImpl.hh"
#include "NET/SDLPacketUDPExtend.hh"

namespace RAGE
{
	namespace SDL
	{

	PacketUDPIf::PacketUDPIf() throw (std::logic_error)
	{
	}
	
	PacketUDPIf::PacketUDPIf( const PacketUDPIf & s)  throw (std::logic_error)
	{
	}



	PacketUDP::PacketUDP() throw (std::logic_error)
	{
	}
	
	PacketUDP::PacketUDP(const PacketUDP &) throw (std::logic_error)
	{
	}
	
	PacketUDP::~PacketUDP()
	{
	}

	
	}
}





