#include "SDL.hh"
#include "Logger.hh"

using namespace RAGE;
using namespace RAGE::SDL;

Logger Log("Test Color");

	RGBSurface* red;
	RGBSurface* green;
	RGBSurface* blue;
	RGBSurface* alpha;

class MyEngine : public DefaultEngine
{

public:

	MyEngine() : DefaultEngine()
	{
	}

    virtual ~MyEngine(){}

	bool init(int width, int height)
	{
		red = new GLSurface(width/4,height,32);
		red->fill(RGBColor(255,0,0));
		green = new GLSurface(width/4,height,32);
		green->fill(RGBColor(0,255,0));
		blue = new GLSurface(width/4,height,32);
		blue->fill(RGBColor(0,0,255));
		alpha = new GLSurface(width-red->getWidth()-green->getWidth()-blue->getWidth(),height,32,true);
		alpha->fill(RGBAColor(255,255,255,0));

		Log << nl << "Red Pixel : " << std::hex << red->getpixel(0,0);
		Log << nl << "Green Pixel : " << std::hex << green->getpixel(0,0);
		Log << nl << "Blue Pixel : " << std::hex << blue->getpixel(0,0);
		alpha->setpixel(0,0,RGBAColor(255,255,255,0));
		Log << nl << "Alpha Pixel : " << std::hex << alpha->getpixel(0,0);

		return DefaultEngine::init(width,height);
	}

	bool resize(int width, int height)
	{
		delete red; delete green; delete blue; delete alpha;
		red = new GLSurface(width/4,height,32);
		red->fill(RGBColor(255,0,0));
		green = new GLSurface(width/4,height,32);
		green->fill(RGBColor(0,255,0));
		blue = new GLSurface(width/4,height,32);
		blue->fill(RGBColor(0,0,255));
		alpha = new GLSurface(width-red->getWidth()-green->getWidth()-blue->getWidth(),height,32, true);
		alpha->fill(RGBAColor(255,255,255,0));
		return DefaultEngine::resize(width,height);
	}

	bool render(VideoSurface & screen) const
    {
		screen.blit(*red,Point(0,0));
		screen.blit(*green,Point(0 + red->getWidth(),0));
		screen.blit(*blue,Point(0 + red->getWidth() + green->getWidth(), 0));
		screen.blit(*alpha,Point(0 + red->getWidth() + green->getWidth() + blue->getWidth(), 0));
		DefaultEngine::render(screen);
		return true;
    }

};


int main(int argc, char** argv)
{
    Logger testlog("Test Log");

	bool ogl = false;
	if (argc > 1 && std::string(argv[1]) == "opengl" ) ogl = true;

    //Starting with usual SDL window
    App::getInstance().initVideo(false,ogl,true,false);
	App::getInstance().setName ("RAGE::SDL test Color : Displayed Color order \"Red - Green - Blue - Purple if alpha is working else White\"");  //BUG HERE: Title never displayed ?!

	//Purple background color (useful to test alpha / color key)
	App::getInstance().getWindow().setBGColor(RGBColor (255,0,255));

    //Setting Display size and BPP
    App::getInstance().getWindow().setDisplay(800,600); // using autodetected bpp

    //Getting video informations
    testlog << nl << App::getInstance().getWindow().getScreenBuffer().getVideoInfo() << std::endl;
	//BUG HERE: displayed infos are false like available memory @ 0 for example

	std::auto_ptr<Engine> engine(new MyEngine());
	//sinking the auto_ptr, and transmitting delete responsibility...
	//App::getInstance().getWindow().getScreenBuffer().resetEngine(engine);
    //update : not anymore -> using callbacks now

	App::getInstance().getWindow().getScreenBuffer().resetInitCallback(&*engine,&Engine::init);
	App::getInstance().getWindow().getScreenBuffer().resetResizeCallback(&*engine,&Engine::resize);
	App::getInstance().getWindow().getScreenBuffer().resetRenderCallback(&*engine,&Engine::render);

    if(App::getInstance().getWindow().show())
    {
       App::getInstance().getWindow().mainLoop();
    }

	//enging managed by auto_ptr now, deleted by the screen buffer...
	delete red; delete green; delete blue; delete alpha;
    return 0;
}


