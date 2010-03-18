#ifndef SDL_MOUSE_HH
#define SDL_MOUSE_HH

#include "Video/Rect.hh"

#include <vector>
#include <map>
#include <string>

namespace SDLut
{
namespace input
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
        Left = 1, Middle, Right, WheelUp, WheelDown
    }
    Button;

    video::Rect getPos();
    video::Rect getDeltaPos();

    bool isButtonPressed(Button b);


    Mouse();
    virtual ~Mouse();

    //Callbacks on Mouse Events
    virtual bool handleMouseMotionEvent (bool button_pressed, unsigned int x, unsigned int y,
                                         signed int xrel, signed int yrel);
    virtual bool handleMouseButtonEvent (Button button, unsigned int x, unsigned int y,
                                         bool pressed);
    inline bool handleMouseButtonPressEvent (Button button, unsigned int x, unsigned int y)
    {
        return handleMouseButtonEvent(button, x, y, true);
    }
    inline bool handleMouseButtonReleaseEvent (Button button, unsigned int x, unsigned int y)
    {
        return handleMouseButtonEvent(button, x, y, false);
    }

// 	    protected :

    static short Button2sdl(Button b); //protect this ??
    static Button sdl2Button(short sdlb);
    static std::string Button2str(Mouse::Button b);
    static Button str2Button(std::string strb);

private :

    static std::vector<short> ButtonSDLut2sdl;
    static std::map<short,Button> Buttonsdl2SDLut;
    static std::map<std::string,Button> Buttonstr2SDLut;
    static std::map<Mouse::Button,std::string> ButtonSDLut2str;
    static std::vector<short> InitButtonMapping();

};

}
}

#endif //SDLMOUSE_HH
