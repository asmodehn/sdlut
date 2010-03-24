#include "TestCommon.hh"

using namespace SDLut::video;

class AssertEngine;

Logger testlog("TestPixelFormat");

Color bgc(128,128,128);
Color red(255,0,0);
Color green(0,255,0);
Color blue(0,0,255);
Color alpha(255,255,255,128);


class MyEngine : public TestEngine
{
    Image * imgred,*imggreen,*imgblue,*imgalpha;

public:

	MyEngine(Logger & log, AssertEngine & ae) : TestEngine(log,ae), imgred(0), imggreen(0),imgblue(0),imgalpha(0)
	{
	    App::getInstance().getDisplay().getScreenBuffer().setBGColor(bgc);
	}

    virtual ~MyEngine()
    {
        delete imgred; delete imggreen; delete imgblue; delete imgalpha;
        }

	virtual bool init(int width, int height)
	{
	    return resize(width,height);
	}

	virtual bool resize(int width, int height)
	{
		delete imgred; delete imggreen; delete imgblue; delete imgalpha;
		imgred = new Image(width/4,height,32);
		imgred->fill(red);
		imggreen = new Image(width/4,height,32);
		imggreen->fill(green);
		imgblue = new Image(width/4,height,32);
		imgblue->fill(blue);
		imgalpha = new Image(width-imgred->getWidth()-imggreen->getWidth()-imgblue->getWidth(),height,32, true);
		imgalpha->fill(alpha);

		testlog << "Red Pixel : " << std::hex << imgred->getpixel(0,0) << std::endl;
		testlog << "Green Pixel : " << std::hex << imggreen->getpixel(0,0)<< std::endl;
		testlog << "Blue Pixel : " << std::hex << imgblue->getpixel(0,0)<< std::endl;
		testlog << "Alpha Pixel : " << std::hex << imgalpha->getpixel(0,0)<< std::endl;

		return true;
	}

	virtual bool render(ScreenBuffer & screen) const
    {
        Rect red_dst(0,0,imgred->getWidth(),imgred->getHeight());
		screen.blit(*imgred,red_dst);
		Rect green_dst(0 + imgred->getWidth(),0,imggreen->getWidth(),imggreen->getHeight());
		screen.blit(*imggreen,green_dst);
		Rect blue_dst(0 + imgred->getWidth() + imggreen->getWidth(), 0,imgblue->getWidth(),imgblue->getHeight());
		screen.blit(*imgblue,blue_dst);
		Rect alpha_dst(0 + imgred->getWidth() + imggreen->getWidth() + imgblue->getWidth(), 0, imgalpha->getWidth(),imgalpha->getHeight());
		screen.blit(*imgalpha,alpha_dst);

		return true;
    }

};


class Test : public AssertEngine
{

    Rect posred,posgreen,posblue,posalpha;

public:
    //we only need one render to see which color are there
    Test( Logger & log, const ArgParser & args) : AssertEngine(log,args)
	{
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
		posalpha = Rect(0 + posred.getw() + posgreen.getw() + posblue.getw(), 0,width-posred.getw()-posgreen.getw()-posblue.getw(),height);


		return true;
	}

	virtual bool assertrender(ScreenBuffer & screen) const
    {
        bool res = true;
        res = res &&  blend(red,bgc).isSimilarTo(screen.getpixel(posred.getx(),posred.gety()));
        if (!res)
        {
            m_log << nl << "Red = " << blend(red,bgc);
            m_log << nl << "Pixel = " << screen.getpixel(posred.getx(),posred.gety());
            setError(-1,"Red Pixel is wrong");
        }
		res = res && blend(green,bgc).isSimilarTo(screen.getpixel(posgreen.getx(),posgreen.gety()));
		if (!res)
        {
            m_log << nl << "Green = " << blend(green,bgc);
            m_log << nl << "Pixel = " << screen.getpixel(posgreen.getx(),posgreen.gety());
            setError(-1,"Green Pixel is wrong");
        }
		res = res && blend(blue,bgc).isSimilarTo( screen.getpixel(posblue.getx(),posblue.gety()));
		if (!res)
        {
            m_log << nl << "Blue = " << blend(blue,bgc);
            m_log << nl << "Pixel = " << screen.getpixel(posblue.getx(),posblue.gety());
            setError(-1,"Blue Pixel is wrong");
        }
		res = res && blend(alpha,bgc).isSimilarTo( screen.getpixel(posalpha.getx(),posalpha.gety()));
		if (!res)
        {
            m_log << nl << "Alpha = " << blend(alpha,bgc);
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
	App::getInstance().setName ("SDLut::video test PixelFormat");

    //Setting Display size and BPP
    App::getInstance().getDisplay().setDisplay(300,240); // using autodetected bpp

    App::getInstance().getDisplay().getScreenBuffer().setOpenGL(args.isOGL());

    Test teng(testlog,args);
	MyEngine engine(testlog,teng);

    int exitstatus = -1;
    if(App::getInstance().getDisplay().show())
    {
       exitstatus = App::getInstance().getDisplay().mainLoop();
    }

    return exitstatus;
}


