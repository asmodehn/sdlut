#include "SDLEventHandler.hh"

namespace SDL {
	
//Code for default event handler

bool EventHandler::handleKeyboardEvent (SDL_keysym &keysym, bool pressed)
{ return false; }

bool EventHandler::handleMouseMotionEvent (Uint8 state, Uint16 x, Uint16 y,
										 Sint16 xrel, Sint16 yrel)
{ return false; }

bool EventHandler::handleMouseButtonEvent (Uint8 button, Uint16 x, Uint16 y,
										 bool pressed)
{ return false; }


bool EventHandler::handleJoyAxisEvent (Uint8 joystick, Uint8 axis, Sint16 value)
{ return false; }

bool EventHandler::handleJoyButtonEvent (Uint8 joystick, Uint8 button, bool pressed)
{ return false; }

bool EventHandler::handleJoyHatEvent(Uint8 joystick, Uint8 hat, Uint8 value)
{ return false; }

bool EventHandler::handleJoyBallEvent(Uint8 joystick, Uint8 ball, Sint16 xrel, Sint16 yrel)
{ return false; }
	
bool EventHandler::handleActiveEvent(bool gain, Uint8 state)
{ return false; }

bool EventHandler::handleResizeEvent(int w, int h)
{ return false; }

bool EventHandler::handleSysWMEvent(void)
{ return false; }
	
bool EventHandler::handleUserEvent(Uint8 type, int code, void* data1, void* data2)
{ return false; }
	
bool EventHandler::handleQuitEvent(void)
{ return false; }
	
bool EventHandler::handleEvent(SDL_Event &event)
{ return false; }

}
