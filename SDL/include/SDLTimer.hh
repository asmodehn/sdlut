#ifndef SDL_TIMER_HH
#define SDL_TIMER_HH

#include "SDLConfig.hh"

namespace RAGE
{
    namespace SDL
    {

		/*****
		* Timer class 
		* XfX -- 15/03/2006
		******/

		class Timer
		{
			private:
				//The clock time when the timer started
				int startTicks;
			    
				//The ticks stored when the timer was paused
				int pausedTicks;
			    
				//The timer status
				bool paused;
				bool started;
		    
			public:
				//Initializes variables
				Timer();
			    
				//The various clock actions
				void start();
				void stop();
				void pause();
				void unpause();
			    
				//Get the number of ticks since the timer started Or gets the number of ticks when the timer was paused
				int get_ticks();
			    
				//Checks the status of the timer
				bool is_started();
				bool is_paused();    

				//Simple SDL_delay implementation
				static void delay(long millisec) { SDL_Delay((millisec)); }
		};
	}
}
#endif
