#ifndef SDL_KEYBOARD_HH
#define SDL_KEYBOARD_HH

#include "SDLConfig.hh"

namespace RAGE
{
    namespace SDL
{

class EventManager;

    ///This class is not suitable for Full Text Input. Use TextInput instead.
    ///However this class is well adapted to key press / release detection, for gaming purpose...
    class Keyboard
    {


    friend class EventManager;
        protected:
        bool _quitRequested;

        public:

        Keyboard() : _quitRequested(false){}
        virtual ~Keyboard() {}

    //Get a snapshot of the current keyboard state
	Uint8* getKeyState (int &numkeys);
	Uint8* getKeyState (void);

	//get the current key modifier state
	//TODO : where this SDLMod comes from ?
	SDLMod getModState (void);
	//set the current key modifier state
	void setModState(SDLMod modstate);

	//get the name of an SDL virtual key symbol
	char* getKeyName(SDLKey key);

	// Unicode keyboard translation
	bool enableUNICODE(void);
	bool disableUNICODE(void);
	bool isUNICODEEnabled(void);

	//Params Key repeat
	bool enableKeyRepeat (int delay = SDL_DEFAULT_REPEAT_DELAY,
								int interval = SDL_DEFAULT_REPEAT_INTERVAL);


        //Callbacks on SDL_KEYUP or SDL_KEYDOWN
        virtual bool handleKeyEvent (SDL_keysym &keysym, bool pressed);
        virtual inline bool handleKeyPressEvent (SDL_keysym &keysym)
        {
            return handleKeyEvent (keysym, true);
        }
        virtual inline bool handleKeyReleaseEvent (SDL_keysym &keysym)
        {
            return handleKeyEvent (keysym, false);
        }

    };

    ///This class is not suitable for Gaming Input (doesnt detect key releases). Use Keyboard instead.
    ///However this class is well adapted for accurate text typing, with unicode enabled.
    class TextInput : public Keyboard
    {
        public:
        TextInput();
        virtual ~TextInput();

        //Callbacks on SDL_KEYUP or SDL_KEYDOWN
        virtual bool handleKeyEvent (SDL_keysym &keysym, bool pressed);

    };
}
}

#endif
