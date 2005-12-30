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

    bool KeyboardHandler::handleKeyEvent (SDL_keysym &keysym, bool pressed)
    {
        bool res = false;
        switch( keysym.sym )
        {
            case SDLK_ESCAPE:
            if (pressed==false)
            {
#ifdef DEBUG
    Log << nl << "Quit requested !" << std::endl;
#endif
                _quitRequested=true;
                res=true;
            }
            break;
            default:
            res=false; break;
        }
        return res;
    }

    TextInputHandler::TextInputHandler()
    {
        SDL_EnableUNICODE(1);
    }

    TextInputHandler::~TextInputHandler()
    {
        SDL_EnableUNICODE(0);
    }


    bool TextInputHandler::handleKeyEvent (SDL_keysym &keysym, bool pressed)
    {
        bool res = false;

        //call the default Keyboard Handler
        res = KeyboardHandler::handleKeyEvent (keysym,pressed);
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
        else //pressed = false
        {
            switch( keysym.sym )
            {
                //deal with other keys for release ( UNICODE doesnt work on released event )
                default:
                res=false;
            }
        }
        //TODO on every Event Loop (not critical, and not only keyboard...
        std::cout << std::flush;

        return res;

    }

}
