#include "SDL.hh"
#include "Logger.hh"

using namespace RAGE;
using namespace RAGE::SDL;

Logger Log("Test Color");

	Image* red;
	Image* green;
	Image* blue;
	Image* alpha;

class MyEngine
{

public:

	MyEngine()
	{
	}

    virtual ~MyEngine(){}

	bool init(int width, int height)
	{
		red = new Image(width/4,height,32);
		red->fill(RGBColor(255,0,0));
		green = new Image(width/4,height,32);
		green->fill(RGBColor(0,255,0));
		blue = new Image(width/4,height,32);
		blue->fill(RGBColor(0,0,255));
		alpha = new Image(width-red->getWidth()-green->getWidth()-blue->getWidth(),height,32,true);
		alpha->fill(RGBAColor(255,255,255,0));

		Log << nl << "Red Pixel : " << std::hex << red->getpixel(0,0);
		Log << nl << "Green Pixel : " << std::hex << green->getpixel(0,0);
		Log << nl << "Blue Pixel : " << std::hex << blue->getpixel(0,0);
		//alpha->setpixel(0,0,RGBAColor(255,255,255,0)); //TMP : for testing only
		Log << nl << "Alpha Pixel : " << std::hex << alpha->getpixel(0,0);

		return true;
	}

	bool resize(int width, int height)
	{
		delete red; delete green; delete blue; delete alpha;
		red = new Image(width/4,height,32);
		red->fill(RGBColor(255,0,0));
		green = new Image(width/4,height,32);
		green->fill(RGBColor(0,255,0));
		blue = new Image(width/4,height,32);
		blue->fill(RGBColor(0,0,255));
		alpha = new Image(width-red->getWidth()-green->getWidth()-blue->getWidth(),height,32, true);
		alpha->fill(RGBAColor(255,255,255,0));
		return true;
	}

	bool render(ScreenBuffer & screen) const
    {
		screen.blit(*red,Point(0,0));
		screen.blit(*green,Point(0 + red->getWidth(),0));
		screen.blit(*blue,Point(0 + red->getWidth() + green->getWidth(), 0));
		screen.blit(*alpha,Point(0 + red->getWidth() + green->getWidth() + blue->getWidth(), 0));

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

    //Setting Display size and BPP
    App::getInstance().getWindow().setDisplay(800,600); // using autodetected bpp

	//Purple background color (useful to test alpha / color key)
	App::getInstance().getWindow().setBGColor(RGBColor (255,0,255));

    //Getting video informations
    testlog << nl << App::getInstance().getWindow().getScreenBuffer().getVideoInfo() << std::endl;
	//BUG HERE: displayed infos are false like available memory @ 0 for example

	std::auto_ptr<MyEngine> engine(new MyEngine());

	App::getInstance().getWindow().getScreenBuffer().resetInitCallback(&*engine,&MyEngine::init);
	App::getInstance().getWindow().getScreenBuffer().resetResizeCallback(&*engine,&MyEngine::resize);
	App::getInstance().getWindow().getScreenBuffer().resetRenderCallback(&*engine,&MyEngine::render);

    if(App::getInstance().getWindow().show())
    {
       App::getInstance().getWindow().mainLoop();
    }

	//engine managed by auto_ptr, deleted by the screen buffer...
	delete red; delete green; delete blue; delete alpha;
    return 0;
}


