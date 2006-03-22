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

class MyEngine : public Engine
{

    RGBSurface _defaultlogocopy;
	Font _font;
	RGBSurface _text;

public:
    MyEngine()
		: _font("data/ECHELON.ttf",16),_text(_font,"Blahblahblah",Color(0,0,255),RGBColor(0,0xFF,0))
    {
        //RGBSurface _defaultlogo("data/SDL_logo.bmp",Color(0xFF,0xFF,0xff));
        Log << nl << "Assignment ... TEST";
        _defaultlogocopy = RGBSurface("data/SDL_logo.bmp",Color(0xFF,0xFF,0xff));
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
    return 0;
}


