#include "SDLKeyboard.hh"
#include "SDLEventManager.hh"

namespace SDL
{

    Uint8* Keyboard::getKeyState(int &numkeys)
    {
        return SDL_GetKeyState(&numkeys);
    }

    Uint8* Keyboard::getKeyState()
    {
        return SDL_GetKeyState(0);
    }

    SDLMod Keyboard::getModState()
    {
        return SDL_GetModState();
    }

    char* Keyboard::getKeyName(SDLKey key)
    {
        return SDL_GetKeyName(key);
    }

    void Keyboard::setModState(SDLMod modstate)
    {
        SDL_SetModState(modstate);
    }

    bool Keyboard::enableKeyRepeat(int delay, int interval)
    {
        return SDL_EnableKeyRepeat(delay, interval) == 0;
    }

    bool Keyboard::handleKeyEvent (SDL_keysym &keysym, bool pressed)
    {
        bool res = false;
#ifdef DEBUG
            Log << nl << " Key Name : " << getKeyName(keysym.sym) <<  " pressed : " << pressed << std::endl;
            res=true;
#endif
        return res;
    }

    TextInput::TextInput()
    {
        SDL_EnableUNICODE(1);
    }

    TextInput::~TextInput()
    {
        SDL_EnableUNICODE(0);
    }


    bool TextInput::handleKeyEvent (SDL_keysym &keysym, bool pressed)
    {
        bool res = false;

        //get the unicode character
        if (!res && pressed)
        {
            if( (keysym.unicode & 0xff80) == 0)
            {
                std::cout << "unicode char : " << char(keysym.unicode & 0x7F) << std::endl;
                res=true;
            }
            else //mess with international codes...
            {
                switch( keysym.sym )
                {
                    //deal with international characters
                    default:
                    res=false;
                }
            }
        }
        //TODO on every Event Loop (not critical, and not only keyboard...
        std::cout << std::flush;

        return res;

    }

}
