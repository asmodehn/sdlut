#include "SDL.hh"
#include "Logger.hh"
using namespace RAGE;
using namespace RAGE::SDL;

Logger Log("Test Video");

class MyEngine
{

public:

	std::auto_ptr<Image> loadedimage;
	mutable Rect imagepos;

	MyEngine( const std::string & imagefilename) : imagepos()
	{
		ImageLoader loader;
		loadedimage = loader.load(imagefilename,Color(0,0,0,255));
	}

    virtual ~MyEngine(){}

    bool init(int width, int height)
	{
		imagepos.resetx( (width - loadedimage->getWidth()) /2);
		imagepos.resety( (height - loadedimage->getHeight()) /2);
		imagepos.resetw( loadedimage->getWidth());
		imagepos.reseth( loadedimage->getHeight());
		return true;
	}

	bool resize(int width, int height)
	{
		imagepos.resetx( (width - loadedimage->getWidth()) /2);
		imagepos.resety( (height - loadedimage->getHeight()) /2);
		imagepos.resetw( loadedimage->getWidth());
		imagepos.reseth( loadedimage->getHeight());
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
//BUG: OpenGL mode fucked up when displaying an external image (white square) and when resized the logo is fucked up the same way
    Logger testlog("Test Log");

	bool ogl = false;
	if ((argc > 1) && ( std::string(argv[1]) == "opengl" ) )
    {
        ogl = true;
    }

    //Setup example

    testlog << nl << " Enabling SDL Video... " << std::endl;
    App::getInstance().initVideo(false,ogl,true,false);

	App::getInstance().setName ("RAGE::SDL test - Video");

    App::getInstance().getDisplay().setBGColor(Color (128,0,0));


	//if argument we load the image in the test engine
	std::auto_ptr<MyEngine> engine;
	if ( ( argc == 3) || ( argc == 2 && !ogl ) )
	{
	if ( argc == 3)
		engine.reset(new MyEngine(static_cast<std::string>(argv[2])));
	else // ( argc == 2 && !ogl )
		engine.reset(new MyEngine(static_cast<std::string>(argv[1])));


	App::getInstance().getDisplay().resetInitCallback(*engine,&MyEngine::init);
	App::getInstance().getDisplay().resetResizeCallback(*engine,&MyEngine::resize);
	App::getInstance().getDisplay().resetRenderCallback(*engine,&MyEngine::render);

	//otherwise we use the default engine only.
	}

    if (! (App::getInstance().getDisplay().setDisplay(800,600,16)))
    {
        testlog << nl << "Display Creation FAILED !"<< std::endl;
    }
    else if ( App::getInstance().getDisplay().show() )
    {
        App::getInstance().getDisplay().mainLoop();
	//think about automatic exit after timeout...
    }

    return 0;
}


