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

        extern Logger Log;

        /**
          * This class manages the global configuration of AML
          */

        class Config
        {
public:
            Config() {
                        Log.enableFileLog("Rage_AML.log");
            }


        }
        ;

    }
}

#endif

