#include "SDL.hh"
using namespace RAGE;
using namespace RAGE::SDL;

//TODO :akeyboard, mouse, joystick,and general handler that measure some stats on event handling, critical or not.

class  MyKeyboard : public Keyboard
{
        public:

        //Callbacks on SDL_KEYUP or SDL_KEYDOWN
        virtual bool handleKeyEvent (const Sym &s, bool pressed)
        {
            bool res = false;
            switch (s.getKey())
            {
                case KEscape :  if (pressed==false)
            {
#ifdef DEBUG
    Log << nl << "Quit requested !" << std::endl;
#endif
                _quitRequested=true;
                res=true;
            }
            break;
                default : Log << nl << " Key Name : " << getKeyName(s.getKey()) <<  " pressed : " << pressed; res=true; break;
            }
            return res;
        }
};

class  MyTextInput : public TextInput
{
        public:

        //Callbacks on SDL_KEYUP or SDL_KEYDOWN
        virtual bool handleKeyEvent (const Sym &s, bool pressed)
        {
            bool res = false;
            switch (s.getKey())
            {
                case KEscape:  if (pressed==false)
            {
#ifdef DEBUG
    Log << nl << "Quit requested !" << std::endl;
#endif
                _quitRequested=true;
                res=true;
            }
            break;
                default : res = TextInput::handleKeyEvent (s, pressed); break;
            }
            return res;
        }
};


int main( int argc, char* argv[])
{
    Logger testlog ("SDLtestInput");

    testlog << nl << "Test Input Started !" << std::endl;
    App::getInstance().setName ("SDLtestInput");

//NB : THE EVENTS DONT WORK WITHOUT ANY WINDOW...
    testlog << nl << "Initialising Window...";
	App::getInstance().initVideo(false,false,true,false);

    testlog << nl << "Enabling Joystick..." ;
	if (App::getInstance().initJoystick())
	{

        if (App::getInstance().getJoystickPool()->countAvailable() > 0)
        {
            testlog << nl << "Opening Joystick 0..." ;
            App::getInstance().getJoystickPool()->open(0);
        }
	}

    testlog << nl << "Setting up Keyboard...";
	MyKeyboard ui;
    App::getInstance().getWindow()->getEventManager()->setKeyboard(&ui);

	testlog << nl << "Displaying Window...";
    App::getInstance().getWindow()->resetDisplay(640,480);

    testlog << nl << "Main Loop...";
    App::getInstance().getWindow()->mainLoop();

    testlog << nl << "Displaying Window...";
    App::getInstance().getWindow()->resetDisplay(640,480);

    testlog << nl << "Setting up TextInput with UniCode enabled...";
	MyTextInput ui2;
    App::getInstance().getWindow()->getEventManager()->setKeyboard(&ui2);

    testlog << nl << "Main Loop...";
    App::getInstance().getWindow()->mainLoop();

	return 0;

}
