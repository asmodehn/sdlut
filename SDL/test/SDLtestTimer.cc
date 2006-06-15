
/* Test program to test the timer callbacks
*/

#include <iostream>
#include "SDL.hh"
using namespace RAGE;

class ObjectWithCallback
{


	public:
	bool called;
		
	ObjectWithCallback() : called(false) {}
		
	unsigned int callback(unsigned int interval, void* args)
	{
		called = !called;
		std::cout << "Called changed to : " << called << std::endl;
		return 0;
	}
};


int main(int argc, char *argv[])
{
	Logger testlog("testver");

	testlog << "SDL init..." << std::endl;

	SDL::App::getInstance();
			
	testlog << "Creating object with callback after 2 seconds" << std::endl;
	ObjectWithCallback obj;

	SDL::Timer<ObjectWithCallback> timer;

	timer.setInterval(200);
	timer.setCallback(&obj,&ObjectWithCallback::callback,(void*)NULL);

	timer.start();

	while (!obj.called)
		SDL::Delay(1); //TODO Display time running

	testlog << "Called back : " << obj.called << std::endl;

	return 0;
}
