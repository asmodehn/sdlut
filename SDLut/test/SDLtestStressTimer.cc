
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

using namespace SDLut;
using namespace SDLut::system;
using namespace RAGE;
using namespace std;

static long ticks;

RAGE::Logger testlog("testTimer");

/*static unsigned int callback(unsigned int interval, void * args)
{
	testlog << nl << GetTicks() - ticks  << " ms : Static Function called back !" ;
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
	NewTimer *Play_Timer_1x;
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

	void play1_1(SimpleArgObject*& ArgObject)
	{
	try {
SCOPED_LOCK(mymtx);

		loop_nb = 0;
		flag = 1;
		delete Play_Timer_1x, Play_Timer_1x = NULL;

		Play_Timer_1x = new NewTimer(*this,&ObjectWithCallbacks::callback1_1);

		testlog << nl << GetTicks() - ticks  << " ms : " << this << "\'s play1_1 create Timer " << Play_Timer_1x << " and launching it" << std::endl;

	} catch (std::exception &exc) {
		Clean_ObjectWithCallbacks();
		throw std::logic_error("Error in ObjectWithCallbacks::play1_1 " + (string)exc.what() );
	} catch (...) {
		Clean_ObjectWithCallbacks();
		throw std::logic_error("Unhandled Error in ObjectWithCallbacks::play1_1" );
	}
	}


private:
	unsigned int callback1_1(unsigned int interval)
	{
	try	{
SCOPED_LOCK(mymtx);
		testlog << nl << GetTicks() - ticks  << " ms : " << this << "\'s callback1_1 called back at frame " << loop_nb << std::endl;

/*		if (args == NULL)
		{
			assert(args == NULL && "Arg Pointer is NULL !");
			throw std::logic_error("Arg Pointer is NULL !");
		}*/

		//Check nb of frame
		if (++loop_nb < sobj->cb_frames)
			return sobj->callback_interval;
		else
		{
			flag = 2;
			return 0;
		}

	} catch (std::exception &exc)	{
		Clean_ObjectWithCallbacks();
		throw std::logic_error("Error in ObjectWithCallbacks::callback1_1 " + (string)exc.what() );
	} catch (...) {
		Clean_ObjectWithCallbacks();
		throw std::logic_error("Unhandled Error in ObjectWithCallbacks::callback1_1" );
	}
	}
};

class OwnerOfObjWCallbacks
{
	friend class DerivateOwnerOfObjWCallbacks;
	friend class ObjectWithCallbacks;

protected:
	ObjectWithCallbacks* objwcb;
	SimpleArgObject* sao;

public:
	OwnerOfObjWCallbacks() : objwcb(NULL), sao(NULL)
	{
	try {

		objwcb = new ObjectWithCallbacks();
		sao = new SimpleArgObject();

	} catch (std::exception &exc) {
		Clean_OwnerOfObjWCallbacks();
		throw std::logic_error("Error in OwnerOfObjWCallbacks Constructor()" +(string)exc.what() );
	} catch (...) {
		Clean_OwnerOfObjWCallbacks();
		throw std::logic_error("Unhandled Error in OwnerOfObjWCallbacks Constructor" );
	}
	}

	virtual ~OwnerOfObjWCallbacks()
	{
		Clean_OwnerOfObjWCallbacks();
	}

	void Clean_OwnerOfObjWCallbacks()
	{
		delete objwcb, objwcb = NULL;
		delete sao, sao = NULL;
	}

	void DoSthg()
	{
	try {
SCOPED_LOCK(objwcb->mymtx);
		switch (objwcb->flag)
		{
		case 0: //no callback running
			testlog << nl << "OwnerOfObjWCallbacks " << this << "\'s ObjectWithCallbacks @ " << this->objwcb << " ::play1_1() called" << std::endl;
			objwcb->start_timer_tick = GetTicks();
			objwcb->play1_1( sao );
			break;

		case 1: //one callback running
			if (objwcb->start_timer_tick + 3000 < GetTicks()) //1100ms = max nb de frame potential * max interval potentiel + 100ms
			{
				testlog << nl << "ERROR : A timer encounter an abornal termination for OwnerOfObjWCallbacks " << this << "\'s ObjectWithCallbacks @ " << this->objwcb << std::endl;
				throw logic_error( " A timer encounter an abornal termination");
			}
			break;

		case 2: //one callback ended
			testlog << nl << "callback1_1 Ended, Resetting objwcb->flag to 0 inside OwnerOfObjWCallbacks" << this << "\'s ObjectWithCallbacks @ " <<this->objwcb << std::endl;
			objwcb->flag = 0;
			break;

		default:
			throw logic_error( "unkown objwcb->flag value : " + Int_To_String(objwcb->flag) );
			break;

		}

	} catch (std::exception &exc) {
		Clean_OwnerOfObjWCallbacks();
		throw std::logic_error("Error in OwnerOfObjWCallbacks::DoSthg() : " + (string)exc.what() );
	} catch (...) {
		Clean_OwnerOfObjWCallbacks();
		throw std::logic_error("Unhandled Error in OwnerOfObjWCallbacks::DoSthg" );
	}
	}
};

/*class DerivateOwnerOfObjWCallbacks : public OwnerOfObjWCallbacks
{

public:
	DerivateOwnerOfObjWCallbacks()
	{}
};*/


int main(int argc, char *argv[])
{
try {
	unsigned int NB_OBJ = 15;
	long TEST_DURATION = 30000; //ms

/***Init & Implement***/

	//Init the rand method using the current time in order to generate more random numbers
	srand( (unsigned)time( NULL ) );

	testlog.enableFileLog("testTimer.log");
	testlog << nl<<"SDL init...";

	App::getInstance().initTimer();

	vector<OwnerOfObjWCallbacks*>* voocb = new vector<OwnerOfObjWCallbacks*>;
	for (unsigned int i = 0; i < NB_OBJ; i++)
	{
		voocb->push_back( new OwnerOfObjWCallbacks() );
	}

	//DerivateOwnerOfObjWCallbacks* iocb = new DerivateOwnerOfObjWCallbacks();

/***Run***/
	//Delay(15000); //TODO Display time running
	ticks = GetTicks();

	while (GetTicks() < (ticks + TEST_DURATION))
	{
		for (unsigned int i = 0; i < voocb->size(); i++)
		{
			std::cout << GetTicks() << "\r";
			voocb->at(i)->DoSthg();
		}
		//iocb->DoSthg();
	}


/***Clean***/
	testlog << nl << "Cleaning and finished";

	for (unsigned int i = 0; i < voocb->size(); i++)
	{
		delete voocb->at(i), voocb->at(i) = NULL;
	}
	delete voocb, voocb = NULL;

	//delete iocb, iocb = NULL;

	//RemoveGlobalTimer(gt_id);

	return 0;
} catch (std::exception &exc) {
	testlog << nl << " ***** ERROR ***** : " << exc.what();
	//Delay(2000);

} catch (...) {
	throw std::logic_error("Unhandled Error in Main !" );
}
}
