#include "Input/SDLMouse.hh"
#include "SDLConfig.hh"
#include <cassert>

namespace SDLut
{
namespace input
{
std::map<short,Mouse::Button> Mouse::Buttonsdl2SDLut;
std::map<std::string,Mouse::Button> Mouse::Buttonstr2SDLut;
std::map<Mouse::Button,std::string> Mouse::ButtonSDLut2str;

//based on the fact that SDLut's enum map to in [0..number-1]. This way the vector is easily built
std::vector<short> Mouse::InitButtonMapping()
{
    std::vector<short> result;

    std::map<Mouse::Button,short> ButtonSDLut2sdlmap;

    //using a max here to support partial mapping list...
    int maxvecindex =0;

#define ASSOCIATE( button, sdlbutton, strbutton ) ButtonSDLut2sdlmap[button] = sdlbutton; Buttonsdl2SDLut[sdlbutton] = button; Buttonstr2SDLut[strbutton] = button;  ButtonSDLut2str[button] = strbutton; maxvecindex = (maxvecindex>button)? maxvecindex : button;
#include "SDLButtonMapping.inl"
#undef ASSOCIATE

    {
        result.resize(maxvecindex+1, 0);

        std::map<Mouse::Button,short>::iterator it = ButtonSDLut2sdlmap.begin();
        std::map<Mouse::Button, short>::iterator itEnd = ButtonSDLut2sdlmap.end();
        for (; it != itEnd; ++it)
        {
            assert((*it).first >= 0 && (*it).first < static_cast<int>(result.size()));
            result[(*it).first] = (*it).second;
        }
    }
    return result;
}

std::vector<short> Mouse::ButtonSDLut2sdl = InitButtonMapping();


short Mouse::Button2sdl(Mouse::Button b)
{
    return ButtonSDLut2sdl[b];
}
Mouse::Button Mouse::sdl2Button(short sdlb)
{
    return Buttonsdl2SDLut[sdlb];
}
std::string  Mouse::Button2str(Mouse::Button b)
{
    return ButtonSDLut2str[b];
}

Mouse::Button Mouse::str2Button(std::string strb)
{
    return Buttonstr2SDLut[strb];
}


video::Rect Mouse::getPos()
{
    int posX,posY;
    SDL_GetMouseState(&posX,&posY);
    return video::Rect(posX,posY,1,1);
}
// TODO : Maybe we can combine thee into just one, returning a Rect
video::Rect Mouse::getDeltaPos()
{
    int rposX,rposY;
    SDL_GetRelativeMouseState(&rposX,&rposY);
    return video::Rect(rposX,rposY,1,1);
}

bool Mouse::isButtonPressed(Button b)
{
    return ( ( SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(b) ) != 0 );
}


Mouse::Mouse()
{
    if (ButtonSDLut2sdl.empty())
    {
        InitButtonMapping();
    }
}

Mouse::~Mouse()
{
}

//Callbacks on Mouse Events
bool Mouse::handleMouseMotionEvent (bool button_pressed, unsigned int x, unsigned int y,signed int xrel, signed int yrel)
{
    bool res = false;
    return res;
}
bool Mouse::handleMouseButtonEvent (Button button, unsigned int x, unsigned int y, bool pressed)
{
    bool res = false;
    return res;
}
}
}
