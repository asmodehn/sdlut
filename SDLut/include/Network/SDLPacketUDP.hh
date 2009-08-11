#ifndef SDLPACKETUDP_HH
#define SDLPACKETUDP_HH

#include <memory>
#include <string>
#include <stdexcept>

namespace RAGE
{
namespace SDL
{

/**
 * \class PacketUDPIf
 *
 * \ingroup Network
 *
 * \brief This class may interface different PacketUDP Implementations
 *
 * This class is an interface for different implementation of PacketUDP.
 *
 * \note
 *
 * \author Alex
 *
 * \date 2007/05/30
 *
 * Contact: asmodehn@gna.org
 *
 */


//using Pimpl idiom to hide use of optional dependencies or fallback behaviour
class PacketUDPIf
{
public:

    PacketUDPIf() throw (std::logic_error);
    PacketUDPIf(const PacketUDPIf &) throw (std::logic_error);

    virtual bool isNETImpl() = 0 ;

    virtual ~PacketUDPIf() {};
};

/**
 * \class PacketUDP
 *
 * \ingroup NetWork
 *
 * \brief This class handles and UDP Packet
 *
 * This class wraps PacketUDP from SDL_net if present, or implements a fallback behavior using a file-based data transfert.
 *
 * \note
 *
 * \author Alex
 *
 * \date 2007/05/30
 *
 * Contact: asmodehn@gna.org
 *
 */

class PacketUDP
{

private :
    std::auto_ptr<PacketUDPIf> pvm_packetUDPimpl;

public:
    PacketUDP() throw (std::logic_error);
    PacketUDP(const PacketUDP &) throw (std::logic_error);
    ~PacketUDP();

};

}
}
#endif
