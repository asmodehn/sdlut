
/* Test program to test the thread callbacks
*/

#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include "SDL.hh"

using namespace SDLut;
using namespace SDLut::system;
using namespace RAGE;

#define DEFAULT_THREAD_NUMBER 5

RAGE::Logger testlog("testMutex");
//TODO : make Logger thread safe, somehow...

class Launcher;

class UpdateStateCB
{
	Launcher* m_pt;
	void (Launcher::*m_ptfunc) ( std::vector<int>::iterator, int);
	std::vector<int>::iterator m_it;

public:
	UpdateStateCB( Launcher* pt, void (Launcher::*ptfunc) ( std::vector<int>::iterator, int), std::vector<int>::iterator it )
	{
		m_pt = pt;
		m_ptfunc = ptfunc;
		m_it = it;
	}
	~UpdateStateCB(){}

	void call( int val)
	{
		(m_pt->*m_ptfunc) ( m_it, val );
	}

};


class ObjectWithThreadCall
{
	//static mutex to authorize only one instance of this class to count at the same time
	static Mutex mtxtest;

	//function pointer to modify the state of the running thread
	UpdateStateCB* m_updatecb;

	void count(int start, int end)
	{
		for (int i = start; i < end; i++)
		{
			testlog << nl << " --- Thread " << getCurrentThreadID() << " Mutex Lock";

			//DEBUG: randomly fails locking mutex
			//if ( rand() % DEFAULT_THREAD_NUMBER != 0 ) mtxtest.lock();
			//else testlog << nl << " === Simulating mutex problem === ";
			//NORMAL :
			mtxtest.lock();

			m_updatecb->call(2);

			testlog << nl << " --- Thread " << getCurrentThreadID() << " --> Mutex Acquired ! Iteration N " << i ;
			Delay(100);

			m_updatecb->call(1);

			mtxtest.unlock();
			testlog << nl << " --- Thread " <<getCurrentThreadID() << " Mutex Unlocked";
		}
	}

	public:

	ObjectWithThreadCall() : m_updatecb(0) {}
	ObjectWithThreadCall(UpdateStateCB * updatecb)
	{
		m_updatecb = updatecb;
	}

	~ObjectWithThreadCall()
	{
	}

	int threadcall(void* args)
	{
		if ( m_updatecb == 0 ) return 0;

		testlog << nl << " --- Thread " << getCurrentThreadID() << " called. Will counting from 0 to 30 --- " << std::endl;
		//DEBUG : to make sure the test can fail
		// initialize random seed ( random serie -> duplicated for each thread -> srand needed in each thread )
		srand ( (unsigned int) time(NULL) );

		m_updatecb->call(1);

		count(1,30);

		m_updatecb->call(3);

		return 0;
	}
};

Mutex ObjectWithThreadCall::mtxtest;

class Launcher
{
	std::vector<NewThread<ObjectWithThreadCall>*> threadid;
	std::vector<ObjectWithThreadCall*> obj;
	std::vector<int> running;
	Mutex statemtx;

	unsigned int nb_thread;

public:
	Launcher(int nbThread) : nb_thread(nbThread)
	{
		threadid.reserve(nbThread);
		obj.reserve(nbThread);
		running.reserve(nbThread);
	}

	~Launcher()
	{}

	int launchAll(long interval_ms)
	{
		//Launch check thread
		NewThread<Launcher> checkThread(this, &Launcher::check_integrity, (void *) NULL);

		//Launch other threads
		for ( unsigned int i = 0 ; i < nb_thread; ++i)
		{
			statemtx.lock();
			running.push_back(0);
			UpdateStateCB* updatecb= new UpdateStateCB(this,&Launcher::updateState,running.end()-1);
			obj.push_back( new ObjectWithThreadCall(updatecb) );
			threadid.push_back( new NewThread<ObjectWithThreadCall>(obj.back(),&ObjectWithThreadCall::threadcall,(void*)NULL) );
			statemtx.unlock();

			Delay(interval_ms);
		}

		for ( unsigned int i = 0; i < nb_thread; ++i )
		{
			threadid[i]->wait();

			statemtx.lock();
			delete threadid[i];	threadid[i] = 0;
			delete obj[i]; obj[i] = 0;
			running[i] = 9; //terminated code
			statemtx.unlock();

		}

		return checkThread.wait();
	}

	void updateState(std::vector<int>::iterator it, int value)
	{
		statemtx.lock();
		//BUG : if mutex fails this fails in a ugly way... find a way to do it better ( exception on error detection or whatever )
		*it= value;
		statemtx.unlock();
	}

	int check_integrity(void* args)
	{
		int res = 0; // OK

		bool goon = true;
		while ( goon )
		{
			statemtx.lock();
			int isrunning = std::count(running.begin(),running.end(),2 /* counting thread */);
			statemtx.unlock();

			if ( 1 < isrunning) // more than one result
			{
				testlog << nl << " !!! ERROR : At least 2 threads have been detected in mutex section at the same time !!! ";
				res = -1 * isrunning; // ERROR : number of concurrent threads detected

				// more investigation can be coded here for DEBUG
				// using vectors obj and threadid...

				break;
			}

			statemtx.lock();
			goon = ( std::count(running.begin(),running.end(),9 /*ended thread */) < (int)nb_thread ); //go on while all thread not finished
			statemtx.unlock();
		}
		return res;
	}

};

int main(int argc, char *argv[])
{
	testlog.enableFileLog("testMutex.log");
	testlog << nl<<"SDL init...";

	App::getInstance();

	int nb_thread = DEFAULT_THREAD_NUMBER;
	if ( argc > 1 )
	{
		nb_thread = atoi(argv[1]);
	}

	testlog << nl<<"Preparing Launcher for " << nb_thread << " threads";
	Launcher launcher(nb_thread);

	int res = launcher.launchAll(1000);

	testlog << nl << "Main exit !"<< std::endl;
	//Reminder hte logger is not thread safe... concurrency access may cause problems...
	//such as not writing "Main exit" in the log file quick enough
	//because it s been used by the thread...

	return res;
}
