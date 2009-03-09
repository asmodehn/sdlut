#include "SDL.hh"
#include "Logger.hh"
using namespace RAGE;
using namespace RAGE::SDL;

Logger Log("Test Video");

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

    App::getInstance().getWindow().setBGColor(RGBColor (128,0,0));
	
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


