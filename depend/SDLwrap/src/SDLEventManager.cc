#include "SDLEventManager.hh"
#include "SDLApp.hh" //for default resize

namespace SDL
{

    bool GeneralHandler::handleActiveEvent(bool gain, Uint8 state)
    {
        return false;
    }

    bool GeneralHandler::handleResizeEvent(int w, int h)
    {
#ifdef DEBUG
        assert(App::getInstance().getWindow());
#endif

        App::getInstance().getWindow()->resize(w,h);
        return true;
    }

    bool GeneralHandler::handleExposeEvent()
    {
        return false;
    }

    bool GeneralHandler::handleSysWMEvent(void)
    {
        return false;
    }

    bool GeneralHandler::handleUserEvent(Uint8 type, int code, void* data1, void* data2)
    {
        return false;
    }

    bool GeneralHandler::handleQuitEvent(void)
    {
        _quitRequested=true;
        return true;
    }

    bool GeneralHandler::handleEvent(CriticalEvent &cevent)
    {
#ifdef DEBUG
        //Getting the details of the Event
        Log << nl << "Last chance handler : " << cevent.getType() << std::endl;
        return true;
#else

        return false;
#endif
    }


    Event EventManager::wait () throw(std::logic_error)
    {
        SDL_Event * res = new SDL_Event();
        if (SDL_WaitEvent(res)  == 0 )
            throw std::logic_error("Error while waiting for events!");
        return Event(res);
    }

    //handle all the critical events in the queue in a loop
    void EventManager::handleAllCritical()
    {
        SDL_Event* event=new SDL_Event();
        while( SDL_PeepEvents(event,1,SDL_GETEVENT,_criticaltypes))
        {
            CriticalEvent cevent(event);
#ifdef DEBUG
            assert(ghndlr);
            assert(khndlr);
            assert(mhndlr);
#endif

            if(! cevent.callHandler(ghndlr, khndlr, mhndlr) )
                ghndlr->handleEvent(cevent);
        }
    }

    //handle the next critical event
    bool EventManager::handleNextCritical()
    {
        SDL_Event* event=new SDL_Event();
        bool ev_handled = false;
        //to improve
        if (SDL_PeepEvents(event,1,SDL_GETEVENT,_criticaltypes) != -1 )
        {
            CriticalEvent cevent(event);
#ifdef DEBUG
            assert(ghndlr);
            assert(khndlr);
            assert(mhndlr);
#endif

            if(! cevent.callHandler(ghndlr, khndlr, mhndlr) )
                ev_handled = ghndlr->handleEvent(cevent);
        }
        return ev_handled;
    }




    //handle the next critical event of this type
    bool EventManager::handleNextCritical(EventType type)
    {
        SDL_Event* event=new SDL_Event();

        bool ev_handled = false;
        //to improve
        if (SDL_PeepEvents(event,1,SDL_GETEVENT,type) != -1 )
        {
            CriticalEvent cevent(event);
#ifdef DEBUG
            assert(ghndlr);
            assert(khndlr);
            assert(mhndlr);
#endif

            if(! cevent.callHandler(ghndlr, khndlr, mhndlr) )
                ev_handled = ghndlr->handleEvent(cevent);
        }
        return ev_handled;
    }

    //handle all the events in the queue in a loop
    void EventManager::handleAll()
    {
        SDL_Event* sdlevent=new SDL_Event();
        while( SDL_PollEvent(sdlevent))
        {
            Event event(sdlevent);
#ifdef DEBUG
            assert(ghndlr);
            assert(khndlr);
            assert(mhndlr);
#endif

            if(! event.callHandler(ghndlr, khndlr, mhndlr) )
                ghndlr->handleEvent(event);
        }
    }

    //handle the next event
    bool EventManager::handleNext()
    {

        SDL_Event* sdlevent=new SDL_Event();
        bool ev_handled = false;

        if( SDL_PollEvent(sdlevent)!= 0)
        {
            Event event(sdlevent);
#ifdef DEBUG
            assert(ghndlr);
            assert(khndlr);
            assert(mhndlr);
#endif

            if(! event.callHandler(ghndlr, khndlr, mhndlr) )
                ev_handled = ghndlr->handleEvent(event);
        }
        return ev_handled;
    }


}
