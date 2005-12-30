#include "SDLwrap.hh"

using namespace SDL;

//TODO :akeyboard, mouse, joystick,and general handler that measure some stats on event handling, critical or not.

class  MyKeyboardHandler : public KeyboardHandler
{
        public:

        //Callbacks on SDL_KEYUP or SDL_KEYDOWN
        virtual bool handleKeyEvent (SDL_keysym &keysym, bool pressed)
        {
            bool res = false;
            if ( (res = KeyboardHandler::handleKeyEvent (keysym, pressed) ) == false )
            switch (keysym.sym)
            {
                case SDLK_a : std::cout << "SDL Code : a" << std::endl; res = true; break;
                case SDLK_q : std::cout << "SDL Code : q" << std::endl; res = true; break;
                default : res=false;
            }
            return res;
        }
};


int main( int argc, char* argv[])
{
    Logger testlog ("SDLtestInput");

    testlog << nl << "Test Input Started !" << std::endl;
    App::getInstance().setName ("SDLtestInput");

//EVENTS INITIALISED ALONG WITH VIDEO... Think about initializins the event by default, without actually creating the window...
//NOT POSSIBLE : THE EVENTS DONT WORK WITHOUT ANY WINDOW...
    testlog << nl << "Initialising Window..." << std::endl;
	App::getInstance().initVideo(false,false,true,false);


    testlog << nl << "Setting up Keyboard..." << std::endl;
	MyKeyboardHandler ui;
    App::getInstance().getWindow()->getEventManager()->setKeyboardHandler(&ui);

	testlog << nl << "Displaying Window..." << std::endl;
    App::getInstance().getWindow()->reset(640,480);

    testlog << nl << "Main Loop..." << std::endl;
    App::getInstance().getWindow()->mainLoop();

    testlog << nl << "Displaying Window..." << std::endl;
    App::getInstance().getWindow()->reset(640,480);

    testlog << nl << "Setting up TextInput with UniCode enabled..." << std::endl;
	TextInputHandler ui2;
    App::getInstance().getWindow()->getEventManager()->setKeyboardHandler(&ui2);

    testlog << nl << "Main Loop..." << std::endl;
    App::getInstance().getWindow()->mainLoop();

	return 0;

}
