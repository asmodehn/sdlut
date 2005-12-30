#ifndef SDL_JOYSTICK_HH
#define SDL_JOYSTICK_HH

#include "SDLConfig.hh"

#include "SDLPoint.hh"

namespace SDL {


    class Joystick
    {
        SDL_Joystick * const _joystick;

        public :

        static int countAvailable();
        static bool opened(int index);

        ///update done automatically by events...
        static void Update();

        //exception if no joystick -> todo asap !
        Joystick(int index = 0);
        ~Joystick();

        //maybe this one is better static ?? depend how we intend to use it...
        std::string getName();

        int getIndex();
        int numAxes();
        int numHats();
        int numButtons();

        signed int getAxisPos(int axis);
        // to think about the hat :  how to handle the different states
        bool isButtonPressed(int button);
        Point getBallDeltaPos(int ball);

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
