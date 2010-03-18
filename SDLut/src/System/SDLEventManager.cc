#include "System/SDLEventManager.hh"

#include "SDLConfig.hh"

#include <cassert>

namespace SDLut
{
namespace system
{

Event EventManager::wait () throw(std::logic_error)
{
    Event res;
    if (SDL_WaitEvent(res.get_pSDL())  == 0 )
        throw std::logic_error("Error while waiting for events!");
    return res;
}

//handle the next critical event of this type
bool EventManager::handleNext(Event::Type type)
{
    Event evt;

    bool ev_handled = false;
    //to improve
    if (SDL_PeepEvents(evt.get_pSDL(),1,SDL_GETEVENT,Event::Type2sdl(type)) != -1 )
    {
#ifdef DEBUG
        assert(ghndlr);
        assert(khndlr);
        assert(mhndlr);
#endif

        if (! evt.callHandler(ghndlr, khndlr, mhndlr) )
            ev_handled = ghndlr->handleEvent(evt);
    }
    return ev_handled;
}

//handle all the events in the queue in a loop
void EventManager::handleAll()
{
    Event evt;

    //TODO : replace with a get_SDL here...
    while ( SDL_PollEvent(evt.get_pSDL()))
    {
#ifdef DEBUG
        assert(ghndlr);
        assert(khndlr);
        assert(mhndlr);
#endif

        if (! evt.callHandler(ghndlr, khndlr, mhndlr) )
            ghndlr->handleEvent(evt);
    }
}

//handle the next event
bool EventManager::handleNext()
{

    Event evt;
    bool ev_handled = false;

    if ( SDL_PollEvent(evt.get_pSDL())!= 0)
    {

#ifdef DEBUG
        assert(ghndlr);
        assert(khndlr);
        assert(mhndlr);
#endif
        if (! evt.callHandler(ghndlr, khndlr, mhndlr) )
            ev_handled = ghndlr->handleEvent(evt);
    }
    return ev_handled;
}

void EventManager::pump()
{
    SDL_PumpEvents();
}


}

}
