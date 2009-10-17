#include "SDL.hh"

using namespace RAGE;
using namespace RAGE::SDL;

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
		red->fill(RGBAColor(255,0,0));
		green = new Image(width/4,height,32);
		green->fill(RGBAColor(0,255,0));
		blue = new Image(width/4,height,32);
		blue->fill(RGBAColor(0,0,255));
		alpha = new Image(width-red->getWidth()-green->getWidth()-blue->getWidth(),height,32,true);
		alpha->fill(RGBAColor(255,255,255,0));

		std::cout << "Red Pixel : " << std::hex << red->getpixel(0,0);
		std::cout << "Green Pixel : " << std::hex << green->getpixel(0,0);
		std::cout << "Blue Pixel : " << std::hex << blue->getpixel(0,0);
		//alpha->setpixel(0,0,RGBAColor(255,255,255,0)); //TMP : for testing only
		std::cout << "Alpha Pixel : " << std::hex << alpha->getpixel(0,0);

		return true;
	}

	bool resize(int width, int height)
	{
		delete red; delete green; delete blue; delete alpha;
		red = new Image(width/4,height,32);
		red->fill(RGBAColor(255,0,0));
		green = new Image(width/4,height,32);
		green->fill(RGBAColor(0,255,0));
		blue = new Image(width/4,height,32);
		blue->fill(RGBAColor(0,0,255));
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

	bool ogl = false;
	if (argc > 1 && std::string(argv[1]) == "opengl" ) ogl = true;

    //Starting with usual SDL window
    App::getInstance().initVideo(false,ogl,true,false);
	App::getInstance().setName ("RAGE::SDL test Color : Displayed Color order \"Red - Green - Blue - Purple if alpha is working else White\"");  //BUG HERE: Title never displayed ?!

    //Setting Display size and BPP
    App::getInstance().getDisplay().setDisplay(800,600); // using autodetected bpp

	//Purple background color (useful to test alpha / color key)
	App::getInstance().getDisplay().setBGColor(RGBAColor (255,0,255));

    //Getting video informations
    //std::cout << App::getInstance().getDisplay().getScreenBuffer().getVideoInfo() << std::endl;
	//BUG HERE: displayed infos are false like available memory @ 0 for example
	//this shouldnt work anymore since we moved the Log out of SDLut
	//TODO : find a way to force the dump of info into the SDLut Log

	std::auto_ptr<MyEngine> engine(new MyEngine());

	App::getInstance().getDisplay().resetInitCallback(&*engine,&MyEngine::init);
	App::getInstance().getDisplay().resetResizeCallback(&*engine,&MyEngine::resize);
	App::getInstance().getDisplay().resetRenderCallback(&*engine,&MyEngine::render);

    if(App::getInstance().getDisplay().show())
    {
       App::getInstance().getDisplay().mainLoop();
    }

	//engine managed by auto_ptr, deleted by the screen buffer...
	delete red; delete green; delete blue; delete alpha;
    return 0;
}


