#ifndef SDL_TIMER_HH
#define SDL_TIMER_HH

#include "SDLConfig.hh"

namespace RAGE::SDL {

class Timer
{
  public:
  static inline void delay(long millisec) { SDL_Delay(static_cast<UInt32>(millisec)); }
  static inline long getTicks(void) { return static_cast<long>(SDL_GetTicks()); }
// add and remove to do... how ??
// A timer can trigger a function directly (beware of the thread-safe problem)
// this can be used to trigger event up in AML (if AML is thread-safe)...
// More safe, but slower, a timer can trigger an SDL event ...

};


}
#endif