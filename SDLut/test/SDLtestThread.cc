
/* Test program to test the thread callbacks
*/

#include <iostream>
#include "SDL.hh"
using namespace RAGE;

Logger testlog("testThread");

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
	SDL::Thread<ObjectWithThreadCall>* thread = new SDL::Thread<ObjectWithThreadCall>();

	thread->setThreadCall(obj,&ObjectWithThreadCall::threadcall,(void*)NULL);

	thread->run();

	testlog << nl<<"Waiting for thread" << std::endl;
	thread->wait();
	SDL::Delay(3000);
	testlog << nl <<"Killing thread: After That No Iteration Should Be Present" << std::endl;
	thread->kill();
	SDL::Delay(3000);
	return 0;
}
