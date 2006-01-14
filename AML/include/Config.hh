#ifndef AML_CONFIG_HH
#define AML_CONFIG_HH
//Common include for every AML header

#define AML_LIB

//defining the use of SDLwrap by default
#ifndef USE_DEPEND_SDLwrap
#define USE_DEPEND_SDLwrap
//if using SDL (mandatory for now)
#include "SDL.hh"
#endif

namespace RAGE
{

    namespace AML
    {

        static Logger Log("RAGE::AML");

        /**
          * This class manages the global configuration of AML
          */

        class Config
        {



        }
        ;

    }
}

#endif

