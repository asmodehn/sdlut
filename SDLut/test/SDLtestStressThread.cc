
/* Test program to test the thread callbacks
*/

#include <iostream>
#include "SDL.hh"
using namespace SDLut;

RAGE::Logger testlog("testThread");

class ObjectWithThreadCall
{
	public:
	ObjectWithThreadCall() {}

	int threadcall(void* args)
	{
		testlog << nl << " --- Thread " << SDL::getCurrentThreadID() << "called. Counting from 0 to 20000 --- " << std::endl;
		for (int i = 0; i < 20000; i++)
		{
			testlog << nl << "Iteration N°" << i << std::endl;
		}
		return 0;
	}
};


int main(int argc, char *argv[])
{
	testlog.enableFileLog("testThread.log");
	testlog << nl<<"SDL init...";

	SDL::App::getInstance();

	testlog << nl<<"Creating instance";
	ObjectWithThreadCall * obj = new ObjectWithThreadCall();

	testlog << nl<<"Creating instance timer";
	SDL::NewThread<ObjectWithThreadCall>* thread = new SDL::NewThread<ObjectWithThreadCall>(obj,&ObjectWithThreadCall::threadcall,(void*)NULL);
	SDL::Delay(3000);

	if ( argc > 1 && std::string(argv[1]) == "wait" )
	{
		testlog << nl<< "Waiting for thread" << std::endl;
		thread->wait();
	}

	testlog << nl << "Main exit !"<< std::endl;
	//Reminder hte logger is not thread safe... concurrency access may cause problems...
	//such as not writing "Main exit" in the log file quick enough
	//because it s been used by the thread...
	//TODO : improve the test to avoid such issue... we shouldnt need to check a log file to determine if it s successful or not anyway...
	return 0;
}
