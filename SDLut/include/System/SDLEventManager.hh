#ifndef SDL_EVENTMANAGER_HH
#define SDL_EVENTMANAGER_HH

#include "System/SDLEvent.hh"
#include "System/SDLEventHandler.hh"
#include "Input/SDLMouse.hh"
#include "Input/SDLKeyboard.hh"
#include "Input/SDLJoystick.hh"

#include <stdexcept>

namespace SDLut
{

namespace video
{
class Display;
}

namespace system
{


/**
* \class EventManager
*
* \ingroup EventHandling
*
* \brief This class manages the event handling in SDLwrap
*
* There should always be one and only one EventManager
*
* \author Alex
*
* \date 2005/12/27
*
* Contact: asmodehn@gna.org
*
*/
class EventManager
{
    friend class video::Display; // to build the unique instance of EventManager

protected:


    bool usergeneral;
    BaseEventHandler * ghndlr;

    bool usermouse;
    input::Mouse * mhndlr;

    bool userkeyboard;
    input::Keyboard * khndlr;


    EventManager()  : usergeneral(false),ghndlr(new DefaultEventHandler()),usermouse(false),mhndlr(new input::Mouse()),userkeyboard(false), khndlr(new input::DefaultKeyboard())
    {

    }

public :

    ~EventManager()
    {
        if (!usergeneral)
            delete ghndlr, ghndlr = NULL;
        if (!usermouse)
            delete mhndlr, mhndlr = NULL;
        if (!userkeyboard)
            delete khndlr, khndlr = NULL;
    }


    void setKeyboard(input::Keyboard * newkhndlr)
    {
        delete khndlr,khndlr=NULL;
        userkeyboard = true;
        khndlr = newkhndlr;
    }
    void setGeneralHandler(BaseEventHandler * newghndlr)
    {
        delete ghndlr,ghndlr=NULL;
        usergeneral = true;
        ghndlr = newghndlr;
    }
    void setMouse(input::Mouse * newmhndlr)
    {
        delete mhndlr,mhndlr=NULL;
        usermouse = true;
        mhndlr = newmhndlr;
    }

    //Wait indefinitely for the next available event
    //return the event found or throw an exception if error.
    Event wait () throw(std::logic_error);
    /*
                void setCriticalType(EventType type)
                {
                    _criticaltypes |= type;
                }*/

    //handle all the critical events in the queue in a loop
    void handleAll();

    //handle the next critical event
    bool handleNext();

    //handle the next event of this type
    bool handleNext(Event::Type type);

    //Pump the event loop.
    //Implicitely called by handleAll() or handleNext() but not by the "critical" methods
    void pump();

};

} //namespace system
} //namespace SDLut

#endif

