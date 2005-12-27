#ifndef SDL_KEYBOARD_HH
#define SDL_KEYBOARD_HH

namespace SDL
{

    class Keyboard
    {

    };

    class KeyboardHandler
    {
        public:
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

    };
}

#endif
