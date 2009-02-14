
/* Test program to test the timer callbacks
*/

#include <iostream>
#include "SDL.hh"
using namespace RAGE;

static long ticks;

Logger testlog("testTimer");

/*static unsigned int callback(unsigned int interval, void * args)
{
	testlog << nl << SDL::GetTicks() - ticks  << " ms : Static Function called back !" ;
	return 50;
}*/

class SimpleObject
{
	friend class ObjectWithCallback;

protected:
	int callback_interval;
	SimpleObject(const int& callback_interval)
	{
		this->callback_interval = callback_interval;
		
		direct_timer_it = 5;
	}

	int direct_timer_it;
};

class ObjectWithCallback
{
private:
	SDL::Timer<ObjectWithCallback> *Play_Timer_1;
	SDL::Timer<ObjectWithCallback> *Play_Timer_2;
	SimpleObject *sobj;
	

public:
	ObjectWithCallback(const int& callback_interval) : sobj(NULL), Play_Timer_1(NULL), Play_Timer_2(NULL)
	{
		Play_Timer_1 = new SDL::Timer<ObjectWithCallback>();
		Play_Timer_2 = new SDL::Timer<ObjectWithCallback>();
		sobj = new SimpleObject(callback_interval);
		
	}

	~ObjectWithCallback()
	{
		delete Play_Timer_1, Play_Timer_1 = NULL;
		delete Play_Timer_2, Play_Timer_2 = NULL;
		delete sobj, sobj = NULL;
	}

	void play1_1()
	{
		Play_Timer_1->setCallback(this,&ObjectWithCallback::callback1_1, NULL);
		if (! Play_Timer_1->launch( 1 ) )
		{
			throw std::logic_error("Unable to launch the callback on Play_Timer_1");
		}
	}
	void play1_2()
	{
		Play_Timer_2->setCallback(this,&ObjectWithCallback::callback1_2, NULL);
		if (! Play_Timer_2->launch( 1 ) )
		{
			throw std::logic_error("Unable to launch the callback on Play_Timer_2");
		}
	}

private:
	unsigned int callback1_1(unsigned int interval, void* args)
	{
		testlog << nl << SDL::GetTicks() - ticks  << " ms : callback1_1 Called back ! " << std::endl;
		return sobj->callback_interval;
	}
	unsigned int callback1_2(unsigned int interval, void* args)
	{
		testlog << nl << SDL::GetTicks() - ticks  << " ms : callback1_2 Called back ! " << std::endl;
		return sobj->callback_interval;
	}

public:
	unsigned int callback2(unsigned int interval, void* args)
	{
		//call the timer 5 times
		//static int iter = 5;

		testlog << nl << SDL::GetTicks() - ticks  << " ms : direct callback2 Called back ! Number: " << sobj->direct_timer_it-- ;

		//SDL doesnt support calling timer from another timer ( because of threads implementation differences )
		//However SDLut implemented a workaround for timer called from another timer. seems to work fine so far
		//static SDL_TimerID gt_id = SDL::AddGlobalTimer(50,callback,NULL);

		if ( sobj->direct_timer_it != 0 )
			return interval;

		//SDL::RemoveGlobalTimer(gt_id);
		testlog << nl << "Stopping direct timer" << std::endl;
		return 0;
	}
};


int main(int argc, char *argv[])
{
try {
	testlog.enableFileLog("testTimer.log");
	testlog << nl<<"SDL init...";

	SDL::App::getInstance().initTimer();
			
	testlog << nl<<"Creating instance";
	ObjectWithCallback* obj = new ObjectWithCallback(80);

	testlog << nl<<"Creating instance timer";
	SDL::Timer<ObjectWithCallback> direct_timer;

	direct_timer.setCallback(obj,&ObjectWithCallback::callback2,(void*)NULL);

	//ticks = SDL::GetTicks();
	testlog << nl << "Starting instance timer1_x ( 80ms )";
	obj->play1_1();
	obj->play1_2();
	
	testlog << nl <<"Starting instance timer 2 (every 200ms)";
	direct_timer.launch(200);

		
	SDL::Delay(5000); //TODO Display time running
	
	testlog << nl <<"Cleaning and finished";
	direct_timer.abort();
	delete obj, obj = NULL;

	return 0;
} catch (std::exception &exc) {
		testlog << nl<< exc.what();
}
}
