#ifndef SDLSOCKETUDP_HH
#define SDLSOCKETUDP_HH

#include <memory>
#include <string>
#include <stdexcept>

namespace RAGE
{
namespace SDL
{

/**
 * \class SocketUDPIf
 *
 * \ingroup Network
 *
 * \brief This class may interface different SocketUDP Implementations
 *
 * This class if an interface for different implementation of SocketUDP.
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
class SocketUDPIf
{
public:
    SocketUDPIf() throw (std::logic_error);
    SocketUDPIf( const SocketUDPIf & s)  throw (std::logic_error);

    virtual bool isNETImpl() = 0 ;

    virtual ~SocketUDPIf() {};
};

/**
 * \class SocketUDP
 *
 * \ingroup NetWork
 *
 * \brief This class handles SocketUDP
 *
 * This class wraps SocketUDP from SDL_net if present, or implements a fallback behavior if using only SDL
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

class SocketUDP
{
private :
    std::auto_ptr<SocketUDPIf> pvm_socketUDPimpl;

public:
    SocketUDP() throw (std::logic_error);
    SocketUDP(const SocketUDP &) throw (std::logic_error);
    ~SocketUDP();
};

}
}
#endif
