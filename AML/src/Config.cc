#include "Config.hh"
namespace RAGE
{
    namespace AML
    {


        Logger Log("RAGE::AML");

#ifdef USE_DEPEND_SDLwrap



#else
#error "No library defined to handle 2D graphics"
#endif

    }
}
