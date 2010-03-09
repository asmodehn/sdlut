#include "SDL.hh"
#include "Logger.hh"
using namespace RAGE;
using namespace RAGE::SDL;

#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

Logger Log("Test Events");


//Defining general EventHandler
class MyGeneralHandler : public DefaultEventHandler
{
	friend class EventManager;
        bool _quitRequested;

        public:

			MyGeneralHandler(): DefaultEventHandler() {};
			virtual ~MyGeneralHandler() {};


			//Callbacks on Window / Display events
            virtual bool handleActiveEvent(bool gain, bool active, bool inputfocus, bool mousefocus)
			{
				::Log << nl << "Active" ;
				return true;
			}

            virtual bool handleResizeEvent(int w, int h)
			{
				DefaultEventHandler::handleResizeEvent(w,h);
        		::Log << nl << "Resize";
				return true;
			}

            virtual bool handleExposeEvent()
			{
				::Log << nl << "Expose";
				return true;
			}

            //callback on platform-dependent windows manager event
            virtual bool handleSysWMEvent(void)
			{
        		::Log << nl << "System WM";
				return true;
			}

            //Callback on other Events
			virtual bool handleUserEvent(Event::Type type, int code, void* data1, void* data2)
			{
        		::Log << nl <<"User Event";
				return true;
			}

            //Callback on Quit Event
            virtual bool handleQuitEvent(void)
			{
				DefaultEventHandler::handleQuitEvent();
				::Log << nl << "Quit";
				return true;
			}

			//Catch-all callback
            virtual bool handleEvent(Event & cevent)
			{
				//Getting the details of the Event
				::Log << nl << "Last chance handler : " << cevent.getType() << std::endl;
				return true;
			}

};

class MyKeyboard: public DefaultKeyboard
{
public:

	MyKeyboard() : DefaultKeyboard() {}

	virtual bool handleKeyEvent (const Sym &s, bool pressed)
	{
		DefaultKeyboard::handleKeyEvent(s,pressed);

		::Log << nl << "SDL Name : "<< getSDLKeyName(s.getKey())
			<< " | Key Name : " << getKeyName(s.getKey());
		if ( pressed ) ::Log << " pressed  "; else ::Log << " released ";
		::Log	<< " | Modifier : " << getModifierName(s.getMod()) ;

        return true;
	}
};

class MyMouse: public Mouse
{
public:

	MyMouse() : Mouse() {}

	//Callbacks on Mouse Events
        virtual bool handleMouseMotionEvent (bool button_pressed, unsigned int x, unsigned int y,
                                             signed int xrel, signed int yrel)
		{
				std::stringstream str;
				if ( button_pressed )
				{
					::Log << nl << "Mouse Drag : X=" << x << " Y=" << y << " Xrel=" << xrel << " Yrel=" << yrel;
				}
				else
				{
					::Log << nl <<"Mouse Moved : X=" << x << " Y=" << y << " Xrel=" << xrel << " Yrel=" << yrel ;
				}
			return true;
		}

        virtual bool handleMouseButtonEvent (Button button, unsigned int x, unsigned int y,
                                             bool pressed)
		{
				std::string but=" Button";
				switch (button)
				{
				case Left: but="Left Button";
					break;
				case Middle: but="Middle Button";
					break;
				case Right: but="Right Button";
					break;
				case WheelUp: but="WheelUp Button";
					break;
				case WheelDown: but="WheelDown Button";
					break;
				default: but="Unknown Button";
					break;
				}

				::Log << nl << but << " X=" << x << "Y=" << y << " pressed? " << pressed;
			return true;
		}

};

//Main Program
int main(int argc, char** argv)
{

    Logger testlog("Test Log");

    //Setup example

    testlog << nl << " Enabling SDL Video... " << std::endl;
	App::getInstance().setName ("RAGE::SDL test - Font");
    App::getInstance().initVideo(false,false,false);
	App::getInstance().initText();

    testlog << nl << " Creating the User Interface... " << std::endl;

    App::getInstance().getDisplay().setBGColor(Color (64,0,0));

    MyGeneralHandler gh;
	MyKeyboard kb;
	MyMouse mouse;
    App::getInstance().getDisplay().getEventManager().setKeyboard(&kb);
	App::getInstance().getDisplay().getEventManager().setMouse(&mouse);
   App::getInstance().getDisplay().getEventManager().setGeneralHandler(&gh);


    if (! (App::getInstance().getDisplay().setDisplay(800,600)))
    {
        testlog << nl << "Display Creation FAILED !"<< std::endl;
        exit(0);
    }
    else
    {
        App::getInstance().getDisplay().mainLoop();
    }

    return 0;
}


