
/* Test program to test the timer callbacks
*/

#include <iostream>
#include "SDL.hh"
#include <ctime>
#include <sstream>
#include <cstdlib>

//to be able to easily remove the locks
#define SCOPED_LOCK(mtx) ScopedLock lock(mtx)
//#define SCOPED_LOCK(mtx)

using namespace RAGE;
using namespace RAGE::SDL;
using namespace std;

static long ticks;

Logger testlog("testTimer");

/*static unsigned int callback(unsigned int interval, void * args)
{
	testlog << nl << SDL::GetTicks() - ticks  << " ms : Static Function called back !" ;
	return 50;
}*/

int random(int min, int max)
{
	return min + (rand()%(max+1-min));
}

std::string Int_To_String(const int &to_convert)
{
	std::stringstream s;
    if (s << to_convert) // conversion worked
        return s.str();

	//failed
	return NULL;
}

class SimpleObject
{
	friend class ObjectWithCallbacks;
	friend class OwnerOfObjWCallbacks;
	friend class DerivateOwnerOfObjWCallbacks;

public:
	int callback_interval, cb_frames;
	SimpleObject()
	{
		callback_interval = random(50,100);
		cb_frames = random(5,9);
	}
};

class SimpleArgObject
{

public:
	int isao;

	SimpleArgObject()
	{
		isao = random(1,10);
	}
};

class ObjectWithCallbacks
{
	friend class OwnerOfObjWCallbacks;

private:
	SDL::NewTimer<ObjectWithCallbacks> *Play_Timer_1x;
	SimpleObject *sobj;

	int direct_timer_it, direct_timer_int;

	int loop_nb;

	long start_timer_tick;

	Mutex mymtx;

protected:
	int flag; //0: default|initial, 1: used by callback, 2: callback ended

public:
	ObjectWithCallbacks() : sobj(NULL), Play_Timer_1x(NULL)
	{
	try	{
		direct_timer_it = 8;
		direct_timer_int = 200;
		loop_nb = 0;

		flag = 0;
		start_timer_tick = 0;

		sobj = new SimpleObject();

	} catch (std::exception &exc) {
		Clean_ObjectWithCallbacks();
		throw std::logic_error("Error in ObjectWithCallbacks Constructor " + (string)exc.what() );
	} catch (...) {
		Clean_ObjectWithCallbacks();
		throw std::logic_error("Unhandled Error in ObjectWithCallbacks Constructor" );
	}
	}

	~ObjectWithCallbacks()
	{
		Clean_ObjectWithCallbacks();
	}

	void Clean_ObjectWithCallbacks()
	{
		if (Play_Timer_1x != NULL)
		{
			Play_Timer_1x->abort();
			delete Play_Timer_1x, Play_Timer_1x = NULL;
		}

		delete sobj, sobj = NULL;
	}

	//Manual abort
	void stop()
	{
SCOPED_LOCK(mymtx);

		if (Play_Timer_1x != NULL)
		{
			testlog << nl << Play_Timer_1x << " aborted by ObjectWithCallbacks::stop()" << std::endl;
			Play_Timer_1x->abort();
			delete Play_Timer_1x, Play_Timer_1x = NULL;
			flag = 0;
		}
	}

public:
	unsigned int callback2(unsigned int interval, void* args)
	{
	try	{
SCOPED_LOCK(mymtx);
		testlog << nl << " ====>> " << SDL::GetTicks() - ticks  << " ms : " << this << "\'s direct callback2 Called back ! Number: " << direct_timer_it-- ;

		if ( direct_timer_it != 0 )
			return direct_timer_int;

		testlog << nl << "Stopping " << this << "\'s direct timer" << std::endl;
		return 0;

	} catch (std::exception &exc) {
		Clean_ObjectWithCallbacks();
		throw std::logic_error("Error in ObjectWithCallbacks::callback2 " + (string)exc.what() );
	} catch (...) {
		Clean_ObjectWithCallbacks();
		throw std::logic_error("Unhandled Error in ObjectWithCallbacks::callback2" );
	}
	}
};


int main(int argc, char *argv[])
{
try {
	unsigned int NB_OBJ = 15;
	long TEST_DURATION = 20000; //ms

/***Init & Implement***/

	//Init the rand method using the current time in order to generate more random numbers
	srand( (unsigned)time( NULL ) );

	testlog.enableFileLog("testTimer.log");
	testlog << nl<<"SDL init...";

	SDL::App::getInstance().initTimer();

	//static SDL_TimerID gt_id = SDL::AddGlobalTimer(50,callback,NULL);

	testlog << nl<<"Creating instance";
	ObjectWithCallbacks* gobj = new ObjectWithCallbacks();

	testlog << nl<<"Creating instance timer";
	SDL::NewTimer<ObjectWithCallbacks> direct_timer(gobj,&ObjectWithCallbacks::callback2,(void*)NULL,200);

	testlog << nl <<"Starting instance timer 2 (every 200ms)";


/***Run***/
	//SDL::Delay(15000); //TODO Display time running
	ticks = SDL::GetTicks();

	while (SDL::GetTicks() < (ticks + TEST_DURATION))
	{
		std::cout << SDL::GetTicks() << "\r";
	}

/***Clean***/
	testlog << nl << "Cleaning and finished";

	direct_timer.abort();

	delete gobj, gobj = NULL;

	return 0;
} catch (std::exception &exc) {
	testlog << nl << " ***** ERROR ***** : " << exc.what();

} catch (...) {
	throw std::logic_error("Unhandled Error in Main !" );
}
}
