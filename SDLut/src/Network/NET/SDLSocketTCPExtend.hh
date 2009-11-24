#ifndef SDLSOCKETTCPEXTEND_HH
#define SDLSOCKETTCPEXTEND_HH

#include "Network/SDLSocketTCP.hh"
#include "SDLConfig.hh"

typedef struct _TCPsocket *TCPsocket;

namespace RAGE
{
namespace SDL
{

//if SDL_Mixer is used, provide a class to be used as a bridge.
//this way the client doesnt have to take care of which function is available
#ifdef WK_SDLNET_FOUND

class SocketTCPExtend : public SocketTCPIf
{
    TCPsocket pvm_tcpsocket;
    IPaddress pvm_ip;

private:

    SocketTCPExtend(const TCPsocket & tcpsocket);

public:
    SocketTCPExtend( unsigned short port, bool localonly = false) throw (std::logic_error);
    SocketTCPExtend(std::string host, unsigned short port) throw (std::logic_error);

    //which behaviour on copy ?
    SocketTCPExtend(const SocketTCPExtend &) throw (std::logic_error);

    ~SocketTCPExtend();

    std::auto_ptr<SocketTCPIf> accept();

    bool isServer();
    std::string gethost()
    {
        const char * host = SDLNet_ResolveIP(&pvm_ip);
        if (host != NULL) return std::string(host);
        else return "Unknown";
    }
    unsigned short getport()
    {
        return static_cast<unsigned short>(pvm_ip.port);
    }

    //TODO : streams here
    int send(const void * data, int len);
    int receive(void * data, int maxlen);

    bool isNETImpl()
    {
        return true;
    }

    TCPsocket& get_rNET();
};
#endif
}
}
#endif
