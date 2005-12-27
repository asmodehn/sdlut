#include "SDLKeyboard.hh"
#include "SDLEventManager.hh"

namespace SDL {

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


KeyboardHandler::KeyboardHandler(EventManager * eventmanager)
 :_eventmanager(eventmanager)
 {

}

bool KeyboardHandler::handleKeyEvent (SDL_keysym &keysym, bool pressed)
{
	    bool res = false;
		switch( keysym.sym ) {
    		case SDLK_ESCAPE: if (pressed==false) _eventmanager->_quitRequested=true; res=true; break;
	    default: res=false;
		}
		return res;
}

}
