#include "System/SDLEventManager.hh"
#include "SDLApp.hh" //for default resize

#include "SDLConfig.hh"


namespace RAGE
{
    namespace SDL
{

    bool GeneralHandler::handleActiveEvent(bool gain, bool active, bool inputfocus, bool mousefocus)
    {
        return false;
    }

    bool GeneralHandler::handleResizeEvent(int w, int h)
    {
        App::getInstance().getWindow().resizeDisplay(w,h);
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

    bool GeneralHandler::handleUserEvent(Event::Type type, int code, void* data1, void* data2)
    {
        return false;
    }

    bool GeneralHandler::handleQuitEvent(void)
    {
        _quitRequested=true;
        return true;
    }

    bool GeneralHandler::handleEvent(Event &event)
    {
#if (DEBUG ==2)
        //Getting the details of the Event
        Log << nl << "Last chance handler : " << cevent.getType() << std::endl;
        return true;
#else

        return false;
#endif
    }


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
        Event event;

        bool ev_handled = false;
        //to improve
	if (SDL_PeepEvents(event.get_pSDL(),1,SDL_GETEVENT,Event::Type2sdl(type)) != -1 )
        {
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

    //handle all the events in the queue in a loop
    void EventManager::handleAll()
    {
	Event event;

	//TODO : replace with a get_SDL here...
        while( SDL_PollEvent(event.get_pSDL()))
        {
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

	Event event;
        bool ev_handled = false;

        if( SDL_PollEvent(event.get_pSDL())!= 0)
        {
            
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

    void EventManager::pump()
    {
	    SDL_PumpEvents();
    }


}

}
