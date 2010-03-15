#ifndef SDL_JOYSTICK_HH
#define SDL_JOYSTICK_HH

#include "Video/Rect.hh"
#include <vector>
#include <map>

//forward reference
typedef struct _SDL_Joystick SDL_Joystick;

namespace RAGE
{
namespace SDL
{

class Joystick
{
    friend class JoystickPool;
protected:
    SDL_Joystick * const _joystick;

    Joystick(int index);

public :

    typedef enum
    {
        Centered, Up, Right, Down, Left, RightUp, RightDown, LeftUp, LeftDown
    }
    JoyHat;

    ~Joystick();

    std::string getName();

    int getIndex();
    int numAxes();
    int numHats();
    int numButtons();

    signed int getAxisPos(int axis);
    // to think about the hat :  how to handle the different states and combinations
    bool isButtonPressed(int button);
    Rect getBallDeltaPos(int ball);

    static short JoyHat2sdl(JoyHat jh); //protect this ??
    static JoyHat sdl2JoyHat(short sdljh);
    static JoyHat str2JoyHat(std::string strjh);

private :

    static std::vector<short> JoyHatrage2sdl;
    static std::map<short,JoyHat> JoyHatsdl2rage;
    static std::map<std::string,JoyHat> JoyHatstr2rage;
    static std::vector<short> InitJoyHatMapping();


};

class JoystickPool
{
    std::vector <Joystick *> _pool;
public:

    JoystickPool();
    virtual ~JoystickPool();

    int countAvailable();
    std::string getName(int index);
    Joystick * open(int index);
    void close(int index);

    ///update done automatically by events...
    void Update();

    //Callbacks on Joystick Events
    virtual bool handleJoyAxisEvent (unsigned short joystick, unsigned short axis, signed int value);
    virtual bool handleJoyButtonEvent (unsigned short joystick, unsigned short button, bool pressed);
    virtual inline bool handleJoyButtonPressEvent (unsigned short joystick, unsigned short button)
    {
        return handleJoyButtonEvent(joystick, button, true);
    }
    virtual inline bool handleJoyButtonReleaseEvent (unsigned short joystick, unsigned short button)
    {
        return handleJoyButtonEvent(joystick, button, false);
    }
    virtual bool handleJoyHatEvent(unsigned short joystick, Joystick::JoyHat hat, unsigned short value);
    virtual bool handleJoyBallEvent(unsigned short joystick, unsigned short ball, signed int xrel, signed int yrel);

};

}
}

#endif
