#include "SDL.hh"
using namespace RAGE;
using namespace RAGE::SDL;


//Defining UserInput
class MyUserInput : public Keyboard
{
public:

    virtual bool handleKeyEvent (const Sym &s, bool pressed)
    {
        bool res = false;
            switch( s.getKey() )
            {
                case KEscape:
                if (pressed==false)
                {
#ifdef DEBUG
                    Log << nl << "Quit requested !" << std::endl;
#endif

                    _quitRequested=true;
                    res=true;
                }
                break;
                case KF5:
                if (pressed==true)
                    App::getInstance().getWindow()->iconify();
                res = true;
                break;
				case KF6:
                if (pressed==true)
                    App::getInstance().getWindow()->setFullscreen(!App::getInstance().getWindow()->isFullscreen());
                res = true;
                break;
                default:
                res = false;
            }
        return res;
    }
};

//TODO : Engine to display a BMP in texture...


//Main Program
int main(int argc, char** argv)
{

    Logger testlog("Test Log");

    //Setup example

    testlog << nl << " Enabling SDL Video... " << std::endl;
	App::getInstance().setName ("RAGE::SDL test - OpenGL");
    App::getInstance().initVideo(false,false,true,false);

    //Getting video informations
    testlog << nl << *App::getInstance().getWindow()->getVideoInfo() << std::endl;

    testlog << nl << " Creating the User Interface... " << std::endl;
    //UI Creation
    MyUserInput ui;
    App::getInstance().getWindow()->getEventManager()->setKeyboard(&ui);

    testlog << nl << " OPENGL activation... " << std::endl;
    App::getInstance().getWindow()->setBGColor(Color (128,0,0));

    MyUserInput ui2; // another ui, since the first is closed ( but not deleted )
    App::getInstance().getWindow()->getEventManager()->setKeyboard(&ui2);
    testlog << nl <<"display reset" << std::endl;

    //GLManager test
    GLManager * glman=App::getInstance().getWindow()->getGLManager();
    testlog << nl<<std::boolalpha <<
    "setRsize(5) " << glman->setRSize(5) << nl <<
    "setGSize(5) " << glman->setGSize(5) << nl <<
    "setBSize(5) " << glman->setBSize(5) << nl <<
    "setASize(5) " << glman->setASize(5) << nl <<
    "setBufferSize(5) " << glman->setBufferSize(12) << nl <<
    std::endl;

    App::getInstance().getWindow()->setOpenGL(true,new DefaultGLEngine());

    if(App::getInstance().getWindow()->resetDisplay())
    {


        //GLManager test
        testlog << nl << *glman << std::endl;

        VideoSurface* display=App::getInstance().getWindow()->getDisplay();
        testlog << nl << "calling display->debug() " << std::endl;
        testlog << nl << *display <<std::endl;

        testlog << nl << std::boolalpha << " setDepthSize(16) " << glman->setDepthSize(16) << std::endl;

        testlog << nl << *glman << std::endl;

        testlog << nl << "loop... " << std::endl;
        App::getInstance().getWindow()->mainLoop();
    }

    return 0;
}


