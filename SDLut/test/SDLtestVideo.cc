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

class MyEngine : public DefaultEngine
{

public:

	RGBSurface loadedimage;
	Point imagepos;

	MyEngine( const std::string & imagefilename) : loadedimage(imagefilename),imagepos()
	{}

    virtual ~MyEngine(){}
			
    bool init(int width, int height)
	{
		imagepos.setx( (width - loadedimage.getWidth()) /2);
		imagepos.sety( (height - loadedimage.getHeight()) /2);
		return DefaultEngine::init(width,height);
	}

	bool resize(int width, int height)
	{
		imagepos.setx( (width - loadedimage.getWidth()) /2);
		imagepos.sety( (height - loadedimage.getHeight()) /2);
		return DefaultEngine::resize(width,height);
	}

	void render(VideoSurface & screen) const
    {
		screen.blit(loadedimage, imagepos );
		DefaultEngine::render(screen);
    }
};


//Main Program
int main(int argc, char** argv)
{

    Logger testlog("Test Log");

    //Setup example

    testlog << nl << " Enabling SDL Video... " << std::endl;
	App::getInstance().setName ("RAGE::SDL test - Video");
    App::getInstance().initVideo(false,false,true,false);

    testlog << nl << " Creating the User Interface... " << std::endl;
    //UI Creation
    MyUserInput ui;
    App::getInstance().getWindow()->getEventManager()->setKeyboard(&ui);

    App::getInstance().getWindow()->setBGColor(Color (64,0,0));
	
	//if argument we load the image in the test engine 
	if ( argc > 1)
		App::getInstance().getWindow()->setEngine(new MyEngine(std::string(argv[1])));
	//otherwise we use the default engine only.

    if (! (App::getInstance().getWindow()->resetDisplay()))
    {
        testlog << nl << "Display Creation FAILED !"<< std::endl;
        exit(0);
    }
    else
    {

        App::getInstance().getWindow()->mainLoop(2);

    }
    return 0;
}


