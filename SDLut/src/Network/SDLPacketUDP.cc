#include "Network/SDLPacketUDP.hh"

#include "SDLConfig.hh"

#include "Default/SDLPacketUDPImpl.hh"
#include "NET/SDLPacketUDPExtend.hh"

namespace SDLut
{
namespace network
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





