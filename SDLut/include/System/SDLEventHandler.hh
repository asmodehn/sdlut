#ifndef SDL_EVENTHANDLER_HH
#define SDL_EVENTHANDLER_HH

#include "System/SDLEvent.hh"

#include <stdexcept>

namespace RAGE
{
namespace SDL
{

/**
 * \class EventHandler
 *
 * \ingroup EventHandling
 *
 * \brief This class handles general events in SDLut
 *
 * \author Alex
 *
 * \date 2005/12/27
 *
 * Contact: asmodehn@gna.org
 *
 */

class BaseEventHandler
{
    friend class EventManager;

public:

    BaseEventHandler() {}
    virtual ~BaseEventHandler() {}

    //Callbacks on Window / Display events
    virtual bool handleActiveEvent(bool gain, bool active, bool inputfocus, bool mousefocus) = 0;
    virtual bool handleResizeEvent(int w, int h) = 0;
    virtual bool handleExposeEvent() = 0;
    //callback on platform-dependent windows manager event
    virtual bool handleSysWMEvent(void) = 0;

    //Callback on other Events
    virtual bool handleUserEvent(Event::Type type, int code, void* data1, void* data2) = 0;

    //Callback on Quit Event
    virtual bool handleQuitEvent(void) = 0;

    //Catch-all callback
    virtual bool handleEvent(Event &event) = 0;
};


//Class for default behaviour
class DefaultEventHandler : public BaseEventHandler
{
    bool _quitRequested; // TODO ????

public:
    DefaultEventHandler() : _quitRequested(false) {}
    virtual ~DefaultEventHandler() {}

    //Callbacks on Window / Display events
    virtual bool handleActiveEvent(bool gain, bool active, bool inputfocus, bool mousefocus);
    virtual bool handleResizeEvent(int w, int h);
    virtual bool handleExposeEvent();
    //callback on platform-dependent windows manager event
    virtual bool handleSysWMEvent(void);

    //Callback on other Events
    virtual bool handleUserEvent(Event::Type type, int code, void* data1, void* data2);

    //Callback on Quit Event
    virtual bool handleQuitEvent(void);

    //Catch-all callback
    virtual bool handleEvent(Event &event);

};

} //SDL
} // RAGE

#endif
