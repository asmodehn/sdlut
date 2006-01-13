#ifndef SDL_EVENT_HH
#define SDL_EVENT_HH

#include "SDLConfig.hh"
#include "SDLCriticalEvent.hh"

namespace RAGE
{
    namespace SDL
{

    class Event : public CriticalEvent
    {
        friend class EventManager;

        explicit Event(SDL_Event *const event) : CriticalEvent(event) {}

        public:

        Event(EventType type = User ) : CriticalEvent(type) {}

        bool callHandler(GeneralHandler * ghndlr, Keyboard * khndlr, Mouse*  mhndlr);

    };
}
}
#endif
