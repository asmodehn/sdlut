#ifndef SDLSOCKETTCP_HH
#define SDLSOCKETTCP_HH

#include <memory>
#include <string>
#include <stdexcept>

#include "Logger.hh"

namespace SDLut
{
namespace network
{

/**
 * \class SocketTCPIf
 *
 * \ingroup Audio
 *
 * \brief This class may interface different SocketTCP Implementations
 *
 * This class if an interface for different implementation of SocketTCP.
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
class SocketTCPIf
{
public:

    virtual std::auto_ptr<SocketTCPIf> accept() = 0;

    virtual bool isServer() = 0;
    virtual std::string gethost() =0 ;
    virtual unsigned short getport() =0 ;

    //TODO : streams here
    virtual int send(const void * data, int len) =0;
    virtual int receive(void * data, int maxlen) =0;
    virtual bool isNETImpl() = 0 ;

    virtual ~SocketTCPIf() {};
};

/**
 * \class SocketTCP
 *
 * \ingroup NetWork
 *
 * \brief This class handles SocketTCP
 *
 * This class wraps SocketTCP from SDL_net if present, or implements a fallback behavior if using only SDL
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

class SocketTCP
{

private :
    std::auto_ptr<SocketTCPIf> pvm_sockettcpimpl;

    SocketTCP(std::auto_ptr<SocketTCPIf> stcpif );


    //which behaviour on copy ?
    SocketTCP(const SocketTCP &) throw (std::logic_error);


public:
    SocketTCP( unsigned short port, bool localonly = false) throw (std::logic_error);
    SocketTCP(std::string host, unsigned short port) throw (std::logic_error);

    ~SocketTCP();

    std::auto_ptr<SocketTCP> accept();

    bool isServer() const;
    std::string gethost() const;
    unsigned short getport() const;

    //TODO : streams here
    int send(const void * data, int len);
    int receive(void * data, int maxlen);

    friend Core::Logger & operator << (Core::Logger & log, const SocketTCP & sock);
};

}
}
#endif
