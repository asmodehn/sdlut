#include "SDLMouse.hh"

namespace SDL
{
    Point Mouse::getPos()
    {
        int posX,posY;
        SDL_GetMouseState(&posX,&posY);
        return Point(posX,posY);
    }

    Point Mouse::getDeltaPos()
    {
        int rposX,rposY;
        SDL_GetRelativeMouseState(&rposX,&rposY);
        return Point(rposX,rposY);
    }

    bool Mouse::isButtonPressed(Button b)
    {
        return ( ( SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(b) ) != 0 );
    }


    	//Callbacks on Mouse Events
	bool MouseHandler::handleMouseMotionEvent (Uint8 state, Uint16 x, Uint16 y, Sint16 xrel, Sint16 yrel)
	{
	    return false;
	}
	bool MouseHandler::handleMouseButtonEvent (Uint8 button, Uint16 x, Uint16 y, bool pressed)
	{
	    return false;
	}

}
