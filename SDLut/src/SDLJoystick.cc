#include "Input/SDLJoystick.hh"
#include "SDLConfig.hh"
#include <cassert>

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





	std::map<short,Joystick::JoyHat> Joystick::JoyHatsdl2rage;
	std::map<std::string,Joystick::JoyHat> Joystick::JoyHatstr2rage;

	//based on the fact that Rage's enum map to in [0..number-1]. This way the vector is easily built
	std::vector<short> Joystick::InitJoyHatMapping()
{
	std::vector<short> result;
		
	std::map<Joystick::JoyHat,short> JoyHatrage2sdlmap;

		//using a max here to support partial mapping list...
	int maxvecindex =0;
		
#define ASSOCIATE( jh, sdljh, strjh ) JoyHatrage2sdlmap[jh] = sdljh; JoyHatsdl2rage[sdljh] = jh; JoyHatstr2rage[strjh] = jh; maxvecindex = (maxvecindex>jh)? maxvecindex : jh;
#include "SDLJoyHatMapping.inl"
#undef ASSOCIATE

{
	result.resize(maxvecindex+1, 0);

	std::map<Joystick::JoyHat,short>::iterator it = JoyHatrage2sdlmap.begin();
	std::map<Joystick::JoyHat,short>::iterator itEnd = JoyHatrage2sdlmap.end();
	for (; it != itEnd; ++it)
	{
		assert((*it).first >= 0 && (*it).first < static_cast<int>(result.size()));
		result[(*it).first] = (*it).second;
	}
}
return result;
}
	
	std::vector<short> Joystick::JoyHatrage2sdl = InitJoyHatMapping();
	



	
	short Joystick::JoyHat2sdl(Joystick::JoyHat jh)
{
	return JoyHatrage2sdl[jh];
}
	Joystick::JoyHat Joystick::sdl2JoyHat(short sdljh)
{
	return JoyHatsdl2rage[sdljh];
}
	Joystick::JoyHat Joystick::str2JoyHat(std::string strjh)
{
	return JoyHatstr2rage[strjh];
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

bool JoystickPool::handleJoyAxisEvent (unsigned short joystick, unsigned short axis, signed int value)
{
#ifdef DEBUG
    Log << nl << "Joystick n°" << joystick << " axis : " << axis << " value : " << value << std::endl;
    return true;
#else
    return false;
#endif
}

bool JoystickPool::handleJoyButtonEvent (unsigned short joystick, unsigned short button, bool pressed)
{
#ifdef DEBUG
    Log << nl << "Joystick n°" << joystick << " button : " << button << " pressed : " << pressed << std::endl;
    return true;
#else
    return false;
#endif
}

bool JoystickPool::handleJoyHatEvent(unsigned short joystick, Joystick::JoyHat hat, unsigned short value)
{
#ifdef DEBUG
    Log << nl << "Joystick n°" << joystick << " hat : " << hat << " value : " << value << std::endl;
    return true;
#else
    return false;
#endif
}

bool JoystickPool::handleJoyBallEvent(unsigned short joystick, unsigned short ball, signed int xrel, signed int yrel)
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
