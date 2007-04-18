#include "SDLMouse.hh"
#include "SDLConfig.hh"
#include <cassert>

namespace RAGE
{
    namespace SDL
{
	std::map<short,Mouse::Button> Mouse::Buttonsdl2rage;
	std::map<std::string,Mouse::Button> Mouse::Buttonstr2rage;

	//based on the fact that Rage's enum map to in [0..number-1]. This way the vector is easily built
	std::vector<short> Mouse::InitButtonMapping()
	{
		std::vector<short> result;
		
		std::map<Mouse::Button,short> Buttonrage2sdlmap;

		//using a max here to support partial mapping list...
		int maxvecindex =0;
		
#define ASSOCIATE( button, sdlbutton, strbutton ) Buttonrage2sdlmap[button] = sdlbutton; Buttonsdl2rage[sdlbutton] = button; Buttonstr2rage[strbutton] = button; maxvecindex = (maxvecindex>button)? maxvecindex : button;
#include "SDLButtonMapping.inl"
#undef ASSOCIATE

{
	result.resize(maxvecindex+1, 0);

	std::map<Mouse::Button,short>::iterator it = Buttonrage2sdlmap.begin();
	std::map<Mouse::Button, short>::iterator itEnd = Buttonrage2sdlmap.end();
	for (; it != itEnd; ++it)
	{
		assert((*it).first >= 0 && (*it).first < static_cast<int>(result.size()));
		result[(*it).first] = (*it).second;
	}
}
return result;
	}
	
	std::vector<short> Mouse::Buttonrage2sdl = InitButtonMapping();
	



	
	short Mouse::Button2sdl(Mouse::Button b)
{
	return Buttonrage2sdl[b];
}
	Mouse::Button Mouse::sdl2Button(short sdlb)
{
	return Buttonsdl2rage[sdlb];
}
	Mouse::Button Mouse::str2Button(std::string strb)
{
	return Buttonstr2rage[strb];
}

	
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

    
    Mouse::Mouse()
    {
	    if (Buttonrage2sdl.empty())
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
#ifdef DEBUG
        Log << nl << " Button pressed ? " << button_pressed << ", x : " << x << ", y : " << y << ", xrel : " << xrel << ", yrel : " << yrel << std::endl;
        res = true;
#endif
        return res;
	}
	bool Mouse::handleMouseButtonEvent (Button button, unsigned int x, unsigned int y, bool pressed)
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
