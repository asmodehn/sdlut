
/* Test program to test the timer callbacks
*/

#include <iostream>
#include "SDL.hh"
using namespace RAGE;

int loop_number = 0;

class ObjectWithCallback
{


	public:
		
	unsigned int callback1(unsigned int interval, void* args)
	{
		std::cout << "Instance Method 1 Called back ! " << std::endl;
		return 0;
	}
	
	unsigned int callback2(unsigned int interval, void* args)
	{
		//this should be only called 3 times
		static int iter = 5;
		std::cout << "Instance Method 2 Called back ! Number: " << iter-- << std::endl;
		if ( iter != 0 )
			return interval;
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
	Logger testlog("testTimer");

	testlog << "SDL init..." << std::endl;

	SDL::App::getInstance().initTimer();	
			
	testlog << "Creating instance"<< std::endl;
	ObjectWithCallback obj;

	testlog << "Creating instance timer" << std::endl;
	SDL::Timer<ObjectWithCallback> timer1;
	SDL::Timer<ObjectWithCallback> timer2;

	timer1.setInterval(2000);
	timer1.setCallback(&obj,&ObjectWithCallback::callback1,(void*)NULL);
	timer2.setInterval(0); //BUG!! when Interval = 0, the timer loop infinitly instead of exit like when there is the return 0;
	timer2.setCallback(&obj,&ObjectWithCallback::callback2,(void*)NULL);
	
	testlog << "Starting instance timer1 ( 2 sec )" << std::endl;
	timer1.start();
	testlog << "Starting instance timer2" << std::endl;
	timer2.start();
	testlog << "Starting static SDL timer ( 4 sec )"<< std::endl;
	SDL_AddTimer(4000,callback,NULL);

	SDL::Delay(6000); //TODO Display time running

	return 0;
}
