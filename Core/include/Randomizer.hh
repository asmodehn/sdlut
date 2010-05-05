#ifndef RANDOMIZER_HH
#define RANDOMIZER_HH

#include <cstdlib>
#include <ctime>
#include <limits>
//class implementing a proper randomizer
//singleton pattern

namespace Core
{

#ifndef PI
#define PI 3.14159265358979323846
#endif
#ifndef M_PI
#define M_PI PI
#endif

template < class T >
class Randomizer
{
private :

    static Randomizer<T> * instance;

    Randomizer()
    {
        srand( (unsigned)time( NULL ) );
    }
    ~Randomizer()
    {
        delete instance, instance = 0;
    }

public:

    ///return a randomly generated number in between [ min, max )
    static T get ( T min = 0, T max = 100);

};

///global declaration
template <class T>
Randomizer<T> * Randomizer<T>::instance;


///from http://www.cppreference.com/wiki/c/other/rand
//the correct random number generator for [min,max]
template <class T>
T Randomizer<T>::get ( T min, T max)
{
    if ( ! instance )
    {
        instance = new Randomizer<T>();
    }

    // scale in range [0,1)
    const float scale = rand()/float(RAND_MAX);

    // return range [min ,max)
    //cast and truncation
    T res = static_cast<T>(min + scale * (max-min));

    return  res;
}




} // Core
#endif
