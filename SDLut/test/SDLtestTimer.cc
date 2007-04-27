
/* Test program to test the timer callbacks
*/

#include <iostream>
#include "SDL.hh"
using namespace RAGE;

static long ticks;


class ObjectWithCallback2
{
	public:
		
	unsigned int callback2_1(unsigned int interval, void* args)
	{
		std::cout << SDL::GetTicks() - ticks  << " ms : Instance 2 Method 1 Called back ! " << std::endl;
		return 0; //stop timer
	}
		
};

class ObjectWithMethod
{
	public:
	
	SDL::Timer<ObjectWithCallback2>* timer2_1;
	ObjectWithCallback2* myObjectWithCallback2;
		
	ObjectWithMethod()
	{
		myObjectWithCallback2 = new ObjectWithCallback2();

		timer2_1 = new SDL::Timer<ObjectWithCallback2>;
		timer2_1->setInterval(100);
		timer2_1->setCallback(myObjectWithCallback2,&ObjectWithCallback2::callback2_1,(void*)NULL);
	}

	~ObjectWithMethod()
	{
		delete myObjectWithCallback2, myObjectWithCallback2 = NULL;
		timer2_1->stop();
		delete timer2_1, timer2_1 = NULL;
	}

	bool Method()
	{
		//start the timer from the other class
		timer2_1->stop();
		timer2_1->start();
		return true;
	}
		
};

class ObjectWithCallback
{
	public:
	
	ObjectWithMethod* myObjectWithMethod;

	ObjectWithCallback()
	{
		myObjectWithMethod = new ObjectWithMethod();
	}
	~ObjectWithCallback()
	{
		delete myObjectWithMethod, myObjectWithMethod = NULL;
	}
		
	unsigned int callback1_1(unsigned int interval, void* args)
	{
		std::cout << SDL::GetTicks() - ticks  << " ms : Instance 1 Method 1 Called back ! " << std::endl;
		return 0;
	}
	
	unsigned int callback1_2(unsigned int interval, void* args)
	{
		//this should be only called 3 times
		static int iter = 5;
		std::cout << SDL::GetTicks() - ticks  << " ms : Instance 1 Method 2 Called back ! Number: " << iter-- << std::endl;

		if ( iter != 0 )
			return interval;

		//call the mehod which willll start another timer
		myObjectWithMethod->Method();

		//stop the current timer /*BUG HERE WE'RE NOT STOPPING JUST COZ OF THE START LINE 51*/
		return 0;
	}
};


static unsigned int callback(unsigned int interval, void * args)
{
	std::cout << SDL::GetTicks() - ticks  << " ms : Static Function called back !" << std::endl;
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
	timer1.setCallback(&obj,&ObjectWithCallback::callback1_1,(void*)NULL);
	timer2.setInterval(500);
	timer2.setCallback(&obj,&ObjectWithCallback::callback1_2,(void*)NULL);

	ticks = SDL::GetTicks();
	testlog << "Starting instance timer1 ( 2 sec )" << std::endl;
	timer1.start();
	testlog << "Starting instance timer 2 (every 500ms)" << std::endl;
	timer2.start();
	testlog << "Starting static SDL timer ( 4 sec )"<< std::endl;
	SDL::AddGlobalTimer(4000,callback,NULL);

	SDL::Delay(10000); //TODO Display time running

	return 0;
}
