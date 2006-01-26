#include "SDL.hh"
using namespace RAGE; // for the Logger only
using namespace RAGE::SDL;

static Logger testlog("Example");

//Defining UserInput
class MyUserInput : public Keyboard
{
public:

    virtual bool handleKeyEvent (SDL_keysym &keysym, bool pressed)
    {
        bool res = false;
        if (! (res = Keyboard::handleKeyEvent(keysym,pressed)))
            switch( keysym.sym )
            {
                case SDLK_ESCAPE:
                if (pressed==false)
                {
                    _quitRequested=true;
                    res=true;
                }
                break;
                case SDLK_F5:
                if (pressed==true)
                    App::getInstance().getWindow()->iconify();
                res = true;
                break;
                case SDLK_F6:
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
    RGBSurface _defaultlogo;
public:
    MyEngine() : _defaultlogo("data/SDL_logo.bmp")
    { }

    virtual ~MyEngine(){}

    bool init(int width, int height)
    {
		return true;
	}

    bool resize(int width, int height)
	{
		return true;
	}

    bool render(void) const
    {
        bool res = false;
        if ( _screen != NULL )
        {
            res= _screen->blit(_defaultlogo,Point((_screen->getWidth()-_defaultlogo.getWidth())/2,(_screen->getHeight()-_defaultlogo.getHeight())/2));
        }

        return res;
    }
};

//Main Program
int main(int argc, char** argv)
{


    //Setup example

    testlog << nl << " Enabling SDL Video... " << std::endl;
    App::getInstance().setName ("Example");
    App::getInstance().initVideo(false,false,true,false);

    //Getting video informations
    testlog << nl << *App::getInstance().getWindow()->getVideoInfo() << std::endl;

    testlog << nl << " Creating the User Interface... " << std::endl;
    //UI Creation
    MyUserInput ui;
    App::getInstance().getWindow()->getEventManager()->setKeyboard(&ui);


    App::getInstance().getWindow()->setBGColor(Color (128,0,0));
    App::getInstance().getWindow()->setEngine(new MyEngine());

    if (! (App::getInstance().getWindow()->reset()))
    {
        testlog << nl << "Display Creation FAILED !"<< std::endl;
        exit(0);
    }
    else
    {

        Cursor::warpCurrent(Point(50,50));

        App::getInstance().getWindow()->mainLoop();

    }

  return 0;
}


