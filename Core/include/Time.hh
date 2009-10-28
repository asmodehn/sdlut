#ifndef TIME_HH
#define TIME_HH

#include <time.h>

void sleep (unsigned int sec);

/** TODO : Class to handle portable calls to standard time functions
 * Pattern : transparent Singleton
**/
class RunTime
{
    static RunTime * instance;

public :

};

/** TODO : Class to handle Simulated time and relation with runtime...
 * Pattern : Transparent Singleton
**/

class SimTime
{
    static SimTime * instance;

public :

};

#endif
