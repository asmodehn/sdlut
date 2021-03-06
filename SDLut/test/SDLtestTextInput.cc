#include "SDL.hh"
#include "Logger.hh"
using namespace RAGE;

using namespace SDLut;


#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

RAGE::Logger Log("Test Text Input");


//Defining general EventHandler
class MyGeneralHandler : public system::DefaultEventHandler
{
    friend class EventManager;

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
    virtual bool handleUserEvent(system::Event::Type type, int code, void* data1, void* data2)
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
    virtual bool handleEvent(system::Event & cevent)
    {
        //Getting the details of the Event
        ::Log << nl << "Last chance handler : " << cevent.getType() << std::endl;
        return true;
    }

};

//Defining UserInput
class MyKeyboard : public input::TextInput
{
public:

    MyKeyboard() : input::TextInput() {}

    virtual bool handleKeyEvent (const Sym &s, bool pressed)
    {
        TextInput::handleKeyEvent(s,pressed);

        ::Log << nl << "Character : " << s.getChar();

        return true;
    }
};



//Main Program
int main(int argc, char** argv)
{

    RAGE::Logger testlog("Test Log");

    //Setup example

    testlog << nl << " Enabling SDL Video... " << std::endl;
    App::getInstance().setName ("SDLut::SDL test - Font");
    App::getInstance().initVideo(false,false,false);
    App::getInstance().initText();

    testlog << nl << " Creating the User Interface... " << std::endl;

    App::getInstance().getDisplay().getScreenBuffer().setBGColor(video::Color (64,0,0));

    MyGeneralHandler gh;
    MyKeyboard kb;

    App::getInstance().getDisplay().getEventManager().setKeyboard(&kb);
    App::getInstance().getDisplay().getEventManager().setGeneralHandler(&gh);


    if (! (App::getInstance().getDisplay().setDisplay(800,600)))
    {
        testlog << nl << "Display Creation FAILED !"<< std::endl;
        exit(0);
    }
    else if ( App::getInstance().getDisplay().show() )
    {
        App::getInstance().getDisplay().mainLoop();
    }

    return 0;
}


