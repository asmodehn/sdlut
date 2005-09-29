#include "SDLEventHandler.hh"

//Code for default event handler

bool SDLEventHandler::handleKeyboardEvent (SDL_keysym &keysym, bool pressed)
{ return false; }

bool SDLEventHandler::handleMouseMotionEvent (Uint8 state, Uint16 x, Uint16 y,
										 Sint16 xrel, Sint16 yrel)
{ return false; }

bool SDLEventHandler::handleMouseButtonEvent (Uint8 button, Uint16 x, Uint16 y,
										 bool pressed)
{ return false; }


bool SDLEventHandler::handleJoyAxisEvent (Uint8 joystick, Uint8 axis, Sint16 value)
{ return false; }

bool SDLEventHandler::handleJoyButtonEvent (Uint8 joystick, Uint8 button, bool pressed)
{ return false; }

bool SDLEventHandler::handleJoyHatEvent(Uint8 joystick, Uint8 hat, Uint8 value)
{ return false; }

bool SDLEventHandler::handleJoyBallEvent(Uint8 joystick, Uint8 ball, Sint16 xrel, Sint16 yrel)
{ return false; }
	
bool SDLEventHandler::handleActiveEvent(bool gain, Uint8 state)
{ return false; }

bool SDLEventHandler::handleResizeEvent(int w, int h)
{ return false; }

bool SDLEventHandler::handleSysWMEvent(void)
{ return false; }
	
bool SDLEventHandler::handleUserEvent(Uint8 type, int code, void* data1, void* data2)
{ return false; }
	
bool SDLEventHandler::handleQuitEvent(void)
{ return false; }
	
bool SDLEventHandler::handleEvent(SDL_Event &event)
{ return false; }

