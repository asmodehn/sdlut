#ifndef SDLEVENTHANDLER_HH
#define SDLEVENTHANDLER_HH

#include "SDLConfig.hh"

/**
 * \class SDLEventHandler
 *
 * \ingroup EventHandling
 *
 * \brief This class is an interface for classes wanted to handle SDL events
 *
 * This class should be derivated by the classes wanted to handle SDL events.
 * It implements the interface for all callbacks on event.
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

class EventHandler
{
public:
	virtual	~EventHandler() {}
	
	//Callbacks on SDL_KEYUP or SDL_KEYDOWN
	virtual bool handleKeyboardEvent (SDL_keysym &keysym, bool pressed);
	virtual inline bool handleKeyPressEvent (SDL_keysym &keysym)
	{
		return handleKeyboardEvent (keysym, true);
	}
	virtual inline bool handleKeyReleaseEvent (SDL_keysym &keysym)
	{
		return handleKeyboardEvent (keysym, false);
	}
	
	//Callbacks on Mouse Events
	virtual bool handleMouseMotionEvent (Uint8 state, Uint16 x, Uint16 y,
										 Sint16 xrel, Sint16 yrel);
	virtual bool handleMouseButtonEvent (Uint8 button, Uint16 x, Uint16 y,
										 bool pressed);
	virtual inline bool handleMouseButtonPressEvent (Uint8 button, Uint16 x, Uint16 y)
	{
		return handleMouseButtonEvent(button, x, y, true);
	}
	virtual inline bool handleMouseButtonReleaseEvent (Uint8 button, Uint16 x, Uint16 y)
	{
		return handleMouseButtonEvent(button, x, y, false);
	}
	
	//Callbacks on Joystick Events
	virtual bool handleJoyAxisEvent (Uint8 joystick, Uint8 axis, Sint16 value);
	virtual bool handleJoyButtonEvent (Uint8 joystick, Uint8 button, bool pressed);
	virtual inline bool handleJoyButtonPressEvent (Uint8 joystick, Uint8 button)
	{
		return handleJoyButtonEvent(joystick, button, true);
	}
	virtual inline bool handleJoyButtonReleaseEvent (Uint8 joystick, Uint8 button)
	{
		return handleJoyButtonEvent(joystick, button, false);
	}
	virtual bool handleJoyHatEvent(Uint8 joystick, Uint8 hat, Uint8 value);
	virtual bool handleJoyBallEvent(Uint8 joystick, Uint8 ball, Sint16 xrel, Sint16 yrel);
	
	//Callbacks on Window / Display events
	virtual bool handleActiveEvent(bool gain, Uint8 state);
	virtual bool handleResizeEvent(int w, int h);
	//callback on platform-dependent windows manager event
	virtual bool handleSysWMEvent(void);
	
	//Callback on other Events
	virtual bool handleUserEvent(Uint8 type, int code, void* data1, void* data2);
	
	//Callback on Quit Event
	virtual bool handleQuitEvent(void);
	
	//Catch-all callback
	virtual bool handleEvent(SDL_Event &event);
	
};

} //namespace SDL

#endif
