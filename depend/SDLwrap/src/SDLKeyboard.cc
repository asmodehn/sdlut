#include "SDLKeyboard.hh"

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


bool KeyboardHandler::handleKeyEvent (SDL_keysym &keysym, bool pressed)
{
    return false;
}

}
