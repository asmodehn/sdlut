#include "SDLMouse.hh"

namespace SDL
{


    Uint8 Mouse::updatePos()
    {
        return SDL_GetMouseState(&_posX,&_posY);
    }

    Uint8 Mouse::updateDeltaPos()
    {
        return SDL_GetRelativeMouseState(&_deltaPosX,&_deltaPosY);
    }


    Mouse::Mouse()
    {
        updatePos();
        updateDeltaPos();
    }

    int Mouse::getPosX()
    {
        updatePos();
        return _posX;
    }

    int Mouse::getPosY()
    {
        updatePos();
        return _posY;
    }

    int Mouse::getDeltaPosX()
    {
        updateDeltaPos();
        return _deltaPosX;
    }
    int Mouse::getDeltaPosY()
    {
        updateDeltaPos();
        return _deltaPosY;
    }

    bool Mouse::isButtonPressed(Button b)
    {
        return updatePos() & SDL_BUTTON(b);
    }

}
