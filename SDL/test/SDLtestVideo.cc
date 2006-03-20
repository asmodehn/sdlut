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
                    App::getInstance().getWindow()->toggleFullScreen();
                res = true;
                break;
                default:
                res = false;
            }
        return res;
    }
};

class MyEngine : public Engine
{

    RGBSurface _defaultlogocopy;
	Font _font;
	RGBSurface _text;

public:
    MyEngine()
		: _font("data/ECHELON.ttf",16),_text(_font,"Blahblahblah",Color(0,0,255),RGBColor(0,0xFF,0))
    {
        RGBSurface _defaultlogo("data/SDL_logo.bmp",Color(0xFF,0xFF,0xff));
        Log << nl << "Assignment ... TEST";
        _defaultlogocopy = _defaultlogo;
        Log << nl << "Assignment... END";
    }

    virtual ~MyEngine(){}

    bool init(int width, int height)
    {
            Log << nl << _defaultlogocopy;
            return true;
    }

    bool resize(int width, int height)
    {return true;}

    void render(VideoSurface* screen) const
    {
            Log << nl<< "Copie TEST";
            RGBSurface _defaultlogocopy2(_defaultlogocopy);
            Log << nl << "Copie END";
     screen->blit(_defaultlogocopy2,Point((screen->getWidth()-_defaultlogocopy2.getWidth())/2,(screen->getHeight()-_defaultlogocopy2.getHeight())/2));

	screen->blit(_text,Point(20,20));
    
    }
};

#include <math.h>
//if not define by math (why ??)
#ifndef M_PI
#define M_PI  3.14159265358979323846
#endif

//Main Program
int main(int argc, char** argv)
{

    Logger testlog("Test Log");

    //Setup example

    testlog << nl << " Enabling SDL Video... " << std::endl;
    App::getInstance().setName ("SDLtest");
    App::getInstance().initVideo(false,false,true,false);

    //Getting video informations
    testlog << nl << *App::getInstance().getWindow()->getVideoInfo() << std::endl;

    testlog << nl << " Creating the User Interface... " << std::endl;
    //UI Creation
    MyUserInput ui;
    App::getInstance().getWindow()->getEventManager()->setKeyboard(&ui);

    testlog << nl << " Creating the SDL Cursor... " << std::endl;
    Cursor cursor(blackArrow);
    cursor.show();
    Cursor::setCurrent(cursor);

    // RGBSurface bitmap (bitmapname);
    //
    // int newW=bitmap.getWidth()+60;
    // int newH=bitmap.getHeight()+60;

	App::getInstance().initText(); //to do before using the Engine

    App::getInstance().getWindow()->setBGColor(Color (128,0,0));
    App::getInstance().getWindow()->setEngine(new MyEngine());


    if (! (App::getInstance().getWindow()->resetDisplay()))
    {
        testlog << nl << "Display Creation FAILED !"<< std::endl;
        exit(0);
    }
    else
    {
        VideoSurface* display=App::getInstance().getWindow()->getDisplay();
        testlog << nl << *display << std::endl;

        //  display->blit(bitmap,Point(30,30));
        //
        //  RGBSurface smiley("icon.bmp",Color(255,255,255));
        //        smiley.optimise(true);
        //
        //  testlog << nl << std::boolalpha << display->blit(smiley,Point(50,50)) << std::endl;

        Cursor::warpCurrent(Point(50,50));

        App::getInstance().getWindow()->mainLoop();

    }

    //First test ended : go on to test OPENGL

    testlog << nl << " OPENGL activation... " << std::endl;

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


