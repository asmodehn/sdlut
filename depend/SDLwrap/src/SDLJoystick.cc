#include "SDLJoystick.hh"

namespace SDL {


int Joystick::countAvailable()
{
    return SDL_NumJoysticks();
}

bool Joystick::opened(int index)
{
    return ( SDL_JoystickOpened(index)!=0);
}

void Joystick::Update()
{
    SDL_JoystickUpdate();
}

Joystick::Joystick(int index) : _joystick(SDL_JoystickOpen(index))
{
}

Joystick::~Joystick()
{
    SDL_JoystickClose(_joystick);
}

std::string Joystick::getName()
{
    return std::string (SDL_JoystickName(getIndex()));
}

int Joystick::getIndex()
{
    return SDL_JoystickIndex(_joystick);
}

int Joystick::numAxes()
{
    return SDL_JoystickNumAxes(_joystick);
}

int Joystick::numHats()
{
    return SDL_JoystickNumHats(_joystick);
}

int Joystick::numButtons()
{
    return SDL_JoystickNumButtons(_joystick);
}

signed int Joystick::getAxisPos(int axis)
{
    return SDL_JoystickGetAxis(_joystick,axis);
}

bool Joystick::isButtonPressed(int button)
{
    return (SDL_JoystickGetButton(_joystick, button) != 0 );
}

Point Joystick::getBallDeltaPos(int ball)
{
    int dx,dy;
    if (0 == SDL_JoystickGetBall(_joystick,ball,&dx, &dy))
    {
        return Point(dx,dy);
    }
    else
    {
    #ifdef DEBUG
    Log << nl << "Error while getting JoyBall Delta Position" << std::endl;
    #endif
        return Point(0,0); // no movement...
    }
}

bool JoystickHandler::handleJoyAxisEvent (Uint8 joystick, Uint8 axis, Sint16 value)
{ return false; }

bool JoystickHandler::handleJoyButtonEvent (Uint8 joystick, Uint8 button, bool pressed)
{ return false; }

bool JoystickHandler::handleJoyHatEvent(Uint8 joystick, Uint8 hat, Uint8 value)
{ return false; }

bool JoystickHandler::handleJoyBallEvent(Uint8 joystick, Uint8 ball, Sint16 xrel, Sint16 yrel)
{ return false; }

}
