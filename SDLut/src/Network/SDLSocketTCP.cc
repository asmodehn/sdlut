#include "Network/SDLSocketTCP.hh"

#include "SDLConfig.hh"

#include "Default/SDLSocketTCPImpl.hh"
#include "NET/SDLSocketTCPExtend.hh"

namespace RAGE
{
	namespace SDL
	{

SocketTCP::SocketTCP(std::auto_ptr<SocketTCPIf> stcpif)
{
	pvm_sockettcpimpl = stcpif;
}
		
SocketTCP::SocketTCP( unsigned short port, bool localonly) throw (std::logic_error)
#ifdef HAVE_SDLNET
try : pvm_sockettcpimpl(new SocketTCPExtend(port,localonly))
#else
try : pvm_sockettcpimpl(new SocketTCPImpl(port, localonly))
#endif
{
}
catch (std::exception &e)
{
	Log << nl << "Exception in SocketTCP::SocketTCP(" << port << ", " << localonly << ") !";
	Log << nl << e.what();
}

SocketTCP::SocketTCP(std::string host, unsigned short port) throw (std::logic_error)
#ifdef HAVE_SDLNET
try : pvm_sockettcpimpl(new SocketTCPExtend(host,port))
#else
try : pvm_sockettcpimpl(new SocketTCPImpl(host, port))
#endif
{
}
catch (std::exception &e)
{
	Log << nl << "Exception in SocketTCP::SocketTCP(" << host << ", " << port << ") !";
	Log << nl << e.what();
}

//which behaviour on copy ?
SocketTCP::SocketTCP(const SocketTCP &) throw (std::logic_error)
{
}
		
SocketTCP::~SocketTCP()
{
	//auto_ptr calls pvm_sockettcpimpl destructor
}

std::auto_ptr<SocketTCP> SocketTCP::accept()
{
	return std::auto_ptr<SocketTCP>(new SocketTCP(pvm_sockettcpimpl->accept()));
}

bool SocketTCP::isServer() const
{
	return pvm_sockettcpimpl->isServer();
}

std::string SocketTCP::gethost() const
{
	return pvm_sockettcpimpl->gethost();
}

unsigned short SocketTCP::getport() const
{
	return pvm_sockettcpimpl->getport();
}

//TODO : streams here
int SocketTCP::send(const void * data, int len)
{
	return pvm_sockettcpimpl->send(data, len);
}

int SocketTCP::receive(void * data, int maxlen)
{
	return pvm_sockettcpimpl->receive(data, maxlen);
}

 Logger & operator << (Logger & log, const SocketTCP & sock)
        {
            log << nl << "SocketTCP::" << nl
            << " - Server ? " << std::boolalpha << sock.isServer() << nl
            << " - Host : " << sock.gethost() << nl
            << " - Port : " << sock.getport();
		return log;
        }
	
	}
}





