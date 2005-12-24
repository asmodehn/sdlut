#include "SDLEvent.hh"

namespace SDL {

bool Event::poll(bool fetch)
{
	if(fetch)
	{
		return SDL_PollEvent(_event) != 0;
	} else {
		return SDL_PollEvent(0) != 0;
	}
}

bool Event::wait(bool fetch)
{
	if(fetch)
	{
		return SDL_WaitEvent(_event) != 0;
	} else {
		return SDL_WaitEvent(0) != 0;
	}
}

bool Event::push()
{
	return SDL_PushEvent(_event) == 0;
}

void Event::pumpEvents()
{
	SDL_PumpEvents();
}

void Event::setEventFilter(SDL_EventFilter filter)
{
	SDL_SetEventFilter(filter);
}

SDL_EventFilter Event::getEventFilter()
{
	return SDL_GetEventFilter();
}

Uint8 Event::eventState(Uint8 type, int state)
{
	return SDL_EventState(type, state);
}

Uint8* Event::getKeyState(int &numkeys)
{
	return SDL_GetKeyState(&numkeys);
}

Uint8* Event::getKeyState()
{
	return SDL_GetKeyState(0);
}

SDLMod Event::getModState()
{
	return SDL_GetModState();
}

char* Event::getKeyName(SDLKey key)
{
	return SDL_GetKeyName(key);
}

void Event::setModState(SDLMod modstate)
{
	SDL_SetModState(modstate);
}

bool Event::enableKeyRepeat(int delay, int interval)
{
	return SDL_EnableKeyRepeat(delay, interval) == 0;
}



Uint8 Event::getAppState()
{
	return SDL_GetAppState();
}

int Event::joystickEventState(int state)
{
	return SDL_JoystickEventState(state);
}

//using that with threads
//http://vilimpoc.org/research/portmonitorg/sdl-tips-and-tricks.html

//Using correct handler for processing events...
// Handler should be const maybe ??
void Event::handleEvents(EventHandler &handler)
{
	SDL_Event event;
    while(SDL_PollEvent(&event)) {
		bool ev_handled = false;
		switch(event.type) {
			case SDL_ACTIVEEVENT:
				ev_handled = handler.handleActiveEvent(event.active.gain == 1,
					       event.active.state);
				break;
			case SDL_KEYDOWN:
				ev_handled = handler.handleKeyPressEvent(event.key.keysym);
				break;
			case SDL_KEYUP:
				ev_handled = handler.handleKeyReleaseEvent(event.key.keysym);
				break;
			case SDL_MOUSEMOTION:
				ev_handled = handler.handleMouseMotionEvent(event.motion.state,
							event.motion.x, event.motion.y, event.motion.xrel,
							event.motion.yrel);
				break;
			case SDL_MOUSEBUTTONDOWN:
				ev_handled = handler.handleMouseButtonPressEvent(event.button.button,
							event.button.x, event.button.y);
				break;
			case SDL_MOUSEBUTTONUP:
				ev_handled = handler.handleMouseButtonReleaseEvent(event.button.button,
							event.button.x, event.button.y);
				break;
			case SDL_JOYAXISMOTION:
				ev_handled = handler.handleJoyAxisEvent(event.jaxis.which,
							event.jaxis.axis, event.jaxis.value);
				break;
			case SDL_JOYBALLMOTION:
				ev_handled = handler.handleJoyBallEvent(event.jball.which,
							event.jball.ball, event.jball.xrel, event.jball.yrel);
				break;
			case SDL_JOYHATMOTION:
				ev_handled = handler.handleJoyHatEvent(event.jhat.which,
							event.jhat.hat, event.jhat.value);
				break;
			case SDL_JOYBUTTONDOWN:
				ev_handled = handler.handleJoyButtonPressEvent(event.jbutton.which,
							event.jbutton.button);
				break;
			case SDL_JOYBUTTONUP:
				ev_handled = handler.handleJoyButtonReleaseEvent(event.jbutton.which,
							event.jbutton.button);
				break;
			case SDL_QUIT:
				ev_handled = handler.handleQuitEvent();
				break;
			case SDL_SYSWMEVENT:
				ev_handled = handler.handleSysWMEvent();
				break;
			case SDL_VIDEORESIZE:
				ev_handled = handler.handleResizeEvent(event.resize.w, event.resize.h);
				break;
			case SDL_USEREVENT:
				ev_handled = handler.handleUserEvent(event.user.type, event.user.code,
							event.user.data1, event.user.data2);
				break;
		}
		if(!ev_handled) {
			handler.handleEvent(event);
		}
	}
}

} //namespace SDL
