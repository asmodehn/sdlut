#ifndef Timer_HH
#define Timer_HH

#include "Project0.hh"

//Timer for FPS management
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
    
    //Get the number of ticks since the timer started
    //Or gets the number of ticks when the timer was paused
    int get_ticks();
    
    //Checks the status of the timer
    bool is_started();
    bool is_paused();    
};

#endif
