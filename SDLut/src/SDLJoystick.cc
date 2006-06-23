#include "SDLJoystick.hh"

namespace RAGE
{
    namespace SDL {


JoystickPool::JoystickPool()
{
    _pool.reserve(SDL_NumJoysticks());
}

JoystickPool::~JoystickPool()
{
    for (unsigned int i=0;i< _pool.size();i++)
        if ( _pool[i] != NULL ) SDL_JoystickClose(_pool[i]->_joystick);
}

Joystick * JoystickPool::open(int index)
{
    if ( _pool[index] ==NULL )
        _pool[index]=new Joystick(index);
    return _pool[index];
}

void JoystickPool::close(int index)
{
    if ( _pool[index] !=NULL )
    {
        delete _pool[index];
        _pool[index]=NULL;
    }

}

int JoystickPool::countAvailable()
{
    Log << nl << "Joystick Pool size = " << _pool.size() << std::endl;
    return _pool.size();
}

void JoystickPool::Update()
{
    SDL_JoystickUpdate();
}

std::string JoystickPool::getName(int index)
{
    return std::string (SDL_JoystickName(index));
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

bool JoystickPool::handleJoyAxisEvent (Uint8 joystick, Uint8 axis, Sint16 value)
{
#ifdef DEBUG
    Log << nl << "Joystick n°" << joystick << " axis : " << axis << " value : " << value << std::endl;
    return true;
#else
    return false;
#endif
}

bool JoystickPool::handleJoyButtonEvent (Uint8 joystick, Uint8 button, bool pressed)
{
#ifdef DEBUG
    Log << nl << "Joystick n°" << joystick << " button : " << button << " pressed : " << pressed << std::endl;
    return true;
#else
    return false;
#endif
}

bool JoystickPool::handleJoyHatEvent(Uint8 joystick, Uint8 hat, Uint8 value)
{
#ifdef DEBUG
    Log << nl << "Joystick n°" << joystick << " hat : " << hat << " value : " << value << std::endl;
    return true;
#else
    return false;
#endif
}

bool JoystickPool::handleJoyBallEvent(Uint8 joystick, Uint8 ball, Sint16 xrel, Sint16 yrel)
{
#ifdef DEBUG
    Log << nl << "Joystick n°" << joystick << " ball : " << ball << " xrel : " << xrel << " yrel : " << yrel << std::endl;
    return true;
#else
    return false;
#endif
}
    }
}
