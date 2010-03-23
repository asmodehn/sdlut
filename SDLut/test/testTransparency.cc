#include "TestCommon.hh"

using namespace SDLut::video;

class AssertEngine;

Logger testlog("TestTransparency");


std::auto_ptr<Image> testImg;
std::auto_ptr<Image> bgtestImg;


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
        screen.blit(*bgtestImg,imgRPos);
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

//Image size : 85x62
const unsigned int imgwidth ;
const unsigned int imgheight ;

public:
    //we only need one render to see which color are there
    Test( Logger & log, const ArgParser & ap) : AssertEngine(log,ap), imgRPos(), imgwidth(85), imgheight(62)
	{
	    //building pixel test


        // rect of 1 pixel dark red around ( or grey in palettized )
        Color grey(0x80,0x80,0x80);
        Color darkred(0x80,0x00,0x00);

        pos.push_back(Rect(0,0,1,1));
        color.push_back(darkred);
        pos.push_back(Rect(imgwidth-1,0,1,1));
        color.push_back(darkred);
        pos.push_back(Rect(imgwidth-1,imgheight-1,1,1));
        color.push_back(darkred);
        pos.push_back(Rect(0,imgheight-1,1,1));
        color.push_back(darkred);


        Color white(0xff,0xff,0xff);
        Color blue(0x40,0x80,0x80);
        Color black(0x00,0x00,0x00);

        // 5 sample pixel test to make sure transparency is progressive
        //measure made on gray16a.png with The GIMP.
         unsigned int xtst[5] = {1,21,42,62,83};
         unsigned int alphaval[5] ={255,212,128,48,0};

        //black stripe
        pos.push_back( Rect( xtst[0],10,1,1));
        black.setA(alphaval[0]);
        color.push_back(black); //copy of color made. we can reuse it
        pos.push_back( Rect( xtst[1],10,1,1));
        black.setA(alphaval[1]);
        color.push_back(black); //copy of color made. we can reuse it
        pos.push_back( Rect( xtst[2],10,1,1));
        black.setA(alphaval[2]);
        color.push_back(black); //copy of color made. we can reuse it
        pos.push_back( Rect( xtst[3],10,1,1));
        black.setA(alphaval[3]);
        color.push_back(black); //copy of color made. we can reuse it
        pos.push_back( Rect( xtst[4],10,1,1));
        black.setA(alphaval[4]);
        color.push_back(black); //copy of color made. we can reuse it

        //blue stripe

        pos.push_back( Rect( xtst[0],30,1,1));
        blue.setA(alphaval[0]);
        color.push_back(blue); //copy of color made. we can reuse it
        pos.push_back( Rect( xtst[1],30,1,1));
        blue.setA(alphaval[1]);
        color.push_back(blue); //copy of color made. we can reuse it
        pos.push_back( Rect( xtst[2],30,1,1));
        blue.setA(alphaval[2]);
        color.push_back(blue); //copy of color made. we can reuse it
        pos.push_back( Rect( xtst[3],30,1,1));
        blue.setA(alphaval[3]);
        color.push_back(blue); //copy of color made. we can reuse it
        pos.push_back( Rect( xtst[4],30,1,1));
        blue.setA(alphaval[4]);
        color.push_back(blue); //copy of color made. we can reuse it

        //white stripe

        pos.push_back( Rect( xtst[0],50,1,1));
        white.setA(alphaval[0]);
        color.push_back(white); //copy of color made. we can reuse it
        pos.push_back( Rect( xtst[1],50,1,1));
        white.setA(alphaval[1]);
        color.push_back(white); //copy of color made. we can reuse it
        pos.push_back( Rect( xtst[2],50,1,1));
        white.setA(alphaval[2]);
        color.push_back(white); //copy of color made. we can reuse it
        pos.push_back( Rect( xtst[3],50,1,1));
        white.setA(alphaval[3]);
        color.push_back(white); //copy of color made. we can reuse it
        pos.push_back( Rect( xtst[4],50,1,1));
        white.setA(alphaval[4]);
        color.push_back(white); //copy of color made. we can reuse it



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
	    imgRPos.resetx( (width - testImg->getWidth()) / 2 );
        imgRPos.resety ( (height - testImg->getHeight()) /2);

		return true;
	}

	virtual bool assertrender(ScreenBuffer & screen) const
    {
        bool res = true;
        for (unsigned int i= 0; i<pos.size() ; i++)
        {
            Color expctd = blend(color[i],bgtestImg->getpixel(imgRPos.getx() + pos[i].getx(),imgRPos.gety() + pos[i].gety()));
            Color real = screen.getpixel(imgRPos.getx() + pos[i].getx(), imgRPos.gety() + pos[i].gety());
            if (!expctd.isSimilarTo(real))
            {
                m_log << nl << "Expected = " << expctd;
                m_log << nl << "Pixel at " << pos[i] << " : " << nl << real;
                setError(-1,"Wrong color detected. Is it a ColorTest.xxx image ?");
                std::string scsht("Screenshot_TestTransparency.bmp");
                m_log << nl << "Screenshot save at " << scsht;
                screen.captureBMP(scsht);
                res = false;
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
    App::getInstance().getDisplay().setDisplay(300,240); // using autodetected bpp

    App::getInstance().getDisplay().getScreenBuffer().setOpenGL(args.isOGL());

int exitstatus = -1;

    ImageLoader loader;
    std::string imgfile = args.get(1);
    std::string bgfile = args.get(2);
    if (imgfile != "" && bgfile != "" )
    {
        testImg = loader.load(imgfile);
        bgtestImg = loader.load(bgfile);
        Test teng(testlog,args);
        MyEngine engine(testlog,teng);


    if(App::getInstance().getDisplay().show())
    {
       exitstatus = App::getInstance().getDisplay().mainLoop();
    }

    }
    else
    {
        testlog << nl << "Usage : " << args.getcmd() << " <Transparent_image> <background_image>";

    }
    return exitstatus;
}



