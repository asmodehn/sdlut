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
		Log << nl << "Alpha Pixel : " << std::hex << alpha->getpixel(0,0); //BUG HERE: alpha value is always gotten at FF

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

	void prerender(unsigned long deltaticks)
	{
		return DefaultEngine::prerender(deltaticks);
	}

	void render(VideoSurface & screen) const
    {
		screen.blit(*red,Point(0,0));
		screen.blit(*green,Point(0 + red->getWidth(),0));
		screen.blit(*blue,Point(0 + red->getWidth() + green->getWidth(), 0));
		screen.blit(*alpha,Point(0 + red->getWidth() + green->getWidth() + blue->getWidth(), 0));
		//BUG HERE: no merge w the BGColor even if there is a alpha on this color
		return DefaultEngine::render(screen);
    }

	void postrender()
	{
		return DefaultEngine::postrender();
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
	
    //Getting video informations
    testlog << nl << App::getInstance().getWindow().getVideoInfo() << std::endl;
	//BUG HERE: displayed infos are false like available memory @ 0 for example

	//Purple background color (useful to test alpha / color key)
	App::getInstance().getWindow().setBGColor(RGBColor (255,0,255));

	Engine* engine;
	engine = new MyEngine();

	App::getInstance().getWindow().setEngine(engine);

    if(App::getInstance().getWindow().resetDisplay(800,600))
    {
       App::getInstance().getWindow().mainLoop();
    }

	delete engine;
	delete red; delete green; delete blue; delete alpha;
    return 0;
}


