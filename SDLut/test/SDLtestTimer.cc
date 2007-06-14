
/* Test program to test the timer callbacks
*/

#include <iostream>
#include "SDL.hh"
using namespace RAGE;

static long ticks;

Logger testlog("testTimer");

static unsigned int callback(unsigned int interval, void * args)
{
	testlog << nl << SDL::GetTicks() - ticks  << " ms : Static Function called back !" ;
	return 0;
}

class ObjectWithCallback
{
	public:
	
	unsigned int callback1_1(unsigned int interval, void* args)
	{
		testlog << nl << SDL::GetTicks() - ticks  << " ms : Instance 1 Method 1 Called back ! " << std::endl;
		return 0;
	}
	
	unsigned int callback1_2(unsigned int interval, void* args)
	{
		//this should be only called 3 times
		static int iter = 5;
		testlog << nl << SDL::GetTicks() - ticks  << " ms : Instance 1 Method 2 Called back ! Number: " << iter-- ;

		if ( iter != 0 )
			return interval;

		//SDL doesnt support calling timer from another timer ( because of threads implementation differences )
		//However SDLut implemented a workaround for timer called from another timer. seems to work fine so far
		//SDL::AddGlobalTimer(50,callback,NULL);

		return 0;
	}
};


int main(int argc, char *argv[])
{
	testlog << nl<<"SDL init...";

	SDL::App::getInstance().initTimer();
			
	testlog << nl<<"Creating instance";
	ObjectWithCallback obj;

	testlog << nl<<"Creating instance timer";
	SDL::Timer<ObjectWithCallback> timer1;
	SDL::Timer<ObjectWithCallback> timer2;

	timer1.setCallback(&obj,&ObjectWithCallback::callback1_1,(void*)NULL);
	timer2.setCallback(&obj,&ObjectWithCallback::callback1_2,(void*)NULL);

	ticks = SDL::GetTicks();
	testlog << nl << "Starting instance timer1 ( 2 sec )";
	timer1.launch(2000);
	
	testlog << nl <<"Starting instance timer 2 (every 200ms)";
	timer2.launch(200);

	testlog << nl << "Aborting instance timer1";
	timer1.abort();
		
	SDL::Delay(10000); //TODO Display time running

	return 0;
}
