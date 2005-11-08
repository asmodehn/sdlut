#ifndef SDLTIMER_HH
#define SDLTIMER_HH

#include "SDLConfig.hh"

namespace SDL {

class Timer
{
  public:
  static inline void delay(long millisec) { SDL_Delay(static_cast<UInt32>(millisec)); }
  static inline long getTicks(void) { return static_cast<long>(SDL_GetTicks()); }
// add and remove to do... how ??
};


}
#endif