#include "SDLEvent.hh"

bool SDLEvent::poll(bool fetch)
{
	if(fetch)
	{
		return SDL_PollEvent(_event) != 0;
	} else {
		return SDL_PollEvent(0) != 0;
	}
}
  
bool SDLEvent::wait(bool fetch)
{
	if(fetch)
	{
		return SDL_WaitEvent(_event) != 0;
	} else {
		return SDL_WaitEvent(0) != 0;
	}
}

bool SDLEvent::push()
{
	return SDL_PushEvent(_event) == 0;
}

void SDLEvent::pumpEvents()
{
	SDL_PumpEvents();
}

void SDLEvent::setEventFilter(SDL_EventFilter filter)
{
	SDL_SetEventFilter(filter);
}    

SDL_EventFilter SDLEvent::getEventFilter()
{
	return SDL_GetEventFilter();
}

Uint8 SDLEvent::eventState(Uint8 type, int state)
{
	return SDL_EventState(type, state);
}

Uint8* SDLEvent::getKeyState(int &numkeys)
{
	return SDL_GetKeyState(&numkeys);
}

Uint8* SDLEvent::getKeyState()
{
	return SDL_GetKeyState(0);
}
  
SDLMod SDLEvent::getModState()
{
	return SDL_GetModState();
}

char* SDLEvent::getKeyName(SDLKey key)
{
	return SDL_GetKeyName(key);
}

void SDLEvent::setModState(SDLMod modstate)
{
	SDL_SetModState(modstate);
}

bool SDLEvent::enableKeyRepeat(int delay, int interval)
{
	return SDL_EnableKeyRepeat(delay, interval) == 0;
}

Uint8 SDLEvent::getMouseState(int *x, int *y)
{
	return SDL_GetMouseState(x, y);
}
  
Uint8 SDLEvent::getRelativeMouseState(int *x, int *y)
{
	return SDL_GetRelativeMouseState(x, y);
}

Uint8 SDLEvent::getAppState()
{
	return SDL_GetAppState();
}

int SDLEvent::joystickEventState(int state)
{
	return SDL_JoystickEventState(state);
}

//using that with threads
//http://vilimpoc.org/research/portmonitorg/sdl-tips-and-tricks.html

//Using correct handler for processing events...
// Handler should be const maybe ??
void SDLEvent::handleEvents(SDLEventHandler &handler)
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
