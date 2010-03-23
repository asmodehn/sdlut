#include "TestCommon.hh"

using namespace SDLut::video;

class AssertEngine;

Logger testlog("TestImage");


std::auto_ptr<Image> testImg;


class MyEngine : public TestEngine
{

    mutable Rect imgRPos;

public:

	MyEngine(Logger & log, AssertEngine & ae) : TestEngine(log,ae), imgRPos()
	{
	}

    virtual ~MyEngine()
    {

        }

	virtual bool init(int width, int height)
	{
	    return resize(width,height);
	}

	virtual bool resize(int width, int height)
	{
        imgRPos.resetx( (width - testImg->getWidth()) / 2 );
        imgRPos.resety( (height - testImg->getHeight()) /2 );
        imgRPos.resetw(testImg->getWidth());
	    imgRPos.reseth(testImg->getHeight());
		return true;
	}

	virtual bool render(ScreenBuffer & screen) const
    {
		screen.blit(*testImg,imgRPos);
		return true;
    }

};


class Test : public AssertEngine
{

Rect imgRPos;

//this Assert Engine check that loaded image is a proper ColorTest image
std::vector<Rect> pos;
std::vector<Color> color;


public:
    //we only need one render to see which color are there
    Test( Logger & log, const ArgParser & ap) : AssertEngine(log,ap), imgRPos()
	{
	    //building pixel test
	    //top columns
	    pos.push_back(Rect(10,10,1,1));
	    color.push_back(Color(0xcc,0xcc,0xcc)); // light grey
	    pos.push_back(Rect(100,10,1,1));
	    color.push_back(Color(0xff,0xff,0x00)); //yellow
	    pos.push_back(Rect(190,10,1,1));
	    color.push_back(Color(0x00,0xff,0xff)); //light blue
	    pos.push_back(Rect(280,10,1,1));
	    color.push_back(Color(0x00,0xff,0x00)); //green
	    pos.push_back(Rect(380,10,1,1));
	    color.push_back(Color(0xff,0x00,0xff)); //pink
	    pos.push_back(Rect(470,10,1,1));
	    color.push_back(Color(0xff,0x00,0x00)); //red
	    pos.push_back(Rect(560,10,1,1));
	    color.push_back(Color(0x00,0x00,0xff)); //blue
	    // middle rect
	    pos.push_back(Rect(10,340,1,1));
	    color.push_back(Color(0x00,0x00,0xff)); //blue
	    pos.push_back(Rect(100,340,1,1));
	    color.push_back(Color(0x13,0x13,0x13)); // dark grey
	    pos.push_back(Rect(190,340,1,1));
	    color.push_back(Color(0xff,0x00,0xff)); //pink
	    pos.push_back(Rect(280,340,1,1));
	    color.push_back(Color(0x13,0x13,0x13)); // dark grey
	    pos.push_back(Rect(380,340,1,1));
	    color.push_back(Color(0x00,0xff,0xff)); //light blue
	    pos.push_back(Rect(470,340,1,1));
	    color.push_back(Color(0x13,0x13,0x13)); // dark grey
	    pos.push_back(Rect(560,340,1,1));
	    color.push_back(Color(0xcc,0xcc,0xcc)); // light grey
	    // lower rect
	    pos.push_back(Rect(10,380,1,1));
	    color.push_back(Color(0x08,0x3e,0x59)); // marine blue
	    pos.push_back(Rect(120,380,1,1));
	    color.push_back(Color(0xff,0xff,0xff)); // white
	    pos.push_back(Rect(240,380,1,1));
	    color.push_back(Color(0x3a,0x00,0x7e)); // purple
	    pos.push_back(Rect(350,380,1,1));
	    color.push_back(Color(0x13,0x13,0x13)); // dark grey
	    pos.push_back(Rect(470,380,1,1));
	    color.push_back(Color(0x00,0x00,0x00)); // black
	    pos.push_back(Rect(500,380,1,1));
	    color.push_back(Color(0x13,0x13,0x13)); // dark grey
	    pos.push_back(Rect(540,380,1,1));
	    color.push_back(Color(0x26,0x26,0x26)); // grey
	    pos.push_back(Rect(560,380,1,1));
	    color.push_back(Color(0x13,0x13,0x13)); // dark grey









	    //TODO : need to check all colors ( in case of wrong colorkey, or format or whatever

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
	    imgRPos.resetx( (width - testImg->getWidth()) / 2);
        imgRPos.resety ( (height - testImg->getHeight()) /2);

		return true;
	}

	virtual bool assertrender(ScreenBuffer & screen) const
    {
        bool res = true;
        for (unsigned int i= 0; i<pos.size() ; i++)
        {
            res  = res && color[i].isSimilarTo(screen.getpixel(imgRPos.getx() + pos[i].getx(), imgRPos.gety() + pos[i].gety()));
            if (!res)
            {
                m_log << nl << "Expected = " << color[i];
                m_log << nl << "Pixel at " << pos[i] << " : ";
                m_log << nl << screen.getpixel(imgRPos.getx() + pos[i].getx(), imgRPos.gety() + pos[i].gety());
                setError(-1,"Wrong color detected. Is it a ColorTest.xxx image ?");
            }

        }

		return res;
    }

};

int main(int argc, char** argv)
{
    ArgParser args(argc,argv);

    //Starting with usual SDL window
    App::getInstance().initVideo(false,true,false);
	App::getInstance().setName ("SDLut::video test Image");

    //Setting Display size and BPP
    App::getInstance().getDisplay().setDisplay(800,600); // using autodetected bpp

    App::getInstance().getDisplay().getScreenBuffer().setOpenGL(args.isOGL());

int exitstatus = -1;

    ImageLoader loader;
    std::string imgfile = args.get(1);
    if (imgfile != "" )
    {
        testImg = loader.load(imgfile);
        Test teng(testlog,args);
	MyEngine engine(testlog,teng);


    if(App::getInstance().getDisplay().show())
    {
       exitstatus = App::getInstance().getDisplay().mainLoop();
    }

    }
    else
    {
        testlog << nl << " File : " << imgfile << "not found. Exiting.";
    }
    return exitstatus;
}


