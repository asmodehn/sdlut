#include "SDLSocketTCPExtend.hh"
#include "SDLConfig.hh"

namespace RAGE
{
	namespace SDL
	{
#ifdef HAVE_SDLNET

		SocketTCPExtend::SocketTCPExtend(const TCPsocket & tcpsocket)
		try : pvm_tcpsocket(tcpsocket),  pvm_ip()
		{
			std::auto_ptr<IPaddress> peerad( SDLNet_TCP_GetPeerAddress(pvm_tcpsocket) );
			if (!peerad.get())
			{
				throw std::logic_error("GetPeerAddress() returned NULL");
			}
			else
			{
			pvm_ip.host = peerad->host;
			pvm_ip.port = peerad->port;
			}
		}
		catch( std::exception & e)
		{
			Log << nl << "Exception in SocketTCPExtend::SocketTCPExtend(" << tcpsocket<< ")";
			Log<< nl << e.what();
		}
		
		SocketTCPExtend::SocketTCPExtend( unsigned short port, bool localonly) throw (std::logic_error)
		try : pvm_tcpsocket(0),  pvm_ip()
		{
			if (SDLNet_ResolveHost(&pvm_ip, NULL , static_cast<Uint16>(port) ) == -1 )
			{
				throw std::logic_error("SDLNet_ResolveHost() returned -1");
			}
			if ( (pvm_tcpsocket = SDLNet_TCP_Open(&pvm_ip)) == NULL )
			{
				throw std::logic_error("SDLNet_TCP_Open() returned -1");
			}
		}
		catch( std::exception & e)
		{
			Log << nl << "Exception in SocketTCPExtend::SocketTCPExtend(" << port << ", " << localonly << ")";
			Log<< nl << e.what();
		}
		
		SocketTCPExtend::SocketTCPExtend(std::string host, unsigned short port) throw (std::logic_error)
		try : pvm_tcpsocket(0),  pvm_ip()
		{
			if (SDLNet_ResolveHost(&pvm_ip, host.c_str(), static_cast<Uint16>(port) ) == -1 )
			{
				throw std::logic_error("SDLNet_ResolveHost() returned -1");
			}
			if ( (pvm_tcpsocket = SDLNet_TCP_Open(&pvm_ip)) == NULL )
			{
				throw std::logic_error("SDLNet_TCP_Open() returned NULL");
			}
		}
		catch( std::exception & e)
		{
			Log << nl << "Exception in SocketTCPExtend::SocketTCPExtend(" << host<< ", " << port << ")";
			Log<< nl << e.what();
		}
		
		SocketTCPExtend::SocketTCPExtend(const SocketTCPExtend::SocketTCPExtend &) throw (std::logic_error)
		{
			//behaviour on copy ??
		}

		std::auto_ptr<SocketTCPIf> SocketTCPExtend::accept()
		{
			return std::auto_ptr<SocketTCPIf>(new SocketTCPExtend(SDLNet_TCP_Accept(pvm_tcpsocket)));
		}
		
		SocketTCPExtend::~SocketTCPExtend()
		{
			SDLNet_TCP_Close(pvm_tcpsocket);
		}

		bool SocketTCPExtend::isServer()
		{
			std::auto_ptr<IPaddress> peerad( SDLNet_TCP_GetPeerAddress(pvm_tcpsocket) );
			if (!peerad.get()) return true;
			return false;
		}

		//TODO : streams here
		int SocketTCPExtend::send(const void * data, int len)
		{
			return SDLNet_TCP_Send(pvm_tcpsocket, data,len);
		}
		
		int SocketTCPExtend::receive(void * data, int maxlen)
		{
			return SDLNet_TCP_Recv(pvm_tcpsocket, data, maxlen);
		}

		TCPsocket& SocketTCPExtend::get_rNET()
		{
			return pvm_tcpsocket;
		}

		
#endif
	}
}
