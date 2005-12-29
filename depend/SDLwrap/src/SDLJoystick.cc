#include "SDLJoystick.hh"

namespace SDL {

JoystickHandler::JoystickHandler(EventManager * eventmanager)
 :_eventmanager(eventmanager)
 {

}

bool JoystickHandler::handleJoyAxisEvent (Uint8 joystick, Uint8 axis, Sint16 value)
{ return false; }

bool JoystickHandler::handleJoyButtonEvent (Uint8 joystick, Uint8 button, bool pressed)
{ return false; }

bool JoystickHandler::handleJoyHatEvent(Uint8 joystick, Uint8 hat, Uint8 value)
{ return false; }

bool JoystickHandler::handleJoyBallEvent(Uint8 joystick, Uint8 ball, Sint16 xrel, Sint16 yrel)
{ return false; }

}
