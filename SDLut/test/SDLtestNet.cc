#include "SDL.hh"
#include "Logger.hh"
using namespace RAGE;
using namespace RAGE::SDL;

Logger Log("Test Net");


//Main Program
int main(int argc, char** argv)
{

    Logger testlog("Test Log");

    //Setup example

    App::getInstance().setName ("RAGE::SDL test - Network");
    
	
	Log << nl << App::getInstance().init();
	
	Log << nl << App::getInstance().initNet();

	SocketTCP serversocket(6666);

	Log << nl <<serversocket;
			
	SocketTCP clientsocket("127.0.0.1",6666);

	Log << nl <<clientsocket;

	std::auto_ptr<SocketTCP> comsocket = serversocket.accept();
	
	std::string msg = "youhou !";
	int size = sizeof(msg);
	clientsocket.send(msg.c_str(),size);

	char * rcvdmsg;
	comsocket->receive(rcvdmsg,size);

	Log << nl << "Message : " << rcvdmsg;
	return 0;
}


