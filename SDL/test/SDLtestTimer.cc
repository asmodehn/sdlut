
/* Test program to test the timer callbacks
*/

#include <iostream>
#include "SDL.hh"
using namespace RAGE;

class ObjectWithCallback
{


	public:
		
	unsigned int callback(unsigned int interval, void* args)
	{
		std::cout << "Instance Method Called back ! " << std::endl;
		return 0;
	}
};

static unsigned int callback(unsigned int interval, void * args)
{
	std::cout << "Static Function called back !" << std::endl;
	return 0;
}

int main(int argc, char *argv[])
{
	Logger testlog("testver");

	testlog << "SDL init..." << std::endl;

	SDL::App::getInstance().initTimer();	
			
	testlog << "Creating instance"<< std::endl;
	ObjectWithCallback obj;

	testlog << "Creating instance timer" << std::endl;
	SDL::Timer<ObjectWithCallback> timer;

	timer.setInterval(2000);
	timer.setCallback(&obj,&ObjectWithCallback::callback,(void*)NULL);
	
	testlog << "Starting instance timer ( 2 sec )" << std::endl;
	timer.start();
	testlog << "Starting static SDL timer ( 4 sec )"<< std::endl;
	SDL_AddTimer(4000,callback,NULL);

	SDL::Delay(6000); //TODO Display time running

	return 0;
}
