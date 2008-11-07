#include "SDL.hh"
#include "Logger.hh"
using namespace RAGE;
using namespace RAGE::SDL;

Logger Log("Test Video");

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
                    App::getInstance().getWindow().iconify();
                res = true;
                break;
		case KF6:
                if (pressed==true)
				{
					//App::getInstance().getWindow().resizeDisplay(800, 600);
                    App::getInstance().getWindow().setFullscreen(!App::getInstance().getWindow().isFullscreen());
				}
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

	MyEngine( const std::string & imagefilename) : loadedimage(imagefilename,RGBAColor(0,0,0,200)),imagepos()
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
    App::getInstance().initVideo(true,false,true,false);
    
	App::getInstance().setName ("RAGE::SDL test - Video");
    

    testlog << nl << " Creating the User Interface... " << std::endl;
    //UI Creation
    MyUserInput ui;
    App::getInstance().getWindow().getEventManager().setKeyboard(&ui);

    App::getInstance().getWindow().setBGColor(Color (128,0,0));
	
	//if argument we load the image in the test engine 
	MyEngine * engine = NULL;
	if ( argc > 1)
	{
		engine = new MyEngine( static_cast<std::string>(argv[1]));

		App::getInstance().getWindow().setEngine(engine);
	//otherwise we use the default engine only.
	}

    if (! (App::getInstance().getWindow().resetDisplay(0,0,16)))
    {
        testlog << nl << "Display Creation FAILED !"<< std::endl;
        exit(0);
    }
    else
    {
        App::getInstance().getWindow().mainLoop(2);
	//think about automatic exit after timeout...
    }
	delete engine;
    return 0;
}


