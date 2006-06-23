#ifndef SDL_JOYSTICK_HH
#define SDL_JOYSTICK_HH

#include "SDLConfig.hh"

#include "SDLPoint.hh"

namespace RAGE
{
    namespace SDL {

    class Joystick
    {
        friend class JoystickPool;
        protected:
        SDL_Joystick * const _joystick;

        Joystick(int index);

        public :

        ~Joystick();

        std::string getName();

        int getIndex();
        int numAxes();
        int numHats();
        int numButtons();

        signed int getAxisPos(int axis);
        // to think about the hat :  how to handle the different states and combinations
        bool isButtonPressed(int button);
        Point getBallDeltaPos(int ball);

    };

class JoystickPool
{
        std::vector <Joystick *> _pool;
        public:

        JoystickPool();
        virtual ~JoystickPool();

        int countAvailable();
        std::string getName(int index);
        Joystick * open(int index);
        void close(int index);

        ///update done automatically by events...
        void Update();

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
}

#endif
