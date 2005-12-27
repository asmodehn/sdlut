#include "SDLEventManager.hh"

namespace SDL
{

GeneralHandler::GeneralHandler(EventManager eventmanager)
 :_eventmanager(eventmanager)
 {
}


bool GeneralHandler::handleActiveEvent(bool gain, Uint8 state)
{ return false; }

bool GeneralHandler::handleResizeEvent(int w, int h)
{
        _eventmanager._focusedwindow.resize(w,h);
        return true;
}

bool GeneralHandler::handleSysWMEvent(void)
{ return false; }

bool GeneralHandler::handleUserEvent(Uint8 type, int code, void* data1, void* data2)
{ return false; }

bool GeneralHandler::handleQuitEvent(void)
{
    _eventmanager._quitRequested=true;
    return true;
}

bool GeneralHandler::handleEvent(CriticalEvent &cevent)
{ return false; }


    Event EventManager::wait () throw(std::logic_error)
    {
        Event res;
        if (SDL_WaitEvent(&res._event)  == 0 )
            throw std::logic_error("Error while waiting for events!");
        return res;
    }

    //handle all the critical events in the queue in a loop
    void EventManager::handleAllCritical()
    {
        CriticalEvent cevent;
        while( SDL_PeepEvents(&(cevent._event),1,SDL_GETEVENT,_criticaltypes))
        {
            if(! cevent.callHandler(*ghndlr, *khndlr, *mhndlr) )
                ghndlr->handleEvent(cevent);
        }
    }

    //handle the next critical event
    bool EventManager::handleNextCritical()
    {
        CriticalEvent cevent;
        bool ev_handled = false;
        //to improve
        if (SDL_PeepEvents(&(cevent._event),1,SDL_GETEVENT,_criticaltypes) != -1 )
        {
            if(! cevent.callHandler(*ghndlr,* khndlr,* mhndlr) )
                ev_handled = ghndlr->handleEvent(cevent);
        }
        return ev_handled;
    }




    //handle the next critical event of this type
    bool EventManager::handleNextCritical(EventType type)
    {
        CriticalEvent cevent;

            bool ev_handled = false;
    //to improve
    if (SDL_PeepEvents(&(cevent._event),1,SDL_GETEVENT,type) != -1 )
        {
            if(! cevent.callHandler(*ghndlr,* khndlr,* mhndlr) )
                ev_handled = ghndlr->handleEvent(cevent);
        }
        return ev_handled;
    }

    //handle all the events in the queue in a loop
    void EventManager::handleAll()
    {
        Event event;
        while( SDL_PollEvent(&(event._event)))
        {
            if(! event.callHandler(*ghndlr, *khndlr, *mhndlr) )
                ghndlr->handleEvent(event);
        }
    }

    //handle the next event
    bool EventManager::handleNext()
    {

        Event event;
        bool ev_handled = false;

        if( SDL_PollEvent(&(event._event))!= 0)
        {
            if(! event.callHandler(*ghndlr, *khndlr, *mhndlr) )
                ev_handled = ghndlr->handleEvent(event);
        }
        return ev_handled;
    }


}
