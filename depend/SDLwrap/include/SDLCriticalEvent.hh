#ifndef SDL_CRITICALEVENT_HH
#define SDL_CRITICALEVENT_HH

#include "SDLConfig.hh"
namespace SDL {

/**
 * \class CriticalEvent
 *
 * \ingroup EventHandling
 *
 * \brief This class wraps SDL_Event for "High Priority" Event
 *
 * This class wraps SDL_Event to allow "High Priority" Event manipulation.
 * The related functions wrapped are mostly SDL_PushEvent, and SDL_PeekEvent
 * For usual Event Handling you should use the Event Class.
 *
 * \note should only be used through SDLEventHandler for more safety...
 *
 * \author Alex
 *
 * \date 2005/12/27
 *
 * Contact: asmodehn@gna.org
 *
 */




    //defining all the events provided by SDL
    typedef enum {  Active = SDL_ACTIVEEVENT,
                            KeyDown = SDL_KEYDOWN,
                            KeyUp = SDL_KEYUP,
                            MouseMotion = SDL_MOUSEMOTION,
                            MouseButtonDown = SDL_MOUSEBUTTONDOWN,
                            MouseButtonUp = SDL_MOUSEBUTTONUP,
                            JoyAxis = SDL_JOYAXISMOTION,
                            JoyBall = SDL_JOYBALLMOTION,
                            JoyHat = SDL_JOYHATMOTION,
                            JoyButtonDown = SDL_JOYBUTTONDOWN,
                            JoyButtonUp = SDL_JOYBUTTONUP,
                            User = SDL_USEREVENT,
                            Quit = SDL_QUIT,
                            SysWM = SDL_SYSWMEVENT,
                            Resize = SDL_VIDEORESIZE,
                            Expose = SDL_VIDEOEXPOSE
    } EventType;

//further reference
class GeneralHandler;
class KeyboardHandler;
class MouseHandler;

class CriticalEvent
{

    friend class EventManager;

    protected :
    SDL_Event & _event;

    explicit CriticalEvent(SDL_Event event) : _event(event) {}
    //CriticalEvent() : _event() {}


    public:

    CriticalEvent(EventType type = User );

    //list of accessors to make the event we want
//    set...
//
//
//    SDL_ACTIVEEVENT 	SDL_ActiveEvent
//SDL_KEYDOWN/UP 	SDL_KeyboardEvent
//SDL_MOUSEMOTION 	SDL_MouseMotionEvent
//SDL_MOUSEBUTTONDOWN/UP 	SDL_MouseButtonEvent
//SDL_JOYAXISMOTION 	SDL_JoyAxisEvent
//SDL_JOYBALLMOTION 	SDL_JoyBallEvent
//SDL_JOYHATMOTION 	SDL_JoyHatEvent
//SDL_JOYBUTTONDOWN/UP 	SDL_JoyButtonEvent
//SDL_QUIT 	SDL_QuitEvent
//SDL_SYSWMEVENT 	SDL_SysWMEvent
//SDL_VIDEORESIZE 	SDL_ResizeEvent
//SDL_VIDEOEXPOSE 	SDL_ExposeEvent
//SDL_USEREVENT 	SDL_UserEvent
//
//

	~CriticalEvent() {}

    //push this event onto the queue
	bool push (void);
	//add this event to the queue a number of times
	int push (int number);

    //Peek number of currently pending event of the same type. (not removed from the queue)
	//std::vector<CriticalEvent> peek(int number);

	//Get number of currently pending event of the same type. (removed from the queue)
	//std::vector<CriticalEvent> get(int number);

	//retrive the tye of this CriticalEvent
    EventType getType();


    //calls the handler coresponding to the event
    bool callHandler(GeneralHandler & ghndlr, KeyboardHandler & khndlr, MouseHandler&  mhndlr );



};

}

#endif

