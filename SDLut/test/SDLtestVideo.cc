#include "SDL.hh"
#include "Logger.hh"
using namespace RAGE;
using namespace RAGE::SDL;

Logger Log("Test Video");

class MyEngine
{

public:

	std::auto_ptr<Image> loadedimage;
	Point imagepos;

	MyEngine( const std::string & imagefilename) : imagepos()
	{
		ImageLoader loader;
		loadedimage = loader.load(imagefilename,RGBAColor(0,0,0,255));
	}

    virtual ~MyEngine(){}

    bool init(int width, int height)
	{
		imagepos.setx( (width - loadedimage->getWidth()) /2);
		imagepos.sety( (height - loadedimage->getHeight()) /2);
		return true;
	}

	bool resize(int width, int height)
	{
		imagepos.setx( (width - loadedimage->getWidth()) /2);
		imagepos.sety( (height - loadedimage->getHeight()) /2);
		return true;
	}

	bool render(ScreenBuffer & screen) const
    {
		screen.blit(*loadedimage, imagepos );

		return true;
    }
};


//Main Program
int main(int argc, char** argv)
{

    Logger testlog("Test Log");

    //Setup example

    testlog << nl << " Enabling SDL Video... " << std::endl;
    App::getInstance().initVideo(false,false,true,false);

	App::getInstance().setName ("RAGE::SDL test - Video");

    App::getInstance().getDisplay().setBGColor(RGBColor (128,0,0));


	//if argument we load the image in the test engine
	std::auto_ptr<MyEngine> engine;
	if ( argc > 1)
	{

	engine.reset(new MyEngine(static_cast<std::string>(argv[1])));

	App::getInstance().getDisplay().resetInitCallback(&*engine,&MyEngine::init);
	App::getInstance().getDisplay().resetResizeCallback(&*engine,&MyEngine::resize);
	App::getInstance().getDisplay().resetRenderCallback(&*engine,&MyEngine::render);

	//otherwise we use the default engine only.
	}

    if (! (App::getInstance().getDisplay().setDisplay(0,0,16)))
    {
        testlog << nl << "Display Creation FAILED !"<< std::endl;
    }
    else if ( App::getInstance().getDisplay().show() )
    {
        App::getInstance().getDisplay().mainLoop(2);
	//think about automatic exit after timeout...
    }

    return 0;
}


