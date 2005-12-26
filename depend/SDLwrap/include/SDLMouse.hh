#ifndef SDLMOUSE_HH
#define SDLMOUSE_HH

#include "SDLConfig.hh"

namespace SDL
{

    class Mouse
    {
        friend class SDLApp;

    protected:


        int _posX, _posY;
        int _deltaPosX, _deltaPosY;
        Uint8 updatePos();
        Uint8 updateDeltaPos();

        Mouse();

    public:

        typedef enum
        {
            Left = 1, Middle, Right
        }
        Button;

        int getPosX();
        int getPosY();
        int getDeltaPosX();
        int getDeltaPosY();

        bool isButtonPressed(Button b);

    };

}

#endif //SDLMOUSE_HH
