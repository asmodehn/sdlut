#ifndef RANDOMIZER_HH
#define RANDOMIZER_HH

#include <cstdlib>
#include <ctime>
//class implementing a proper randomizer
//singleton pattern

#ifndef PI
#define PI 3.14159265358979323846
#endif
#ifndef M_PI
#define M_PI PI
#endif

class Randomizer
{
private :

    static Randomizer * instance;

    Randomizer()
    {
        srand( (unsigned)time( NULL ) );
    }
    ~Randomizer()
    {
        delete instance, instance = 0;
    }

public:

    static unsigned int getui (unsigned int min = 0, unsigned int max = 100);
    static int geti ( int min =0 ,  int max = 100 );
    static float getf (float min =0.0, float max = 1.0);
    static double getd (double min = 0.0, double max = 1.0);

};

#endif
