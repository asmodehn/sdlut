#include "Randomizer.hh"

#include <cassert>
#include <iostream>

Randomizer * Randomizer::instance= 0 ;

///from http://www.cppreference.com/wiki/c/other/rand
//the correct random number generator for [min,max]

unsigned int Randomizer::getui ( unsigned int min, unsigned int max)
{
    if ( ! instance )
    {
        instance = new Randomizer();
    }

    // scale in range [0,1)
    const float scale = rand()/float(RAND_MAX);

    // return range [min ,max]
    //cast and truncation
    unsigned int res = static_cast<unsigned int>(min + scale * (max-min) + 0.5);

#ifdef _DEBUG
    if ( res < min || res > max )
    {
        std::cerr << "Error random number generated " << res << "is not in" << "[" << min << "," << max << "]" << std::endl;
    }
#endif

    return  res;
}

int Randomizer::geti ( int min, int max )
{
    if ( ! instance )
    {
        instance = new Randomizer();
    }

    // scale in range [0,1)
    const float scale = rand()/float(RAND_MAX);

    // return range [0,hi]
    //cast and truncation
    int res = static_cast<int>(min + scale * (max-min) + 0.5);

    //TODO : with assert
#ifdef _DEBUG
    if ( res < min || res > max )
    {
        std::cerr << "Error random number generated " << res << "is not in" << "[" << min << "," << max << "]" << std::endl;
    }
#endif

    return  res;
}



float Randomizer::getf ( float min , float max )
{
    if ( ! instance )
    {
        instance = new Randomizer();
    }

    // scale in range [0,1)
    const float scale = rand()/float(RAND_MAX);

    // return range [0,hi]
    //cast and truncation
    float res = static_cast<float>(min + scale * (max-min) );

    //TODO : with assert
#ifdef _DEBUG
    if ( res < min || res > max )
    {
        std::cerr << "Error random number generated " << res << "is not in" << "[" << min << "," << max << "]" << std::endl;
    }
#endif

    return  res;
}


double Randomizer::getd ( double min, double max )
{
    if ( ! instance )
    {
        instance = new Randomizer();
    }

    // scale in range [0,1)
    const double scale = rand()/double(RAND_MAX);

    // return range [0,hi]
    //cast and truncation
    double res = static_cast<double>(min + scale * (max-min));

    //TODO : with assert
#ifdef _DEBUG
    if ( res < min || res > max )
    {
        std::cerr << "Error random number generated " << res << "is not in" << "[" << min << "," << max << "]" << std::endl;
    }
#endif

    return  res;
}
