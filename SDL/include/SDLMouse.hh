#ifndef SDL_MOUSE_HH
#define SDL_MOUSE_HH

#include "SDLConfig.hh"

#include "SDLPoint.hh"

namespace RAGE
{
    namespace SDL
{


    /**
    * \class Mouse
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

    class Mouse
    {

    public:

        typedef enum
        {
            Left = 1, Middle, Right
        }
        Button;

        Point getPos();
        Point getDeltaPos();

        bool isButtonPressed(Button b);


        Mouse()
        {}
        virtual ~Mouse()
        {}

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
}

#endif //SDLMOUSE_HH
