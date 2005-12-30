#ifndef SDL_JOYSTICK_HH
#define SDL_JOYSTICK_HH

#include "SDLConfig.hh"

namespace SDL {


    class Joystick
    {
    };

class JoystickHandler
{friend class EventManager;
protected:
        bool _quitRequested;
        public:

        	JoystickHandler() : _quitRequested(false){}
            virtual ~JoystickHandler() {}

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
};

}

#endif
