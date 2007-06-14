
/* Test program to test the thread callbacks
*/

#include <iostream>
#include "SDL.hh"
using namespace RAGE;

Logger testlog("testThread");

class ObjectWithThreadCall
{
	public:
	
	int threadcall(void* args)
	{
		testlog << nl << "Thread " << SDL::getCurrentThreadID() << "called " << std::endl;
		return 0;
	}
	
};


int main(int argc, char *argv[])
{
	testlog << nl<<"SDL init...";

	SDL::App::getInstance();
			
	testlog << nl<<"Creating instance";
	ObjectWithThreadCall obj;

	testlog << nl<<"Creating instance timer";
	SDL::Thread<ObjectWithThreadCall> thread;

	thread.setThreadCall(&obj,&ObjectWithThreadCall::threadcall,(void*)NULL);

	thread.run();

	testlog << nl<<"Waiting for thread to finish";
	thread.wait();
	
	return 0;
}
