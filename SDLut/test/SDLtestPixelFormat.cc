#include "TestCommon.hh"

using namespace SDLut::video;

class AssertEngine;

Logger testlog("TestPixelFormat");

class MyEngine : public TestEngine
{
    Image * red,*green,*blue,*alpha;


public:

	MyEngine(Logger & log, AssertEngine & ae) : TestEngine(log,ae), red(0), green(0),blue(0),alpha(0)
	{
	}

    virtual ~MyEngine()
    {
        delete red; delete green; delete blue; delete alpha;
        }

	virtual bool init(int width, int height)
	{

	    return resize(width,height);
	}

	virtual bool resize(int width, int height)
	{
		delete red; delete green; delete blue; delete alpha;
		red = new Image(width/4,height,32);
		red->fill(Color(255,0,0));
		green = new Image(width/4,height,32);
		green->fill(Color(0,255,0));
		blue = new Image(width/4,height,32);
		blue->fill(Color(0,0,255,128));
		alpha = new Image(width-red->getWidth()-green->getWidth()-blue->getWidth(),height,32, true);
		alpha->fill(Color(255,255,255,128));


		std::cout << "Red Pixel : " << std::hex << red->getpixel(0,0) << std::endl;
		std::cout << "Green Pixel : " << std::hex << green->getpixel(0,0)<< std::endl;
		std::cout << "Blue Pixel : " << std::hex << blue->getpixel(0,0)<< std::endl;
		std::cout << "Alpha Pixel : " << std::hex << alpha->getpixel(0,0)<< std::endl;

		return true;
	}

	virtual bool render(ScreenBuffer & screen) const
    {
        Rect red_dst(0,0,red->getWidth(),red->getHeight());
		screen.blit(*red,red_dst);
		Rect green_dst(0 + red->getWidth(),0,green->getWidth(),green->getHeight());
		screen.blit(*green,green_dst);
		Rect blue_dst(0 + red->getWidth() + green->getWidth(), 0,blue->getWidth(),blue->getHeight());
		screen.blit(*blue,blue_dst);
		Rect alpha_dst(0 + red->getWidth() + green->getWidth() / 2, 0,alpha->getWidth(),alpha->getHeight());
		screen.blit(*alpha,alpha_dst);

		return true;
    }

};


class Test : public AssertEngine
{
    Rect posred,posgreen,posblue,posalpha;

    Color red,green,blue,alpha;
public:
    //we only need one render to see which color are there
    Test( Logger & log) : AssertEngine(log,1)
	{
	    red = Color(255,0,0);
	    green = Color(0,255,0);
	    blue  = Color(0,0,255);
	    alpha = Color(0,0,0,0);
	}

    virtual ~Test()
    {
    }

	virtual bool assertinit(int width, int height)
	{

	    return assertresize(width,height);
	}

	virtual bool assertresize(int width, int height)
	{


		posred = Rect(0,0,width/4,height);
		posgreen = Rect(0 + posred.getw(),0,width/4,height);
        posblue = Rect(0 + posred.getw() + posgreen.getw(), 0,width/4,height);
		posalpha = Rect(0 + posred.getw() + posgreen.getw() / 2, 0,width-posred.getw()-posgreen.getw()-posblue.getw(),height);


		return true;
	}

	virtual bool assertrender(ScreenBuffer & screen) const
    {
        bool res = false;
        res &=  red == screen.getpixel(posred.getx(),posred.gety());
        if (!res)
        {
            m_log << nl << "Red = " << red;
            m_log << nl << "Pixel = " << screen.getpixel(posred.getx(),posred.gety());
            setError(-1,"Red Pixel is wrong");
        }
		res &= green == screen.getpixel(posgreen.getx(),posgreen.gety());
		if (!res)
        {
            m_log << nl << "Green = " << green;
            m_log << nl << "Pixel = " << screen.getpixel(posgreen.getx(),posgreen.gety());
            setError(-1,"Green Pixel is wrong");
        }
		res &= blue == screen.getpixel(posblue.getx(),posblue.gety());
		if (!res)
        {
            m_log << nl << "Blue = " << blue;
            m_log << nl << "Pixel = " << screen.getpixel(posblue.getx(),posblue.gety());
            setError(-1,"Blue Pixel is wrong");
        }
		res &= alpha == screen.getpixel(posalpha.getx(),posalpha.gety());
		if (!res)
        {
            m_log << nl << "Alpha = " << alpha;
            m_log << nl << "Pixel = " << screen.getpixel(posalpha.getx(),posalpha.gety());
            setError(-1,"Alpha Pixel is wrong");
        }

		return res;
    }

};

int main(int argc, char** argv)
{
    ArgParser args(argc,argv);

    //Starting with usual SDL window
    App::getInstance().initVideo(false,true,false);
	App::getInstance().setName ("SDLut::SDL test Color : Displayed Color order \"Red - Green - Blue - Purple if alpha is working otherwise White\"");

    //Setting Display size and BPP
    App::getInstance().getDisplay().setDisplay(800,600); // using autodetected bpp

    App::getInstance().getDisplay().getScreenBuffer().setOpenGL(args.isOGL());

	//yellow background color (useful to test alpha / color key)
	App::getInstance().getDisplay().getScreenBuffer().setBGColor(Color (255,255,0));

    Test teng(testlog);
	MyEngine engine(testlog,teng);

    int exitstatus = -1;
    if(App::getInstance().getDisplay().show())
    {
       exitstatus = App::getInstance().getDisplay().mainLoop();
    }

    return exitstatus;
}


