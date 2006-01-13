#include "SDLMouse.hh"

namespace RAGE
{
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
	bool Mouse::handleMouseMotionEvent (Uint8 state, Uint16 x, Uint16 y, Sint16 xrel, Sint16 yrel)
	{
	    bool res = false;
#ifdef DEBUG
        Log << nl << " State : " << state << ", x : " << x << ", y : " << y << ", xrel : " << xrel << ", yrel : " << yrel << std::endl;
        res = true;
#endif
        return res;
	}
	bool Mouse::handleMouseButtonEvent (Uint8 button, Uint16 x, Uint16 y, bool pressed)
	{
	    bool res = false;
#ifdef DEBUG
        Log << nl << " Button : " << button << ", x : " << x << ", y : " << y << "pressed : " << pressed << std::endl;
        res = true;
#endif
        return res;
	}
}
}
