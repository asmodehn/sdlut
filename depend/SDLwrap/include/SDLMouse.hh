#ifndef SDL_MOUSE_HH
#define SDL_MOUSE_HH

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

 /**
 * \class SDLMouseHandler
 *
 * \ingroup EventHandling
 *
 * \brief This class is an interface for classes wanted to handle SDL Mouse events
 *
 * It implements the interface for Mouse callbacks on event.
 *
 * \author Alex
 *
 * \date 2005/12/26
 *
 * Contact: asmodehn@gna.org
 *
 */

class MouseHandler
{
protected:


public:

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

};

}

#endif //SDLMOUSE_HH
