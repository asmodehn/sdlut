#ifndef SDLEVENT_HH
#define SDLEVENT_HH

#include "SDLConfig.hh"
#include "SDLEventHandler.hh"
/**
 * \class SDLEvent
 *
 * \ingroup EventHandling
 *
 * \brief This class wraps SDL_Event
 *
 * This class wraps SDL_Event and all the SDL related functions
 *
 * \note should only be used through SLDEventHandler for more safety...
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

namespace SDL {
//TODO : have a look about Uint8 *keys = SDL_GetKeyPresses();

class Event {
	//the adress of SDL_Event struct should never change
	SDL_Event * const _event;

public:

	Event() : _event(new SDL_Event) {}
	~Event() {delete _event;}

	//Polls for currently pending events
	bool poll (bool fetch = true);
	//Wait indefinitely for the next available event
	bool wait (bool fetch = true);
	//push this event onto the queue
	bool push (void);

	//pumps the event loop
	static void pumpEvents(void);

	//sets up a filter on all events, processed before they are transferred to the queue
	static void setEventFilter(SDL_EventFilter filter);
	//get the filter //TODO : Wrap the SDL_Filter structure
	static SDL_EventFilter getEventFilter(void);
	//sets the state of processing for certain events
	static Uint8 eventState(Uint8 type, int state);

	//Handle all queued events using the specified EventHandler
	static void handleEvents(EventHandler& handler);

	//Get a snapshot of the current keyboard state
	static Uint8* getKeyState (int &numkeys);
	static Uint8* getKeyState (void);

	//get the current key modifier state
	//TODO : where this SDLMod comes from ?
	static SDLMod getModState (void);
	//set the current key modifier state
	static void setModState(SDLMod modstate);

	//get the name of an SDL virtual key symbol
	static char* getKeyName(SDLKey key);

	// Unicode keyboard translation
	static bool enableUNICODE(void);
	static bool disableUNICODE(void);
	static bool isUNICODEEnabled(void);

	//Params Key repeat
	static bool enableKeyRepeat (int delay = SDL_DEFAULT_REPEAT_DELAY,
								int interval = SDL_DEFAULT_REPEAT_INTERVAL);

	//gets the state of the application
	static Uint8 getAppState(void);

	//Enable / Disable Joystick Event polling
	static int joystickEventState(int state);

};

} //namespace SDL

#endif
